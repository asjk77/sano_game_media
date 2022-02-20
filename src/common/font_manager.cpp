#include <sano_game_media_pch.hpp>
#include <fstream>

extern unsigned char data_font_pc_senior_pcsenior_ttf[];
extern unsigned int data_font_pc_senior_pcsenior_ttf_len;

namespace sg_media {
void Font::Release() { platform::DestoryFont(mF); }

TexturePtr Font::CreateTextureString( const char * inString_UTF8, Color& inColor ) {
    auto&& renderer_ptr = GraphicsDevice2d::sInstance->GetRendererPtr();
    auto&& texture_ptr = platform::RenderTextFromFontUTF8_Solid(renderer_ptr, mF, inString_UTF8, inColor);
    return TexturePtr( new Texture(texture_ptr) );
}

FontPtr CreateFontFromMemory(const char* inMemory, size_t inMemorySize,
                             size_t inFontSize) {
  auto&& font_ptr =
      platform::LoadFontFromMemory(inMemory, inMemorySize, inFontSize);

  return FontPtr(new Font(font_ptr));
}

FontPtr CreateFontFromFile(const char * inFileName, size_t inFontSize) { 

    auto&& font_ptr = platform::LoadFontFromFile( inFileName, inFontSize );
    if ( font_ptr == nullptr ) {
        LOG( LogLevel::Warn, ls::FONT_CREATION_ERROR );
        return FontPtr( nullptr );
    }
    return FontPtr( new Font( font_ptr ));
}

std::unique_ptr<FontManager> FontManager::sInstance;

void FontManager::StaticInit() {
  auto&& base_font =
      CreateFontFromMemory((const char*)data_font_pc_senior_pcsenior_ttf,
                           data_font_pc_senior_pcsenior_ttf_len, 10);

  // auto&& nanum_sb= CreateFontFromFile("data/font/NanumSquareB.ttf", 20);

  if (! base_font->IsInit()) {
      LOG(LogLevel::Fatal, ls::FONT_MANAGER_INIT_ERROR_BASE_FONT);
      throw Exception(ls::FONT_MANAGER_INIT_ERROR);
  }

  sInstance.reset(new FontManager(base_font));
  LOG(LogLevel::Info, ls::FONT_MANAGER_INIT_COMPLETION);
  
}

void FontManager::RegisterFont( const FontKey& inKey, FontPtr& inFont ) {
    auto& dest_font = mFonts[ inKey ]; 

    if ( dest_font ) {
        LOG(LogLevel::Warn, "중복된 폰트가 등록되었습니다. %s", inKey.c_str());
    }
    dest_font = inFont;
}

const FontPtr& FontManager::GetFont( const FontKey& inKey ) const {
    auto&& font_iter = mFonts.find( inKey );
    if ( font_iter == mFonts.end() ) {
        return mBaseFont;
    }
    return font_iter->second;
}

void CreateFontAndRegisterFromFile(FontKey&& inKey, std::string&& inFileName,
                                   size_t inFontSize)  {
    auto&& font = CreateFontFromFile( inFileName.c_str(), inFontSize );

    if ( font == nullptr ) {
        LOG(LogLevel::Warn, "폰트 등록 실패" );
        return;
    }
    FontManager::sInstance->RegisterFont(inKey, font);
    LOG(LogLevel::Info, "새로운 폰트 등록 %s",  inKey.c_str());
}

void SetBaseFontFromKey( FontKey&& inKey ) {
    auto& font = FontManager::sInstance->GetFont( inKey );
    if ( font == nullptr ) {
        LOG( LogLevel::Error, "기본 폰트 변경 실패" );
    }
    FontManager::sInstance->SetBaseFont( font );
    LOG(LogLevel::Info, "기본 폰트가 변경되었습니다. %s",  inKey.c_str());
}
}  // namespace sg_media
