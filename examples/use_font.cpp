#include <iostream>
#include <sano_game_media.hpp>

using namespace sg_media;

/**
 * @brief 로그를 작성합니다.
 */
void PrintLog() {
  std::cout << " - Log - " << std::endl;
  auto& log_list = gLogger.GetLogList();
  for (auto& log : log_list) {
    std::cout << log << std::endl;
  }
}
bool IsRunning = true;

/**
 * @brief 종료 함수를 만듭니다.
 */
void QuitFunction() { IsRunning = false; }
platform::util::EventHandler gEventHandler;

ColorEx background_color(255, 255, 255);
ColorEx black_color(0, 0, 0);
RectEx my_rect(1, 1, 10, 10);

void RenderTexture() {
    // 텍스처를 랜더링합니다.
}
/**
 * @brief 랜더링합니다.
 */
void Render() {
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();

  GraphicsDevice2d::sInstance->SetRenderColor(black_color);
  RenderTexture();
  GraphicsDevice2d::sInstance->Present();
}

int main(int argc, char* argv[]) {
  try {
    // 헬로우 월드라는 이름의 기본 윈도우를 생성합니다.
    sg_media::Init("use_widget", 1024, 1024);
  } catch (Exception& e) {  // 만약 라이브러리 초기화 가 실패하였다면 예외를
                            // 발생합니다.
    std::cout << e.GetDesc() << std::endl;
    PrintLog();
    return -1;
  }

  //.. 코드를 작성합니다.
  gEventHandler.mQuitEventHandler = QuitFunction;

  while (IsRunning) {
    platform::util::ProcessPollEventAdapter(gEventHandler);
    Render();
  }
  // 라이브러리를 활당 해제합니다.
  sg_media::Release();
  return 0;
}
