// 효과음 및 청크 를 생성 및 실행합니다.
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


void KeyDownA() {
    gLogger.WriteLog(LogLevel::Debug, "KeyDownA");

}

void KeyDownS() {
    gLogger.WriteLog(LogLevel::Debug, "KeyDownS");
}
void KeyDownUp() {
    gLogger.WriteLog(LogLevel::Debug, "KeyDownUp");

}
void KeyDownDown() {
    gLogger.WriteLog(LogLevel::Debug, "KeyDownDown");
}

void Setup() {
    // 기본 최상위 위젯을 재정의합니다. 키보드 입력 가능한 위젯입니다.
    auto& window = WindowManager::sInstance->GetWindow();
    uint32_t window_width;
    uint32_t window_height;

    RectEx window_rect(0,0, window_width, window_height);

  widget::KeyInputable* key_inputable_widget_ptr;
  widget::WidgetPtr&& key_inputable_widget =
      widget::CreateKeyInputable(window_rect, key_inputable_widget_ptr);
  widget::WidgetManager::sInstance->RegisterWidget("key_inputable",
                                                   key_inputable_widget);

  // 해당 위젯의 키 입력 관리자를 얻습니다.
  auto& key_input_manager = key_inputable_widget_ptr->GetKeyInputManager();
  // 키들을 설정합니다.
  key_input_manager.SetKey(key::KeyCode::K_a, KeyDownA);
  key_input_manager.SetKey(key::KeyCode::K_s, KeyDownS);
  key_input_manager.SetKey(key::KeyCode::K_UP, KeyDownUp);
  key_input_manager.SetKey(key::KeyCode::K_DOWN, KeyDownDown);

  // GUIEngine을 리셋합니다.
  widget::GuiEngine::sInstance->Reset(key_inputable_widget);

  // MUSIC 및 Chunk 파일을 로드합니다.
  CreateMusicAndRegisterFromFile("chunk", "data/sound");
}
/**
 * @brief 랜더링합니다.
 */
void Render() {
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();

  util::DebugView::sInstance->Render();

  GraphicsDevice2d::sInstance->Present();
}
void Update() {
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
