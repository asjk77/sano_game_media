#include <sano_game_media_pch.hpp>

namespace sg_media {
void Texture::Release() noexcept { if(mT) platform::DestoryTexture(mT); }
void Texture::GetInfo(int& outWidth, int& outHeight) {
  platform::QueryTexture(mT, &outWidth, &outHeight);
}

TexturePtr CreateTextureFromMemory(const char* inMemory, size_t inMemorySize) {
  // TODO
  // 주의 LoadTextureFromMemory 이 함수는 Graphicsdevice 를 요구해야함
  // 또한 CreateTextureFromMemory 함수에서 로그를 발생시켜야 되는데
  // platform::LoadTextureFromMemory에서 로그를 발생하고 있음
  return TexturePtr(
      new Texture(platform::LoadTextureFromMemory(inMemory, inMemorySize)));
}

TexturePtr CreateTexture(int inWidth, int inHeight) {
  const platform::RendererPtr renderer =
      GraphicsDevice2d::sInstance->GetRendererPtr();

  platform::TexturePtr t = platform::CreateTexture(renderer, inWidth, inHeight);

  if (t == nullptr) {
    LOG(LogLevel::Warn, ls::texture::TEXTURE_CREATION_ERROR_,
        platform::GetLastError());
  }

  return TexturePtr(new Texture(t));
}

TexturePtr CreateTextureFromFile(const char * inFileName) {
    util::ConstFileBuffer file_buffer( inFileName );


    if ( ! file_buffer.IsInit() ) {
        return TexturePtr( nullptr );
        
    }
    return CreateTextureFromMemory(file_buffer.GetMemory(), file_buffer.GetMemorySize() );

}
TexturePtr CreateBlendModeTexture( int inWidth, int inHeight ) {
    auto&& texture = CreateTexture( inWidth, inHeight );
    platform::SetTextureBlendMode(texture->GetTexture());
    return TexturePtr(texture);
}

}  // namespace sg_media
