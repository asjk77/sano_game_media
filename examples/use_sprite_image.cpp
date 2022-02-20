// 스플라이트 이미지를 사용법
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

ImageKey test_image_key( "test_image" );
void Setup() {
    FontPtr& base_font = FontManager::sInstance->GetBaseFont();


    TexturePtr test_font_texture = base_font->CreateTextureString("HELLO WORLD", black_color );
    // Create 후에는 반드시 TextureManager에 등록을 해줘야 합니다. shared_ptr 특성상 관리자 객체에 저장해야합니다..
    RectList rect_list;
    rect_list.push_back(RectEx(0,0, 20, 20));
    rect_list.push_back(RectEx(20,0, 20, 20));
    rect_list.push_back(RectEx(40,0, 20, 20));
    auto&& image_sprite_animation = CreateImageSpriteAnimation(test_font_texture, rect_list, 200);
    ImageManager::sInstance->RegisterImage( test_image_key, image_sprite_animation );
}
/**
 * @brief 랜더링합니다.
 */
void Render() {
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();

  RectEx dest_rect(0,0,20,20);
    ImageManager::sInstance->GetImage(test_image_key)->Render(dest_rect);

  GraphicsDevice2d::sInstance->Present();
}
void Update() {
    ImageManager::sInstance->GetImage(test_image_key)->Update();
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
