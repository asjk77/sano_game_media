#ifndef SANO_GAME_MEDIA_SANO_GAME_MEDIA_PCH_HPP
#define SANO_GAME_MEDIA_SANO_GAME_MEDIA_PCH_HPP

#include <sano_game_media.hpp>

/**
 * @brief 로그를 작성합니다.
 *
 * @param loglevel 로그 레벨을 입력합니다.
 * @param ...
 *
 * @return 로그를 반환합니다.
 */
#define LOG(level, ...)                   \
  do {                                    \
    gLogger.SetTag("media");              \
    gLogger.WriteLog(level, __VA_ARGS__); \
    gLogger.SetTag(nullptr);              \
  } while (0)

/**
 * @brief 로그 스트링을 관리합니다.
 */
namespace ls {
inline const char* MODULE_INIT_COMPLETION = " 모듈 초기화 완료";
inline const char* MODULE_RELEASE_COMPLETION = "모듈 종료 완료";
inline const char* MODULE_NOT_INIT = "모듈이 초기화 되지 않았습니다.";
namespace platform {
inline const char* PLATFORM_INIT_ERROR = "플렛폼를 초기화 할 수 없습니다.";
inline const char* PLATFORM_INIT_COMPLETION = "플렛폼 초기화완료";
inline const char* PLATFORM_RELEASE_COMPLETION = "플렛폼 종료 완료";
inline const char* PLATFORM_TEXTURE_LOAD_ERROR_ = "텍스처를 로드 실패: %s";
inline const char* PLATFORM_FONT_LOAD_ERROR_ = "폰트 로드 실패: %s";
inline const char* MUSIC_LOAD_ERROR_ = "Music 을 로드 할 수 없습니다. %s";
inline const char* CHUNK_LOAD_ERROR_ = "Chunk 을 로드 할 수 없습니다. %s";

}  // namespace platform
namespace window {
inline const char* WINDOW_MANAGER_INIT_ERROR =
    "윈도우 관리자를 초기화 할 수 없습니다.";
inline const char* WINDOW_MANAGER_FAILED_TO_CREATE_WINDOW =
    "윈도우 생성에 실패하였습니다.";
inline const char* WINDOW_MANAGER_NOT_INIT =
    "윈도우 관리자가 초기화 되지 않았습니다.";
inline const char* WINDOW_MANAGER_INIT_COMPLETION = "윈도우 관리자 초기화 완료";

}  // namespace window
namespace texture {
inline const char* TEXTURE_MANAGER_INIT_ERROR =
    "텍스처 관리자를 초기화 할 수 없습니다.";
inline const char* TEXTURE_MANAGER_INIT_ERROR_BASE_TEXTURE =
    "기본 텍스처를 초기화 할 수 없습니다.";
inline const char* TEXTURE_MANAGER_INIT_ERROR_REQUIRED_GRAPHICS_DEVICE_2D =
    "텍스처 관리자를 초기화 하기 위해서는 그래픽 장치2D 가 필요합니다.";
inline const char* TEXTURE_MANAGER_INIT_COMPLETION =
    "텍스처 관리자 초기화 완료";
inline const char* TEXTURE_MANAGER_NOT_INIT =
    "텍스처 관리자가 초기화 되지 않았습니다.";

inline const char* TEXTURE_CREATION_ERROR_ = "텍스처가 생성되지 않았습니다. %s";
}  // namespace texture

namespace image {
inline const char* IMAGE_MANAGER_INIT_ERROR =
    "이미지 관리자를 초기화 할 수 없습니다.";
inline const char* IMAGE_MANAGER_INIT_ERROR_REQUIRED_TEXTURE_MANAGER =
    "이미지 관지라를 초기화 하기 위해서는 텍스처 관리자 가 필요합니다.";
inline const char* IMAGE_MANAGER_INIT_COMPLETION = "이미지 관리자 초기화 완료";
inline const char* IMAGE_MANAGER_NOT_INIT =
    "이미지 관리자가 초기화 되지 않았습니다.";
}  // namespace image
namespace widget {
inline const char* GUI_ENGINE_INIT_ERROR = "GUI 엔진을 초기화 할 수 없습니다.";
inline const char* GUI_ENGINE_INIT_ERROR_REQUIRED_Wi =
    "GUI 엔진을 초기화 할 수 없습니다.";
inline const char* GUI_ENGINE_INIT_COMPLETION = "GUI 엔진 초기화 완료";
inline const char* GUI_ENGINE_NOT_INIT = "GUI 엔진 초기화 되지 않았습니다.";
inline const char* GUI_ENGINE_INIT_ERROR_REQUIRED_WIDGET_MANAGER =
    "GUI 엔진을 초기화 하기 위해서는 위젯 관리자가 필요합니다.";

inline const char* WIDGET_MANAGER_INIT_ERROR =
    "위젯 관리자를 초기화 할 수 없습니다.";
inline const char* WIDGET_MANAGER_INIT_COMPLETION = "위젯 관리자 초기화 완료";
inline const char* WIDGET_MANAGER_WIDGET_DUPLICATE_REGISTER_ =
    "위젯을 중복하여 저장하였습니다.";

inline const char* WIDGET_TEXTURE_CREATION_ERROR = "위젯 텍스처 생성 에러";
}  // namespace widget

inline const char* GRAPHICS_DEVICE2D_INIT_ERROR =
    "GrpahicsDevice2d 초기화 할 수 없습니다.";
inline const char* GRAPHICS_DEVICE2D_INIT_ERROR_REQUIRED_WINDOW_MANAGER =
    " GraphicsDevice2를 초기화 하기 위해서는 윈도우 관리자가 필요합니다.";
inline const char* GRAPHICS_DEVICE2D_INIT_COMPLETION =
    "GraphicsDevice2d 초기화 완료";
inline const char* GRAPHICS_DEVICE2D_NOT_INIT =
    "GraphicsDevice2d 초기화 되지 않았습니다.";

inline const char* FONT_MANAGER_INIT_ERROR =
    "FontManager를 초기화 할 수 없습니다.";
inline const char* FONT_MANAGER_INIT_ERROR_BASE_FONT =
    "기본 폰트를 초기화 할 수 없습니다.";
inline const char* FONT_MANAGER_INIT_COMPLETION =
    "GraphicsDevice2d 초기화 완료";

inline const char* FONT_CREATION_ERROR = "폰트를 생성할 수 없습니다.";


inline const char* AUDIO_DEVICE_INIT_COMPLETION = "AudioDevice를 초기화 완료.";
inline const char* AUDIO_DEVICE_INIT_ERROR =
    "AudioDevice를 초기화 할 수 없습니다.";
inline const char* AUDIO_DEVICE_INIT_ERROR_ = "Audio 를 열수 없습니다. %s";

}  // namespace ls

#endif /* SANO_GAME_MEDIA_SANO_GAME_MEDIA_PCH_HPP */
