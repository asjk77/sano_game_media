#include <sano_game_media_pch.hpp>

namespace sg_media {

std::unique_ptr<ImageManager> ImageManager::sInstance;

void ImageManager::StaticInit() {
  if (!TextureManager::sInstance) {
    LOG(LogLevel::Fatal,
        ls::image::IMAGE_MANAGER_INIT_ERROR_REQUIRED_TEXTURE_MANAGER);
    throw Exception(ls::image::IMAGE_MANAGER_INIT_ERROR);
  }

  // 기본 텍스처를 구합니다.
  TexturePtr& base_texture = TextureManager::sInstance->GetBaseTexture();
  ImagePtr&& base_image = CreateImage(base_texture);

  // 텍스처 관리자를 초기화 합니다.
  sInstance.reset(new ImageManager(base_image));
  LOG(LogLevel::Info, ls::image::IMAGE_MANAGER_INIT_COMPLETION);
}

ImagePtr& ImageManager::GetImage(ImageKey& inKey) {
  auto&& image_iter = mImageMap.find(inKey);

  if (image_iter == mImageMap.end()) {  // not found
    return mBaseImage;
  }
  return image_iter->second;
}

void ImageManager::RegisterImage(ImageKey& inKey, ImagePtr& inImage) {
  auto& dest_image = mImageMap[inKey];
  if (dest_image) {
    LOG(LogLevel::Warn, "중복된 이미지를 등록하였습니다. %s", inKey.c_str());
  }
  dest_image = inImage;
}

}  // namespace sg_media
