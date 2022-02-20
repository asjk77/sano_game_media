#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {

WidgetPtr CreateStaticWidget(int inPosX, int inPosY, FontPtr& inFont,
                             const char* inString_UTF8, Color& inColor) {
    auto&& texture_ptr = inFont->CreateTextureString(inString_UTF8, inColor);
    if ( ! texture_ptr->IsInit() ) {
        return WidgetPtr( nullptr );
    }
    auto&& image_ptr = CreateImage( texture_ptr );
    RectEx position( inPosX, inPosY, image_ptr->GetFocusRect().mWidth, image_ptr->GetFocusRect().mHeight);


    return CreateBoard(position, image_ptr);
}

ColorEx gBaseColor(0,0,0);
WidgetPtr CreateStaticWidget(int inPosX, int inPosY,
                             const char* inString_UTF8) {
    auto&& base_font = FontManager::sInstance->GetBaseFont();
    return CreateStaticWidget( inPosX, inPosY, base_font, inString_UTF8, gBaseColor );
}
}  // namespace widget
}  // namespace sg_media
