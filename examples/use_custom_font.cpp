#include <iostream>
#include <sano_game_media.hpp>

using namespace sg_media;

/**
 * @brief 로그를 작성합니다.
 */
void PrintLog() {
  std::cout << " - Log - " << std::endl;
  auto &log_list = gLogger.GetLogList();
  for (auto &log : log_list) {
    std::cout << log << std::endl;
  }
}
bool IsRunning = true;
void QuitFunction() { IsRunning = false; }
platform::util::EventHandler gEventHandler;

ColorEx black_color(0, 0, 0);
FontPtr g_custom_font;
void Init() {
}
void Render() {
  FontKey font_key("n_sb");
  FontPtr dest_font = FontManager::sInstance->GetBaseFont();

  for (int i = 0; i < 500; i = i + 50) {
    util::DrawString(0, i, "한", dest_font, black_color);
    util::DrawString(50, i, "글", dest_font, black_color);
    util::DrawString(100, i, "공", dest_font, black_color);
    util::DrawString(150, i, "부", dest_font, black_color);
    util::DrawString(200, i, "합", dest_font, black_color);
  }
}
void Quit() { g_custom_font.reset(); }

int main(int argc, char *argv[]) {
  try {
    // 헬로우 월드라는 이름의 기본 윈도우를 생성합니다.
    sg_media::Init("init_and_release", 1024, 1024);
  } catch (Exception &e) {  // 만약 라이브러리 초기화 가 실패하였다면 예외를
                            // 발생합니다.
    std::cout << e.GetDesc() << std::endl;
    PrintLog();
    return -1;
  }
  //.. 코드를 작성합니다.
  gEventHandler.mQuitEventHandler = QuitFunction;
  Init();

  while (IsRunning) {
    platform::util::ProcessPollEventAdapter(gEventHandler);
    ColorEx background_color(255, 255, 255);
    GraphicsDevice2d::sInstance->SetRenderColor(background_color);
    GraphicsDevice2d::sInstance->Clear();
    Render();
    GraphicsDevice2d::sInstance->Present();
  }
  Quit();
  // 라이브러리를 활당 해제합니다.
  sg_media::Release();
  return 0;
}
