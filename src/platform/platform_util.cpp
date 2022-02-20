#include <SDL.h>

#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace platform {
namespace util {
namespace {
typedef sg_media::widget::Event Event;
typedef sg_media::widget::EventType EventType;

/**
 * @brief 마우스 모션 이벤트를 변환합니다.
 *
 */
void ConvertMouseMotionEvent(const SDL_Event& inPlatformEvent,
                             Event& outWidgetEvent) {
  outWidgetEvent.mouse_motion.type = EventType::MOUSE_MOTION;
  outWidgetEvent.mouse_motion.x = inPlatformEvent.motion.x;
  outWidgetEvent.mouse_motion.y = inPlatformEvent.motion.y;
  outWidgetEvent.mouse_motion.rel_x = inPlatformEvent.motion.xrel;
  outWidgetEvent.mouse_motion.rel_y = inPlatformEvent.motion.yrel;
}

/**
 * @brief 마우스 버튼 이벤트를 변환합니다.
 */
void ConvertMouseButtonEvent(const SDL_Event& inPlatformEvent,
                             Event& outWidgetEvent) {
  outWidgetEvent.mouse.x = inPlatformEvent.button.x;
  outWidgetEvent.mouse.y = inPlatformEvent.button.y;

  typedef sg_media::widget::MouseButton MouseButton;

  switch (inPlatformEvent.button.button) {
    case SDL_BUTTON_LEFT:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_LEFT;
      break;
    case SDL_BUTTON_RIGHT:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_RIGHT;
      break;
    case SDL_BUTTON_MIDDLE:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_MIDDLE;
      break;
    case SDL_BUTTON_X1:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_X1;
      break;
    case SDL_BUTTON_X2:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_X2;
      break;
    default:
      outWidgetEvent.mouse.button = MouseButton::BUTTON_LEFT;
      break;
  }
}

/**
 * @brief 마우스 버튼 DOWN/UP 이벤트를 변환합니다.
 */
void ConvertMouseButtonDownEvent(const SDL_Event& inPlatformEvent,
                                 Event& outWidgetEvent) {
  outWidgetEvent.mouse.type = EventType::MOUSE_BUTTON_DOWN;
  ConvertMouseButtonEvent(inPlatformEvent, outWidgetEvent);
}

void ConvertMouseButtonUpEvent(const SDL_Event& inPlatformEvent,
                               Event& outWidgetEvent) {
  outWidgetEvent.mouse.type = EventType::MOUSE_BUTTON_UP;
  ConvertMouseButtonEvent(inPlatformEvent, outWidgetEvent);
}

void ConvertKeyEvent(const SDL_Event& inPlatformEvent, Event& outWidgetEvent) {
  // SDL 에서의 키값과 platform에서의 키값이 다를 수 있습니다.
  outWidgetEvent.keyboard.key_code =
      (key::KeyCode)inPlatformEvent.key.keysym.sym;
  outWidgetEvent.keyboard.scan_code =
      (key::Scancode)inPlatformEvent.key.keysym.scancode;
}

void ConvertKeyDownEvent(const SDL_Event& inPlatformEvent,
                         Event& outWidgetEvent) {
  outWidgetEvent.mouse.type = EventType::KEYBOARD_KEY_DOWN;
  ConvertKeyEvent(inPlatformEvent, outWidgetEvent);
}
void ConvertKeyUpEvent(const SDL_Event& inPlatformEvent,
                       Event& outWidgetEvent) {
  outWidgetEvent.mouse.type = EventType::KEYBOARD_KEY_UP;
  ConvertKeyEvent(inPlatformEvent, outWidgetEvent);
}

//////////////////////////////////////////////////////////////////////
/**
 * @brief platform의 이벤트를 widget이벤트로 변환합니다.
 *
 * @param inPlatformEvent 플렛폼 이벤트
 * @param outWidgetEvent 위젯 이벤트
 */
//////////////////////////////////////////////////////////////////////
void ConvertPlatformEventToWidgetEvent(const SDL_Event& inPlatformEvent,
                                       Event& outWidgetEvent) {
  switch (inPlatformEvent.type) {
    case SDL_MOUSEMOTION:
      ConvertMouseMotionEvent(inPlatformEvent, outWidgetEvent);
      break;
    case SDL_MOUSEBUTTONDOWN:
      ConvertMouseButtonDownEvent(inPlatformEvent, outWidgetEvent);
      break;
    case SDL_MOUSEBUTTONUP:
      ConvertMouseButtonUpEvent(inPlatformEvent, outWidgetEvent);
      break;
    case SDL_KEYDOWN:
      ConvertKeyDownEvent(inPlatformEvent, outWidgetEvent);
      break;
    case SDL_KEYUP:
      ConvertKeyUpEvent(inPlatformEvent, outWidgetEvent);
      break;
    default:
      outWidgetEvent.type = EventType::UNKNOWN;
      break;
  }
}

typedef int (*EventProcessMethod)(SDL_Event*);

int WaitEvent(SDL_Event* outEvent) { return SDL_WaitEvent(outEvent); }

int PollEvent(SDL_Event* outEvent) { return SDL_PollEvent(outEvent); }

}  // namespace

void ProcessEventLogic(EventProcessMethod inMethod,
                       const EventHandler& inEventHandler) noexcept {
  if (inMethod == nullptr) return;

  SDL_Event platform_event;
  Event widget_event;
  while (inMethod(&platform_event)) {
    if (platform_event.type == SDL_QUIT) {
       inEventHandler.mQuitEventHandler();
      return;
    }

    ConvertPlatformEventToWidgetEvent(platform_event, widget_event);
    sg_media::widget::GuiEngine::sInstance->HandleEvent(widget_event);
  }
}

void ProcessPollEventAdapter(const EventHandler& inEventHandler) noexcept {
  ProcessEventLogic(PollEvent, inEventHandler);
}
void ProcessWaitEventAdapter(const EventHandler& inEventHandler) noexcept {
  ProcessEventLogic(WaitEvent, inEventHandler);
}

}  // namespace util
}  // namespace platform
}  // namespace sg_media
