#include <iostream>
#include <sano_game_media.hpp>

using namespace sg_media;

/**
 * @brief 로그를 작성합니다. 
 */
void PrintLog() {
    std::cout << " - Log - " << std::endl;
    auto& log_list = gLogger.GetLogList();
    for( auto & log : log_list ) {
        std::cout << log << std::endl;
    }
}
bool IsRunning = true;
void QuitFunction() {
    IsRunning = false;
}
platform::util::EventHandler gEventHandler;

void Setup() {
    // moveable 위젯
    RectEx rect_ex(30, 30, 100,100 );
    auto&& moveable_widget = widget::CreateMoveable(rect_ex);
    widget::WidgetManager::sInstance->RegisterWidget("moveable", moveable_widget);

    auto root_widget = widget::GuiEngine::sInstance->GetRootWidget();
    root_widget->AddChildWidget( moveable_widget );
}

ColorEx black_color(0,0,0);
ColorEx white_color(255,255,255);
void Render() {
    GraphicsDevice2d::sInstance->SetRenderColor(white_color);
    GraphicsDevice2d::sInstance->Clear();

    util::DebugView::sInstance->Render(); // 디버그 뷰 를 랜더링 합니다.
    widget::GuiEngine::sInstance->RenderRootWidget();

    GraphicsDevice2d::sInstance->Present();
}

void Update() {
    util::DebugView::sInstance->Update();
}
int main(int argc, char *argv[]) {
  try {
    // 헬로우 월드라는 이름의 기본 윈도우를 생성합니다.
    sg_media::Init("use_moveable_widget", 1024, 1024);
  } catch (Exception &e) { // 만약 라이브러리 초기화 가 실패하였다면 예외를 발생합니다.
    std::cout << e.GetDesc() << std::endl;
    PrintLog();
    return -1;
  }
  //.. 코드를 작성합니다.
  gEventHandler.mQuitEventHandler = QuitFunction;

  Setup();

  while ( IsRunning ) {
      platform::util::ProcessPollEventAdapter(gEventHandler);
      // platform::util::ProcessWaitEventAdapter(gEventHandler);
      Render();
      Update();
  }
  // 라이브러리를 활당 해제합니다.
  sg_media::Release();
  return 0;
}
