#include <filesystem>
#include <fstream>
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

TextureKey loaded_texture_key = "loaded_texture";
FontPtr loaded_font;
ColorEx black_color(0, 0, 0);

void Setup() {
  // 파일에서 텍스처를 로드합니다.
  auto &&loaded_texture = CreateTextureFromFile(
      "data/image/"
      "593d17a58e88c4305f8f8bd330a288250d0942f39f414ee9eaaac3dcbc40e8d00a9e538a"
      "c3f5c9eec1bb20936784d6b0f2a250ea57d13f1f1c96cd91c0def358da3e8d9ce83be6da"
      "41ade0e0b470a16f99519fd893dea2f2c8ff430b060b40dee59fa25823af03ba9a08b4f9"
      "e3571cc5.jpeg");
  if (loaded_texture) {
    gLogger.WriteLog(LogLevel::Debug, "test.png success");
    TextureManager::sInstance->RegisterTexture(loaded_texture_key,
                                               loaded_texture);
  } else {
    gLogger.WriteLog(LogLevel::Debug, "test.png fall");
  }

  loaded_font = CreateFontFromFile("data/font/NanumGothicBold.ttf", 20);
  if (loaded_font) {
    auto &&texture_string =
        loaded_font->CreateTextureString("AFDSDFA", black_color);

    int width = 0;
    int height = 0;
    texture_string->GetInfo(width, height);
    gLogger.WriteLog(LogLevel::Debug, "base_font Good %d %d", width, height);

  }
}

void Render() {
  ColorEx background_color(255, 255, 255);
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();
  auto &&loaded_texture =
      TextureManager::sInstance->GetTexture(loaded_texture_key);
  if (loaded_texture) {
    int width;
    int height;
    loaded_texture->GetInfo(width, height);
    RectEx texture_rect(0, 0, width, height);

    RectEx draw_rect(100, 100, 300, 300);
    GraphicsDevice2d::sInstance->RenderTexture(loaded_texture, texture_rect,
                                               draw_rect);
  } else {}

  GraphicsDevice2d::sInstance->Present();
}


void Quit() { loaded_font.reset(); }
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

  Setup();
  //
  while (IsRunning) {
    platform::util::ProcessPollEventAdapter(gEventHandler);
    Render();
  }
  // 라이브러리를 활당 해제합니다.
  Quit();
  sg_media::Release();
  return 0;
}
