#include <sano_game_media_pch.hpp>

namespace sg_media {

void Window::Release() noexcept {
  // 현제 윈도우가 존재할시 윈도우를 삭제합니다.
  if (mW) {
    platform::DestroyWindow(mW);
  }
}
void Window::GetWindowSize(int& outWidth, int& outHeight) {
    platform::GetWindowSize(mW, &outWidth, &outHeight);
}

WindowPtr CreateWindow(const char* inTitle, const int inWidth,
                    const int inHeight) {
  platform::WindowPtr new_window =
      platform::CreateWindow(inTitle, 0, 0, inWidth, inHeight);
  if (!new_window) {
      LOG(LogLevel::Warn, platform::GetLastError());
  }
  return WindowPtr( new Window(new_window) ); // 새로운 윈도우를 반환합니다.
}

std::unique_ptr< WindowManager > WindowManager::sInstance;

void WindowManager::StaticInit( const char * inTitle, const int inWidth, const int inHeight ) {
    WindowPtr && new_window = CreateWindow(inTitle, inWidth, inHeight);

    if ( new_window->GetWindow() == nullptr ) {
        LOG(LogLevel::Fatal, ls::window::WINDOW_MANAGER_FAILED_TO_CREATE_WINDOW );
        throw Exception(ls::window::WINDOW_MANAGER_INIT_ERROR);
    }
    sInstance.reset( new WindowManager( new_window ) );
    LOG(LogLevel::Info, ls::window::WINDOW_MANAGER_INIT_COMPLETION);
}

}  // namespace sg_media
