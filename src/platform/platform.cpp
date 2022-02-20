#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace platform {

/**
 * @brief 각 플렛폼에 관련된 라이브러리 들을 초기화 합니다.
 * 여기서는 SDL2, SDL_ttf, SDL_image, SDL_mixer
 */
void Init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    LOG(LogLevel::Fatal, "SDL_InitError: %s", GetLastError());
    throw Exception(ls::platform::PLATFORM_INIT_ERROR);
  }

  if (TTF_Init() == -1) {
    LOG(LogLevel::Fatal, "TTF_InitError: %s", TTF_GetError());
    throw Exception(ls::platform::PLATFORM_INIT_ERROR);
  }

  // init SDL_IMG
  int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;

  int img_initted = IMG_Init(img_flags);
  if (img_initted != img_flags) {
    LOG(LogLevel::Fatal, "IMG_InitError:", IMG_GetError());
    throw Exception(ls::platform::PLATFORM_INIT_ERROR);
  }

  // load support for the OGG and MOD sample/music formats
  int mixer_flags = MIX_INIT_OGG | MIX_INIT_MOD;
  int mixer_initted = Mix_Init(mixer_flags);
  if (mixer_initted != mixer_flags) {
    LOG(LogLevel::Fatal, "Mixer_InitError:", IMG_GetError());
    throw Exception(ls::platform::PLATFORM_INIT_ERROR);
    // handle error
  }
  LOG(LogLevel::Info, ls::MODULE_INIT_COMPLETION);
}
void Release() {
  SDL_Quit();
  TTF_Quit();
  IMG_Quit();
  Mix_Quit();
  LOG(LogLevel::Info, ls::MODULE_RELEASE_COMPLETION);
}

const char* GetLastError() { return SDL_GetError(); }

WindowPtr CreateWindow(const char* inTitle, int inX, int inY, int inW,
                       int inH) {
  return SDL_CreateWindow(inTitle, inX, inY, inW, inH, SDL_WINDOW_SHOWN);
}

void DestroyWindow(WindowPtr inWindow) {
  SDL_DestroyWindow(static_cast<SDL_Window*>(inWindow));
}

void GetWindowSize(WindowPtr& inWindow, int* outWidth, int* outHeight) {
  SDL_GetWindowSize(static_cast<SDL_Window*>(inWindow), outWidth, outHeight);
}

RendererPtr CreateRenderer(WindowPtr inWindow) {
  return SDL_CreateRenderer(static_cast<SDL_Window*>(inWindow), -1,
                            SDL_RENDERER_ACCELERATED);
}

void DestroyRenderer(RendererPtr inRenderer) {
  SDL_DestroyRenderer(static_cast<SDL_Renderer*>(inRenderer));
}

void SetRenderDrawColor(RendererPtr inRenderer, uint8_t inR, uint8_t inG,
                        uint8_t inB, uint8_t inA) {
  SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(inRenderer), inR, inG, inB,
                         inA);
}

void GetRenderDrawColor(RendererPtr inRenderer, uint8_t* outR, uint8_t* outG,
                        uint8_t* outB, uint8_t* outA) {
  SDL_GetRenderDrawColor(static_cast<SDL_Renderer*>(inRenderer), outR, outG,
                         outB, outA);
}

void SetRenderDrawBlendMode(RendererPtr& inRenderer) {
  SDL_SetRenderDrawBlendMode(static_cast<SDL_Renderer*>(inRenderer),
                             SDL_BlendMode::SDL_BLENDMODE_BLEND);
}

void RenderClear(RendererPtr inRenderer) {
  SDL_RenderClear(static_cast<SDL_Renderer*>(inRenderer));
}

void RenderPresent(RendererPtr inRenderer) {
  SDL_RenderPresent(static_cast<SDL_Renderer*>(inRenderer));
}

void RenderRect(RendererPtr inRenderer, const Rect& inRect) {
  SDL_Rect rect;
  rect.x = inRect.mX;
  rect.y = inRect.mY;
  rect.w = inRect.mWidth;
  rect.h = inRect.mHeight;

  SDL_RenderDrawRect(static_cast<SDL_Renderer*>(inRenderer), &rect);
}
void RenderRect(RendererPtr inRenderer, const RectF& inRect) {
  SDL_FRect rect;
  rect.x = inRect.mX;
  rect.y = inRect.mY;
  rect.w = inRect.mWidth;
  rect.h = inRect.mHeight;

  SDL_RenderDrawRectF(static_cast<SDL_Renderer*>(inRenderer), &rect);
}

void RenderFillRect(RendererPtr inRenderer, const Rect& inRect) {
  SDL_Rect rect;
  rect.x = inRect.mX;
  rect.y = inRect.mY;
  rect.w = inRect.mWidth;
  rect.h = inRect.mHeight;

  SDL_RenderFillRect(static_cast<SDL_Renderer*>(inRenderer), &rect);
}

