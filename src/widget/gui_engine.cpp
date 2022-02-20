#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {

/**
 * @brief 새로운 이벤트 타입의 이벤트를 만들고 Simple 이벤트를 전달합니다.
 *
 * @param ExcuteFunction
 * @param inEvent
 */
void MakeAndForwardSimpleEvent(WidgetPtr& inWidget, EventType inEventType) {
  Event e;
  e.type = inEventType;

  inWidget->ForwardEvent(e);
}

/**
 * @brief excute 함수들을 정의합니다.
 * 위젯을 찾고 실제로 무엇을 할지 정의하는 함수들입니다.
 * ExcuteFunction 의 첫 번째 인자로
 * util::FindCollisionWidgetToDotAndExcute 가 찾아낸 첫번째 위젯이 있습니다.
 *
 * excute 함수는 다음 원형을 가지고 있습니다.
 * typedef void (*ExcuteFunction)( WidgetPtr& inWidget, const Event& inEvent);
 */
namespace excute {

/**
 * @brief 위젯 포커스를 처리합니다.
 * NOTE 위젯의 포커스가 변경되기 위해서는 마우스 버튼 다운 일경우
 * 해당 위젯이 포커스를 가질 수 있는 위젯이어야 하고
 * 해당 위젯에 클릭된 마우스 버튼이 BUTTN_LEFT 이벤트가 발생되어야 합니다.
 * GUI_ENGINE에 포커스된 위젯이 현제 선택된 위젯과 같지 않아야 됩니다.
 */
void ProcessWidgetFocus(WidgetPtr& inWidget, const Event& inEvent) {
  bool& is_mouse_button_down =
      GuiEngine::sInstance->GetIsMouseLeftButtonDownRef();

  if (!is_mouse_button_down) {
    return;  //현제 마우스 다운 상태가 아닌경우
  }

  if (inWidget == GuiEngine::sInstance->GetFocusWidget()) {
    return;  // GUI_ENGINE에 포커스된 위젯이 현제 선택된 위젯과 같을경우
  }

  if (!inWidget->IsFocusable()) {
    return;  // 위젯이 포커스를 가질 수 없다면
  }

  auto& current_focus_ref = GuiEngine::sInstance->GetFocusWidget();
  MakeAndForwardSimpleEvent(current_focus_ref, EventType::ON_UNFOCUS);

  GuiEngine::sInstance->SetFocusWidget(inWidget);
  MakeAndForwardSimpleEvent(inWidget, EventType::ON_FOCUS);
}

/**
 * @brief 클릭을 처리합니다.
 * 여기서 말하는 클릭이란?
 * 마우스 LEFT 다운 후 UP 할때 둘다 같은 위젯일 경우 클릭 이벤트를 만들어
 * 발생시킵니다.
 */
void ProcessWidgetClick(WidgetPtr& inWidget, const Event& inEvent) {
  auto& is_mouse_button_down =
      GuiEngine::sInstance->GetIsMouseLeftButtonDownRef();

  if (is_mouse_button_down) {  // 마우스 버튼 다운일경우
    GuiEngine::sInstance->SetMouseClickCacheWidget(inWidget);
  } else {  // 마우스 버튼 Up일경우
    auto& cached_widget = GuiEngine::sInstance->GetMouseClickCacheWidget();

    if (cached_widget == inWidget) {
      MakeAndForwardSimpleEvent(inWidget, EventType::ON_CLICK);
    }
    // 캐시를 초기화합니다.
    cached_widget.reset();
  }
}

/**
 * @brief 마우스 버튼을 눌렀을경우
 * 위젯 클릭을 처리합니다.
 * 위젯 포커스를 처리합니다.
 * @param inWidget
 * @param inEvent
 */
void MouseButtonExcute(WidgetPtr& inWidget, const Event& inEvent) {
  ProcessWidgetFocus(inWidget, inEvent);
  ProcessWidgetClick(inWidget, inEvent);
}

/**
 * @brief Mouse Hover 이벤트를 처리합니다.
 *
 * 또한 캐쉬된 위젯이 찾은 위젯이랑 같지 않을경우
 * OnHover, OnUnHover 이벤트를 전달합니다.
 * @param inWidget
 */
void ProcessMouseHoveringEventExcute(WidgetPtr& inWidget,
                                     const Event& inEvent) {
  auto&& cached_widget = GuiEngine::sInstance->GetMouseHoveringCacheWidget();
  if (cached_widget == nullptr) {
    MakeAndForwardSimpleEvent(inWidget, EventType::HOVER);
    GuiEngine::sInstance->SetMouseHoveringCacheWidget(inWidget);
    return;
  }

  if (cached_widget != inWidget) {
    // 지금 호버링된 위젯에 hover 이벤트를 전달하고
    MakeAndForwardSimpleEvent(inWidget, EventType::HOVER);
    // 이전에 호버링된 위젯에 unHover 이벤트를 전달합니다.
    // 그리고 지금 호버링된 값을 캐슁합니다.
    MakeAndForwardSimpleEvent(cached_widget, EventType::UNHOVER);
    GuiEngine::sInstance->SetMouseHoveringCacheWidget(inWidget);
  }
}

/**
 * @brief 마우스 모션 이벤트를 처리합니다.
 * 마우스 모션 이벤트가 발생하였을 경우 OnHover, OnUnHover 이벤트를 전달합니다.
 *
 * @param inWidget
 */
void MouseMotionExcute(WidgetPtr& inWidget, const Event& inEvent) {
  ProcessMouseHoveringEventExcute(inWidget,
                                  inEvent);  // 마우스 하버 이벤트를 전달합니다.
}

}  // namespace excute

