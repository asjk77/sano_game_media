#include <sano_game_media_pch.hpp>

extern unsigned char data_image_base_texture_png[];
extern unsigned int data_image_base_texture_png_len;

namespace sg_media {

std::unique_ptr<TextureManager> TextureManager::sInstance;

void TextureManager::StaticInit() {
  // TODO 기본 텍스처를 생성하여 기본 윈도우를 초기화 합니다.

  if (! GraphicsDevice2d::sInstance) {
    LOG(LogLevel::Fatal,
        ls::texture::TEXTURE_MANAGER_INIT_ERROR_REQUIRED_GRAPHICS_DEVICE_2D);
    throw Exception(ls::texture::TEXTURE_MANAGER_INIT_ERROR);
  }

  TexturePtr&& base_texture = CreateTextureFromMemory(
      (const char*)data_image_base_texture_png, data_image_base_texture_png_len);

  if ( ! base_texture->IsInit()) {
    LOG(LogLevel::Fatal, ls::texture::TEXTURE_MANAGER_INIT_ERROR_BASE_TEXTURE);
    throw Exception(ls::texture::TEXTURE_MANAGER_INIT_ERROR);
  }
  sInstance.reset(new TextureManager(base_texture));
  LOG(LogLevel::Info, ls::texture::TEXTURE_MANAGER_INIT_COMPLETION);
}

TexturePtr& TextureManager::GetTexture(TextureKey& inKey) {
  auto&& texture_iter = mTextureMap.find(inKey);

  if (texture_iter == mTextureMap.end()) {  // not found
    return mBaseTexture;
  }
  return texture_iter->second;
}
void TextureManager::RegisterTexture(TextureKey& inKey, TexturePtr& inTexture) {
  auto& dest_texture = mTextureMap[inKey];
  if (dest_texture) {
    LOG(LogLevel::Warn, "중복된 텍스처를 등록하였습니다. %s", inKey.c_str());
  }
  dest_texture = inTexture;
}
}  // namespace sg_media
