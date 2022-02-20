// use_widget_s
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

/**
 * @brief 위젯을 등록합니다.
 */
ColorEx background_color(255, 255, 255);
ColorEx black_color(0, 0, 0);
RectEx my_rect(1, 1, 10, 10);

ImageList image_list;
void Setup() {
  TexturePtr target_texture =
      FontManager::sInstance->GetBaseFont()->CreateTextureString("Hello1world",
                                                                 black_color);

  /**
   * @brief 텍스처로부터 이미지를 생성합니다.
   *
   * @param target_texture 타겟 텍스처로부터
   * @param 10 이미지의 너비
   * @param 10 이미지의 높이
   * @param 0 시작 오프셋x
   * @param 0 시작 오프셋y
   * @param 40 총 40개의 이미지를 생성합니다.
   * @param 20 가로 Cell 수는 20 개입니다.
   * @param 2 세로 Cell 수는 30 개 입니다.
   *
   * @return
   */
  ImageLoader loader(target_texture, 10, 10, 0, 0, 40, 20, 2);

  loader.LoadImageList(image_list);
  // 이미지를 로드하였습니다.
}

void RenderImageList(const ImageList& inImageList) {
  uint32_t offset_x = 0;
  uint32_t offset_y = 0;
  uint32_t width = 16;
  uint32_t height = 16;

  for (auto& image : inImageList) {
    RectEx draw_rect(offset_x, offset_y, width, height);
    image->Render(draw_rect);
    offset_x = offset_x + width;
  }
}
/**
 * @brief 랜더링합니다.
 */
void Render() {
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();

  RenderImageList(image_list);
  // 위젯을 랜더링합니다.
  widget::GuiEngine::sInstance->RenderRootWidget();
  GraphicsDevice2d::sInstance->Present();
}
void Update() {}

int main(int argc, char* argv[]) {
  try {
    // 헬로우 월드라는 이름의 기본 윈도우를 생성합니다.
    sg_media::Init("image_loader", 1024, 1024);
  } catch (Exception& e) {  // 만약 라이브러리 초기화 가 실패하였다면 예외를
                            // 발생합니다.
    std::cout << e.GetDesc() << std::endl;
    PrintLog();
    return -1;
  }

  //.. 코드를 작성합니다.
  gEventHandler.mQuitEventHandler = QuitFunction;
  Setup();

  while (IsRunning) {
    platform::util::ProcessPollEventAdapter(gEventHandler);
    Render();
    Update();
  }
  // 라이브러리를 활당 해제합니다.
  sg_media::Release();
  return 0;
}
