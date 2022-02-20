#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {

void Moveable::HandleEvent(const Event& inEvent) {
  switch (inEvent.type) {
    case EventType::MOUSE_MOTION:
      HandleMouseMotionEvent(inEvent);
      break;
    default:
      break;
  }

}
void Moveable::HandleMouseMotionEvent(const Event& inEvent) {
  bool& is_mouse_left_button_down =
      GuiEngine::sInstance->GetIsMouseLeftButtonDownRef();
  if (! mIsMouseHover) { 
      return;
    // 만약 마우스가 호버되고 마우스 버튼이 다운되었으면 이동합니다.
  }
  if (! is_mouse_left_button_down ) {
      return;
  }
    MoveTarget(inEvent.mouse_motion.rel_x, inEvent.mouse_motion.rel_y);
}

void Moveable::MoveTarget(int inRelXPos, int inRelYPos) {
  if (mTargetWidget) {
    mTargetWidget->Move(inRelXPos, inRelYPos);
    Expire();  // 해당 위젯을 만료 시킴
  }
}

WidgetPtr CreateMoveable(const Rect& inPosition, Widget* inTarget) {
  return WidgetPtr(new Moveable(inPosition, inTarget));
}
WidgetPtr CreateMoveable(const Rect& inPosition) {
  return WidgetPtr(new Moveable(inPosition));
}
}  // namespace widget
}  // namespace sg_media