void RenderFillRect(RendererPtr inRenderer, const RectF& inRect) {
  SDL_FRect rect;
  rect.x = inRect.mX;
  rect.y = inRect.mY;
  rect.w = inRect.mWidth;
  rect.h = inRect.mHeight;

  SDL_RenderFillRectF(static_cast<SDL_Renderer*>(inRenderer), &rect);
}

void RenderCopy(RendererPtr inRenderer, TexturePtr inTexture,
                const Rect& inSrcRect, const Rect& inDestRect) {
  SDL_Rect src_rect;
  src_rect.x = inSrcRect.mX;
  src_rect.y = inSrcRect.mY;
  src_rect.w = inSrcRect.mWidth;
  src_rect.h = inSrcRect.mHeight;

  SDL_Rect dest_rect;
  dest_rect.x = inDestRect.mX;
  dest_rect.y = inDestRect.mY;
  dest_rect.w = inDestRect.mWidth;
  dest_rect.h = inDestRect.mHeight;

  SDL_RenderCopy(static_cast<SDL_Renderer*>(inRenderer),
                 static_cast<SDL_Texture*>(inTexture), &src_rect, &dest_rect);
}

void RenderCopy(RendererPtr inRenderer, TexturePtr inTexture,
                const Rect& inSrcRect, const RectF& inDestRect) {
  SDL_Rect src_rect;
  src_rect.x = inSrcRect.mX;
  src_rect.y = inSrcRect.mY;
  src_rect.w = inSrcRect.mWidth;
  src_rect.h = inSrcRect.mHeight;

  SDL_FRect dest_rect;
  dest_rect.x = inDestRect.mX;
  dest_rect.y = inDestRect.mY;
  dest_rect.w = inDestRect.mWidth;
  dest_rect.h = inDestRect.mHeight;

  SDL_RenderCopyF(static_cast<SDL_Renderer*>(inRenderer),
                  static_cast<SDL_Texture*>(inTexture), &src_rect, &dest_rect);
}

void SetRenderTarget(RendererPtr inRenderer, TexturePtr inTexture) {
  SDL_SetRenderTarget(static_cast<SDL_Renderer*>(inRenderer),
                      static_cast<SDL_Texture*>(inTexture));
}
TexturePtr GetRenderTarget(RendererPtr inRenderer) {
  return static_cast<TexturePtr>(
      SDL_GetRenderTarget(static_cast<SDL_Renderer*>(inRenderer)));
}
TexturePtr CreateTexture(RendererPtr inRenderer, int inWidth, int inHeight) {
  return SDL_CreateTexture(static_cast<SDL_Renderer*>(inRenderer),
                           SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_TARGET,
                           inWidth, inHeight);
}

TexturePtr LoadTextureFromMemory(const char* inMemory, size_t inMemorySize) {
  SDL_RWops* rw = SDL_RWFromConstMem(inMemory, inMemorySize);

  SDL_Surface* loaded_surface = IMG_Load_RW(rw, 1);

  // Create Surface
  if (loaded_surface == nullptr) {
    LOG(LogLevel::Warn, ls::platform::PLATFORM_TEXTURE_LOAD_ERROR_,
        IMG_GetError());
    return nullptr;
  }

  const RendererPtr& renderer_ptr =
      GraphicsDevice2d::sInstance->GetRendererPtr();

  // CreateTexture From Surface
  SDL_Texture* texture = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(renderer_ptr), loaded_surface);

  // Delete Surface
  SDL_FreeSurface(loaded_surface);

  if (texture == nullptr) {
    LOG(LogLevel::Warn, ls::platform::PLATFORM_TEXTURE_LOAD_ERROR_,
        GetLastError());
  }

  return static_cast<TexturePtr>(texture);
}

void SetTextureBlendMode(TexturePtr inTexture) {
  SDL_SetTextureBlendMode(static_cast<SDL_Texture*>(inTexture),
                          SDL_BLENDMODE_BLEND);
}

void DestoryTexture(TexturePtr inTexture) {
  SDL_DestroyTexture(static_cast<SDL_Texture*>(inTexture));
}

void QueryTexture(TexturePtr inTexture, int* outWidth, int* outHeight) {
  SDL_QueryTexture(static_cast<SDL_Texture*>(inTexture), NULL, NULL, outWidth,
                   outHeight);
}

