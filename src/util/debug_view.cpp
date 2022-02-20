#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace util {
std::unique_ptr<DebugView> DebugView::sInstance;

void DebugView::Render() {
  RenderLastLog(0, 0);
  RenderMousePos(0, 30);
  RenderTarget(0, 60);
}

void DebugView::Update() {
  mDebugTarget = widget::GuiEngine::sInstance->GetFocusWidget().get();
}
void DebugView::RenderMousePos(int inDrawPosX, int inDrawPosY) {
  int mouse_pos_x = 0;
  int mouse_pos_y = 0;
  platform::GetMousePos(&mouse_pos_x, &mouse_pos_y);
  std::string mouse_pos_string;
  mouse_pos_string = "X: " + std::to_string(mouse_pos_x) +
                     " Y: " + std::to_string(mouse_pos_y);

  DrawString(inDrawPosX, inDrawPosY, mouse_pos_string.c_str());
}

void DebugView::RenderTarget(int inDrawPosX, int inDrawPosY) {
  if (mDebugTarget == nullptr) return;
  uint32_t debuggable_class_id = mDebugTarget->GetDebuggableClassId();

  switch (debuggable_class_id) {
    case DebuggableClass::Widget:
      RenderWidgetInfo(ConvertDebuggable<widget::Widget>(mDebugTarget),
                       inDrawPosX, inDrawPosY);
      break;
    default:
      break;
  }
}
void DebugView::RenderWidgetInfo(widget::Widget* inWidget, int inDrawPosX,
                                 int inDrawPosY) {
  if (inWidget == nullptr) return;
  int y_offset_increment = 20;
  DrawString(inDrawPosX, inDrawPosY, ConvertDebuggableString(mDebugTarget));

  inDrawPosY = inDrawPosY + y_offset_increment;
  std::string widget_info;
  widget_info = " IsExpired: " + std::to_string(inWidget->GetIsExpiredRef());
  DrawString(inDrawPosX, inDrawPosY, widget_info.c_str());

  inDrawPosY = inDrawPosY + y_offset_increment;
  widget_info = "IsActivate: " + std::to_string(inWidget->IsActivate());
  DrawString(inDrawPosX, inDrawPosY, widget_info.c_str());

  inDrawPosY = inDrawPosY + y_offset_increment;
  widget_info = "Position: " + std::to_string(inWidget->GetPosX()) + " " +
                std::to_string(inWidget->GetPosY()) + " " +
                std::to_string(inWidget->GetWidth()) + " " + std::to_string(inWidget->GetHeight());

  DrawString(inDrawPosX, inDrawPosY, widget_info.c_str());
}
void DebugView::RenderLastLog(int inDrawPosX, int inDrawPosY) {
    auto&& last_log = gLogger.GetLastLog();

    DrawString( inDrawPosX, inDrawPosY, last_log.c_str() );
}
}  // namespace util
}  // namespace sg_media
