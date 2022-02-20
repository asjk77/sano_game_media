#ifndef SANO_GAME_MEDIA_SANO_GAME_MEDIA_HPP
#define SANO_GAME_MEDIA_SANO_GAME_MEDIA_HPP

#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <array>

#include <sano_game_global.hpp>

#ifndef sg_media
#define sg_media sano::game::media
#endif  // sg_media

namespace sg_media {
#include "common/types.hpp"

#include "common/key_code.hpp"
#include "common/key_input_manager.hpp"

// ! platform 은 자체적으로 이름공간을 설정함
#include "platform/platform.hpp"
#include "platform/platform_util.hpp"

#include "common/texture.hpp"
#include "common/texture_manager.hpp"
#include "common/font_manager.hpp"
#include "common/graphics_device2d.hpp"
#include "common/window_manager.hpp"

#include "image/image.hpp"
#include "image/image_sprite_animation.hpp"
#include "image/image_loader.hpp"
#include "image/image_manager.hpp"

namespace util {
#include "util/debuggable.hpp"
#include "util/debug_view.hpp"
#include "util/log_listener.hpp"
#include "util/string_util.hpp"
#include "util/file_buffer.hpp"
}

namespace widget {
#include "widget/event.hpp"
#include "widget/types.hpp"
#include "widget/widget_class.hpp"
#include "widget/widget.hpp"
#include "widget/board.hpp"
#include "widget/button.hpp"
#include "widget/static.hpp"
#include "widget/key_inputable.hpp"
#include "widget/moveable.hpp"
#include "widget/scrollable.hpp"

#include "widget/widget_util.hpp"
#include "widget/widget_manager.hpp"
#include "widget/gui_engine.hpp"
}  // namespace widget

#include "common/sound.hpp"
#include "common/sound_registry.hpp"

#include "common/audio_device.hpp"

/**
 * @brief 라이브러리를 초기화합니다.
 *
 * @param inWindowTitle 기본 윈도우 제목
 * @param inWidth 기본 윈도우의 너비
 * @param inHeight 기본 윈도우의 높이
 */
void Init( const char * inWindowTitle, const int inWidth, const int inHeight );

/**
 * @brief 라이브러리를 파괴합니다.
 */
void Release();
}  // namespace sg_media

#endif /* SANO_GAME_MEDIA_SANO_GAME_MEDIA_HPP */