FontPtr LoadFontFromMemory(const char* inMemory, size_t inMemorySize,
                           size_t inFontSize) {
  SDL_RWops* rw = SDL_RWFromConstMem(inMemory, inMemorySize);

  TTF_Font* font = TTF_OpenFontRW(rw, 1, inFontSize);

  if (font == nullptr) {
    LOG(LogLevel::Warn, ls::platform::PLATFORM_FONT_LOAD_ERROR_,
        TTF_GetError());
  }

  return static_cast<FontPtr>(font);
}
FontPtr LoadFontFromFile( const char * inFile, size_t inFontSize ) {
    TTF_Font * font = TTF_OpenFont( inFile, inFontSize );

  if (font == nullptr) {
    LOG(LogLevel::Warn, ls::platform::PLATFORM_FONT_LOAD_ERROR_,
        TTF_GetError());
  }
    return static_cast<FontPtr>(font);
}

void DestoryFont(FontPtr inFont) {
  TTF_CloseFont(static_cast<TTF_Font*>(inFont));
}

TexturePtr RenderTextFromFontUTF8_Solid(RendererPtr inRenderer, FontPtr inFont,
                                        const char* inText, Color inColor) {
  SDL_Color color;
  color.r = inColor.r;
  color.g = inColor.g;
  color.b = inColor.b;
  color.a = inColor.a;

  // Surface Create
  SDL_Surface* surface =
      TTF_RenderUTF8_Solid(static_cast<TTF_Font*>(inFont), inText, color);

  if (surface == nullptr) {
      // LOG(LogLevel::Warn, "RenderFontError %s", TTF_GetError());
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(
      static_cast<SDL_Renderer*>(inRenderer), surface);

  // Surface Release
  SDL_FreeSurface(surface);

  if (texture == nullptr) {
    return nullptr;
  }

  return static_cast<TexturePtr>(texture);
}

// Mouse & Keyboard
void GetMousePos(int* outPosX, int* outPosY) {
  SDL_GetMouseState(outPosX, outPosY);
}

const uint8_t* GetKeyboardState() { return SDL_GetKeyboardState(NULL); }

MusicPtr LoadMusicFromMemory(const char* inMemory, int inMemorySize) {
  SDL_RWops* rw = SDL_RWFromConstMem(inMemory, inMemorySize);
  Mix_Music* music = Mix_LoadMUS_RW(rw, 1);  //자동으로 rw객체를 닫습니다.

  if (music == nullptr) {
    LOG(LogLevel::Warn, ls::platform::CHUNK_LOAD_ERROR_, Mix_GetError());
  }
  return static_cast<MusicPtr>(music);
}

MusicPtr LoadMusicFromFile(const char* inFile) {
    Mix_Music* music = Mix_LoadMUS(inFile);  //자동으로 rw객체를 닫습니다.
    if (music == nullptr) {
    LOG(LogLevel::Warn, ls::platform::CHUNK_LOAD_ERROR_, Mix_GetError());
    }
    return static_cast<MusicPtr>(music);
}

ChunkPtr LoadChunkFromMemory(const char* inMemory, int inMemorySize) {
  SDL_RWops* rw = SDL_RWFromConstMem(inMemory, inMemorySize);

  Mix_Chunk* chunk = Mix_LoadWAV_RW(rw, 1);  //자동으로 rw객체를 닫습니다.

  if (chunk == nullptr) {
    LOG(LogLevel::Warn, ls::platform::CHUNK_LOAD_ERROR_, Mix_GetError());
  }
  return static_cast<ChunkPtr>(chunk);
}

ChunkPtr LoadChunkFromFile(const char* inFile) {
  Mix_Chunk* chunk = Mix_LoadWAV( inFile );  //자동으로 rw객체를 닫습니다.

  if (chunk == nullptr) {
    LOG(LogLevel::Warn, ls::platform::CHUNK_LOAD_ERROR_, Mix_GetError());
  }
  return static_cast<ChunkPtr>(chunk);
}

void FreeChunk(ChunkPtr inChunk) {
  Mix_FreeChunk(static_cast<Mix_Chunk*>(inChunk));
}

void FreeMusic(MusicPtr inMusic) {
  Mix_FreeMusic(static_cast<Mix_Music*>(inMusic));
}

bool OpenAudio() {
  int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  if (result == -1) {
    return false;
  }

  return true;
}
void CloseAudio() { Mix_CloseAudio(); }

void PlayMusic(MusicPtr inMusic, int inRepeatCount) {
  Mix_PlayMusic(static_cast<Mix_Music*>(inMusic),
                static_cast<int>(inRepeatCount));
}
void PauseMusic() { Mix_PauseMusic(); }

void ResumeMusic() { Mix_ResumeMusic(); }

bool IsPlayingMusic() { return Mix_PlayingMusic() == 1; }

bool IsPausedMusic() { return Mix_PausedMusic() == 1; }

void PlayChannel(int inChannel, ChunkPtr inChunk, int inLoop ) {
    Mix_PlayChannel( inChannel, static_cast< Mix_Chunk*>( inChunk ), inLoop ); 
}


void SetVolume( int inChennel, int inVolume ) {
    Mix_Volume( inChennel, inVolume );
}

}  // namespace platform
}  // namespace sg_media
