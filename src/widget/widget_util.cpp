#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget::util {

/**
 * @brief 점과 위젯의 충돌 부분을 찾고 그 위젯에 ExcuteFunction 을 실행합니다.
 *
 * @param inNext 다음 자식 위젯
 * @param inCurrentPosX 현제 마우스 위치X
 * @param inCurrentPosY 현제 마우스 위치Y
 * @param inParentPosX 기준점 절대좌표 X
 * @param inParentPosY 기준점 절대좌표 Y
 * @param inExcute ExcuteFunction
 * @param inEvent Excute 함수에 들어갈 Event
 * @return 만약 true 일경우 이미 처리된 Widget을 의미 합니다.
 */
bool FindCollisionWidgetToDotAndExcuteNext(const WidgetPtr& inNext,
                                           int inPointPosX, int inPointPosY,
                                           int inParentPosX, int inParentPosY,
                                           ExcuteFunction inExcute,
                                           const Event& inEvent) {
  if (inNext == nullptr) {
    return false;
  }
  auto next_widget = inNext;

  if (!next_widget->IsActivate()) return false;
  // 현제 사각형을 얻습니다.
  RectEx widget_current_rect(next_widget->GetPosX() + inParentPosX,
                             next_widget->GetPosY() + inParentPosY,
                             next_widget->GetWidth(), next_widget->GetHeight());
  // 만약 충돌되지 않을 경우
  if (!widget_current_rect.IsCollide(inPointPosX, inPointPosY)) {
    return false;
  }

  auto& children_widget = next_widget->GetChildrenWidget();

  for (auto& child_widget : children_widget) {
    if (child_widget == nullptr ) return false;
    auto&& child_widget_sp = child_widget;

    bool is_prosess = FindCollisionWidgetToDotAndExcuteNext(
        child_widget_sp, inPointPosX, inPointPosY, widget_current_rect.mX,
        widget_current_rect.mY, inExcute, inEvent);

    if (is_prosess) return true;
  }
  // OnClick
  inExcute(next_widget, inEvent);
  return true;
}

void FindCollisionWidgetToDotAndExcute(const WidgetPtr& inRoot, int inPointPosX,
                                       int inPointPosY, ExcuteFunction inExcute,
                                       const Event& inEvent) {
  if (inRoot == nullptr) return;
  FindCollisionWidgetToDotAndExcuteNext(inRoot, inPointPosX, inPointPosY,
                                        inRoot->GetPosX(), inRoot->GetPosY(),
                                        inExcute, inEvent);
}

/**
 * @brief 재귀적으로 위젯을 랜더링 합니다
 * 후위 순회로 랜더링합니다.
 * NOTE 랜더링할때 제일 아래에 있는 노드들 부터 순회합니다.
 * 노드의 부모가 IsExpired(만료된) 경우 (* 다시 그려야할 필요가 있을경우)
 * 자식 노드들을 다시 그리고 만료를 해제 시킵니다.
 *
 * @param inNext 다음 위젯
 * @param inParentPosX 위젯 부모 좌표X
 * @param inParentPosY 위젯 부모 좌표Y
 */
void RenderWidgetNext(const Widget::WidgetPtr& inNext, int inParentPosX,
                      int inParentPosY) {
  if (inNext == nullptr ) return;
  auto&& next_widget = inNext;

  if (!next_widget->IsActivate()) return;  // 활성화 되지 않았다면

  if (!next_widget->IsExpired())
    return;  // 현제 위젯이 다시 그릴 필요성이 없을 경우 return

  next_widget->GetIsExpiredRef() = false;

  auto& children_widget = next_widget->GetChildrenWidget();
  ClearTexture(next_widget->GetTexture());
  for (auto& child_widget : children_widget) {
    if (child_widget == nullptr) continue;
    auto&& child_widget_sp = child_widget; 
    RenderWidgetNext(child_widget_sp, child_widget_sp->GetPosX() + inParentPosX,
                     child_widget_sp->GetPosY() + inParentPosY);

    child_widget_sp->Render(next_widget->GetTexture());
  }
}

void RenderWidget(const WidgetPtr& inRoot) {
  RenderWidgetNext(inRoot, inRoot->GetPosX(), inRoot->GetPosY());
}

void ExpireRecursive(Widget* inNextParent) {
  if (inNextParent == nullptr) return;
  // true로 설정
  inNextParent->GetIsExpiredRef() = true;

  ExpireRecursive(inNextParent->GetParentWidget());
}
}  // namespace widget::util
}  // namespace sg_media
