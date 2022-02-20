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
void RegisterWidgets() {
  // 기본적으로 GUI위젯에는 기본Root Widget이 존재합니다.
  widget::WidgetPtr& root_widget =
      widget::GuiEngine::sInstance->GetRootWidget();


  // 기본 위젯 생성 및 사용
  // 다음과 같이 위젯을 생성할수 있습니다.
  RectEx test_rect(10, 10, 200, 200);
  auto&& test_widget = widget::CreateWidget(test_rect);
  // 위젯을 생성한후 꼭 WidgetManager에 등록하여야 합니다.
  string widget_key = "MyTestWidget";
  widget::WidgetManager::sInstance->RegisterWidget(widget_key, test_widget);

  // 위와같이 생성하고 위젯을 등록하는 함수 가 존재합니다.
  auto&& test1 = widget::CreateWidgetAndRegister(RectEx(10, 10, 50, 50),
                                                 widget::WidgetKey("test1"));

  // 보드 위젯은 다음과 같이 생성할 수 있습니다.
  // 보드 위젯은 이미지가 필요합니다.
  // 이미지는 IMAGE_MANAGER의 기본 이미지를 사용하도록 하겠습니다.
  //
  auto& base_widget = ImageManager::sInstance->GetBaseImage();
  auto&& test_board_widget = widget::CreateBoardAndRegister(
      RectEx(10, 20, 50, 50), base_widget,
      widget::WidgetKey("test_widget"));

  // 현제 GUI_ENGINE 이 가르키는 루트노드에 새로운 자식 위젯을 포함시킵니다.
  root_widget->AddChildWidget(test_board_widget);

  // 버튼 위젯 의 생성
  auto&& button_widget = widget::CreateBaseButtonAndRegister(RectEx(100,100, 20,20), QuitFunction, widget::WidgetKey("test3"));
  root_widget->AddChildWidget( button_widget );

  // Static Widget UTF-8 한글은 정의되지 않습니다. 기본 폰트는 한글 폰트가 무겁기 때문에 한글 폰트를 지원하지 않습니다.
  // 이 라이브러리 사용자는 한글 폰트를 사용하고 싶다면 재정의 해야 합니다.
  auto&& static_widget = widget::CreateStaticWidget(300,100,"HelloMyString 안녕하세요");
  widget::WidgetKey static_widget_key("HelloMyString");
  widget::WidgetManager::sInstance->RegisterWidget(static_widget_key, static_widget );
  root_widget->AddChildWidget( static_widget );

}

ColorEx background_color(255, 255, 255);
ColorEx black_color(0, 0, 0);
RectEx my_rect(1, 1, 10, 10);

/**
 * @brief 랜더링합니다.
 */
void Render() {
  GraphicsDevice2d::sInstance->SetRenderColor(background_color);
  GraphicsDevice2d::sInstance->Clear();

  GraphicsDevice2d::sInstance->SetRenderColor(black_color);
  widget::GuiEngine::sInstance->RenderRootWidget();

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

  RegisterWidgets();
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
