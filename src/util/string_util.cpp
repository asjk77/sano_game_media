#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace util {

TexturePtr CreateStringTextureFromBaseFont(const char* inString,
                                           Color& inColor) {
    auto&& font = FontManager::sInstance->GetBaseFont();


    return font->CreateTextureString( inString, inColor );
}


void DrawString(int inPosX, int inPosY, const char* inString,
                const FontPtr& inFont, Color& inColor) {
  int string_texture_width = 0;
  int string_texture_height = 0;

  auto&& string_texture = inFont->CreateTextureString(inString, inColor);

  if (string_texture == nullptr) {
    return;
  }

  string_texture->GetInfo(string_texture_width, string_texture_height);

  RectEx texture_rect(0, 0, string_texture_width, string_texture_height);
  RectEx dest_rect(inPosX, inPosY, string_texture_width, string_texture_height);

  GraphicsDevice2d::sInstance->RenderTexture(string_texture, texture_rect,
                                             dest_rect);
}

void DrawString(int inPosX, int inPosY, const char* inString,
                const FontKey& inKey, Color& inColor) {
  auto&& font_ptr = FontManager::sInstance->GetFont(inKey);

  DrawString(inPosX, inPosY, inString, font_ptr, inColor);
}

void DrawString(int inPosX, int inPosY, const char* inString) {
  ColorEx black_color(0, 0, 0);

  auto&& base_font = FontManager::sInstance->GetBaseFont();
  DrawString(inPosX, inPosY, inString, base_font, black_color);
}


}  // namespace util
}  // namespace sg_media
