#include <SDL.h>

#include <sano_game_media_pch.hpp>
namespace sg_media {
void Init( const char * inWindowTitle, const int inWidth, const int inHeight ) {
  // 중복되어 Init되지 않습니다.
  SANO_PROCESS_ONLY_ONCE();

  // sg_media 를 초기화 합니다.
  platform::Init();

  WindowManager::StaticInit( inWindowTitle, inWidth, inHeight );
  GraphicsDevice2d::StaticInit();
  TextureManager::StaticInit();
  ImageManager::StaticInit();
  FontManager::StaticInit();

  AudioDevice::StaticInit();
  SoundRegistry::StaticInit();

  widget::WidgetManager::StaticInit();
  widget::GuiEngine::StaticInit();

  util::DebugView::StaticInit();
  LOG(LogLevel::Info, ls::MODULE_INIT_COMPLETION);
}


void Release() {
  // 중복되어 Release되지 않습니다.
  SANO_PROCESS_ONLY_ONCE();
  // 초기화 의 역순으로 종료합니다.
  util::DebugView::StaticRelease();

  widget::GuiEngine::StaticRelease();
  widget::WidgetManager::StaticRelease();

  SoundRegistry::StaticRelease();
  AudioDevice::StaticRelease();

  FontManager::StaticRelease();
  ImageManager::StaticRelease();
  TextureManager::StaticRelease();
  GraphicsDevice2d::StaticRelease();
  WindowManager::StaticRelease();

  // sg_release를 종료합니다.
  platform::Release();

  // 각 관리자는 스마트 포인터 기반으로 되어서 자동으로 파괴됩니다.
  LOG(LogLevel::Info, ls::MODULE_RELEASE_COMPLETION);

}

}  // namespace sg_media
