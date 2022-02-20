#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {
void KeyInputable::HandleEvent(const Event& inEvent) {
  if (inEvent.type != EventType::KEYBOARD_KEY_DOWN) {
    return;
  }
  // 키 코드를 처리합니다.
  ProcessKeyDown(inEvent);
}

void KeyInputable::ProcessKeyDown(const Event& inEvent) {
    // 실제 키코드를 실행합니다.
    mKeyInputManager.DoAction( inEvent.keyboard.key_code );
}

WidgetPtr CreateWindowSizeKeyInputable(KeyInputable*& outNewWidget ) {
    WindowPtr& win = WindowManager::sInstance->GetWindow();
    int w;
    int h;
    win->GetWindowSize( w, h);
    RectEx window_rect(0,0, w, h);
    return CreateKeyInputable(window_rect, outNewWidget );
}

}  // namespace widget
}  // namespace sg_media