std::unique_ptr<GuiEngine> GuiEngine::sInstance;

void GuiEngine::StaticInit() {
  if (!WidgetManager::sInstance) {
    LOG(LogLevel::Fatal,
        ls::widget::GUI_ENGINE_INIT_ERROR_REQUIRED_WIDGET_MANAGER);
    throw Exception(ls::widget::GUI_ENGINE_INIT_ERROR);
  }

  auto base_widget = WidgetManager::sInstance->GetBaseWidget();
  sInstance.reset(new GuiEngine(base_widget));
  LOG(LogLevel::Info, ls::widget::GUI_ENGINE_INIT_COMPLETION);
}

void GuiEngine::HandleEvent(const Event& inEvent) {
  // 현제 포커스 위젯에 모든 이벤트를 전달합니다.
  mFocusWidget->ForwardEvent(inEvent);

  // 이벤트를 이용하여 새로운 이벤트를 생성후 방문합니다.
  switch (inEvent.type) {
    case EventType::MOUSE_MOTION:
      HandleMouseMotionEvent(inEvent);
      break;
    case EventType::MOUSE_BUTTON_DOWN:
    case EventType::MOUSE_BUTTON_UP:
      HandleMouseButtonEvent(inEvent);
      break;
    default:
      break;
  }
}
void GuiEngine::HandleMouseMotionEvent(const Event& inEvent) {
  // 마우스 모션이 일어나는 위치를 찾아서 각 이벤트를 전달합니다.
  int mouse_pos_x = inEvent.mouse_motion.x;
  int mouse_pos_y = inEvent.mouse_motion.y;
  util::FindCollisionWidgetToDotAndExcute(mRootWidget, mouse_pos_x, mouse_pos_y,
                                          excute::MouseMotionExcute, inEvent);
}

void GuiEngine::SetIsMouseLeftButtonDownState(const Event& inEvent) {
  if (inEvent.mouse.type == EventType::MOUSE_BUTTON_DOWN &&
      inEvent.mouse.button == MouseButton::BUTTON_LEFT) {
    mIsMouseLeftButtonDown = true;
  };

  if (inEvent.mouse.type == EventType::MOUSE_BUTTON_UP &&
      inEvent.mouse.button == MouseButton::BUTTON_LEFT) {
    mIsMouseLeftButtonDown = false;
  };
}

void GuiEngine::HandleMouseButtonEvent(const Event& inEvent) {
  // 마우스 버튼 다운 상태를 설정합니다.
  SetIsMouseLeftButtonDownState(inEvent);

  // 마우스 버튼 이벤트를 전달합니다.
  int mouse_pos_x = inEvent.mouse.x;
  int mouse_pos_y = inEvent.mouse.y;
  util::FindCollisionWidgetToDotAndExcute(mRootWidget, mouse_pos_x, mouse_pos_y,
                                          excute::MouseButtonExcute, inEvent);
}

void GuiEngine::RenderRootWidget() {
  // 위젯을 랜더링합니다.
  util::RenderWidget(mRootWidget);

  GraphicsDevice2d::sInstance->RenderTexture(
      mRootWidget->mTexture, mRootWidget->mPosition, mRootWidget->mPosition);
}

void GuiEngine::Reset(WidgetPtr& inRootWidget) {
  mRootWidget = inRootWidget;   // Root 위젯 또한 변경합니다.
  mFocusWidget = inRootWidget;  // 포커스 위젯으로 변경합니다.

  // 모든 캐쉬를 삭제합니다.
  mMouseHoveringCacheWidget.reset();
  mMouseClickCacheWidget.reset();
}
}  // namespace widget
}  // namespace sg_media
