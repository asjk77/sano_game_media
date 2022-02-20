namespace platform {

/**
 * @brief 외부 문서입니다.
 */
// typedef int Rect;
// typedef int Color;

/**
 * @brief 리소스 핸들을 정의합니다.
 */
typedef void* WindowPtr;
typedef void* SerfacePtr;
typedef void* TexturePtr;
typedef void* RendererPtr;

// mixer
typedef void* MusicPtr;
typedef void* ChunkPtr;

// ttf
typedef void* FontPtr;
/**
 * @brief 플렛폼을 초기화 합니다.
 */
void Init();

/**
 * @brief 플렛폼을 해제 합니다.
 */
void Release();

/**
 * @brief 플렛폼의 에러를 반환합니다.
 *
 * @return 에러 문자열
 */
const char* GetLastError();
/**
 * @brief 윈도우를 생성합니다.
 *
 * @param inTitle 윈도우 타이틀을 입력합니다.
 * @param inX 생성될 좌표 x
 * @param inY 생성될 좌표 y
 * @param inW 윈도우의 넓이
 * @param inH 윈도우의 높이
 *
 * @return 윈도우 핸들을 반환합니다. 실패시 nullptr을 반환합니다.
 */
WindowPtr CreateWindow(const char* inTitle, int inX, int inY, int inW, int inH);

/**
 * @brief 윈도우를 파괴합니다.
 *
 * @param inWindow 파괴할 윈도우를 입력합니다.
 */
void DestroyWindow(WindowPtr inWindow);

/**
 * @brief 윈도우 사이즈를 구합니다.
 *
 * @param inWindow 윈도우
 * @param outWidth
 * @param outHeight
 */
void GetWindowSize(WindowPtr& inWindow, int* outWidth, int* outHeight);

/**
 * @brief 랜더러를 생성합니다.
 *
 * @param inWindow 윈도우 핸들
 *
 * @return 랜더러 핸들을 반환합니다. 실패시 nullptr을 반환합니다.
 */
RendererPtr CreateRenderer(WindowPtr inWindow);

/**
 * @brief 랜더러를 파괴합니다.
 *
 * @param inRenderer 랜더러 핸들을 반환합니다.
 */
void DestroyRenderer(RendererPtr inRenderer);

/**
 * @brief 랜더러의 DrawColor를 설정합니다.
 *
 * @param inRenderer 랜더러의 핸들
 * @param inR RedColor
 * @param inG GreenColor
 * @param inB BlueColor
 * @param inA Alpha
 */
void SetRenderDrawColor(RendererPtr inRenderer, uint8_t inR, uint8_t inG,
                        uint8_t inB, uint8_t inA);

/**
 * @brief 랜더러를 블랜드 모드 로 설정합니다.
 *
 * @param inRenderer
 */
void SetRenderDrawBlendMode(RendererPtr& inRenderer);

/**
 * @brief 랜더러의 DrawColor를 얻습니다.
 *
 * @param inRenderer 랜더러의 핸들
 * @param outR RedColor
 * @param outG GreenColor
 * @param outB BlueColor
 * @param outA Alpha
 */
void GetRenderDrawColor(RendererPtr inRenderer, uint8_t* outR, uint8_t* outG,
                        uint8_t* outB, uint8_t* outA);

/**
 * @brief 화면을 지웁니다. 그리기 색상으로 현제 화면을 지웁니다.
 *
 * @param inRenderer 랜더러 의 핸들
 */
void RenderClear(RendererPtr inRenderer);

/**
 * @brief 수행된 랜더링으로 화면을 업데이트 합니다.
 *
 * @param inRenderer 랜더러의 핸들
 */
void RenderPresent(RendererPtr inRenderer);

/**
 * @brief 화면에 직사각형 그리기 색상으로 그립니다..
 *
 * @param inRenderer 랜더러의 핸들
 * @param inRect 직사각형
 */
void RenderRect(RendererPtr inRenderer, const Rect& inRect);
void RenderRect(RendererPtr inRenderer, const RectF& inRect);

/**
 * @brief 화면에 직사각형 그리기 색상으로 현제 직사각형을 채웁니다.
 *
 * @param inRenderer 랜더러의 핸들
 * @param inRect
 */
void RenderFillRect(RendererPtr inRenderer, const Rect& inRect);
void RenderFillRect(RendererPtr inRenderer, const RectF& inRect);

/**
 * @brief 화면에 텍스처를 복사합니다.
 *
 * @param inRenderer 랜더러의 핸들
 * @param inTexture 그릴 택스처
 * @param inSrcRect 텍스처의 원본 직사각형
 * @param inDestRect 화면의 목적지 직사각형
 */
void RenderCopy(RendererPtr inRenderer, TexturePtr inTexture,
                const Rect& inSrcRect, const Rect& inDestRect);
void RenderCopy(RendererPtr inRenderer, TexturePtr inTexture,
                const Rect& inSrcRect, const RectF& inDestRect);

/**
 * @brief 랜더 타겟을 설정합니다.
 *
 * @param inRenderer
 * @param inTexture
 */
void SetRenderTarget(RendererPtr inRenderer, TexturePtr inTexture);

/**
 * @brief 랜더 타겟을 얻습니다.
 *
 * @param inRenderer
 * @param outTexture
 */
TexturePtr GetRenderTarget(RendererPtr inRenderer);

/**
 * @brief 텍스처를 생성합니다.
 * RGBA8888 형식의 SDL_TEXTUREACCESS_TARGET (해당 텍스처는 Target 이 될 수
 * 있습니다)
 *
 * @param inRenderer 랜더러의 핸들
 * @param inWidth 텍스처의 너비
 * @param inHeight 텍스처의 높이
 *
 * @return 텍스처 객체
 */
TexturePtr CreateTexture(RendererPtr inRenderer, int inWidth, int inHeight);

/**
 * @brief 텍스처를 블랜드(혼합) 모드로 설정합니다.
 *
 * @param 텍스쳐
 */
void SetTextureBlendMode(TexturePtr inTexture);

/**
 * @brief 텍스처를 메모리로부터 로드합니다.
 *
 * @param inMemory 텍스처의 메모리 주소
 * @param inMemorySize 텍스처의 메모리 사이즈
 *
 * @return 성공시 텍스처의 핸들 실패시 nullptr을 반환합니다.
 */
TexturePtr LoadTextureFromMemory(const char* inMemory, size_t inMemorySize);

/**
 * @brief 텍스처를 파괴합니다.
 *
 * @param inTexture 텍스처의 핸들
 */
void DestoryTexture(TexturePtr inTexture);

/**
 * @brief 텍스처의 정보를 얻습니다.
 *
 * @param inTexture 텍스처의 핸들
 * @param outWidth 높이
 * @param outHeight 넓이
 */
void QueryTexture(TexturePtr inTexture, int* outWidth, int* outHeight);

/**
 * @brief 폰트를 메모리로부터 얻습니다.
 *
 * @param inMemory 폰트 메모리 첫 주소
 * @param inMemorySize 폰트의 메모리 사이즈
 * @param inFontSize 폰트의 사이즈를 입력받습니다.
 *
 * @return 성공시 폰트의 핸들 실패시 nullptr 을 반환합니다.
 */
FontPtr LoadFontFromMemory(const char* inMemory, size_t inMemorySize,
                           size_t inFontSize);
FontPtr LoadFontFromFile(const char* inFile, size_t inFontSize);

/**
 * @brief 폰트를 파괴합니다.
 *
 * @param inFont
 */
void DestoryFont(FontPtr inFont);

/**
 * @brief 폰트를 텍스처로 랜더합니다.
 *
 * @param inRenderer 랜더러 핸들
 * @param inFont 폰트 핸들
 * @param inText 텍스트 주소
 * @param inColor 랜더할 색상
 *
 * @return 성공시 랜더된 텍스처 실패시 0
 */
TexturePtr RenderTextFromFontUTF8_Solid(RendererPtr inRenderer, FontPtr inFont,
                                        const char* inText, Color inColor);

/**
 * @brief 마우스 위치를 반환합니다.
 *
 * @param outPosX 마우스 좌표 X
 * @param outPosY 마우스 좌표 Y
 */
void GetMousePos(int* outPosX, int* outPosY);

/**
 * @brief 키 상태를 반환합니다.
 * ! 반환된 키는 임의로 해제 하면 안됩니다.
 *
 * @return 키배열
 */
const uint8_t* GetKeyboardState();

///////////////////////////////////////////////////////////////////////////////
// MIXER
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 음악를 로드합니다.
 *
 * @param inMemory 메모리
 * @param inMemorySize 메모리사이즈
 *
 * @return 성공시 음악 실패시 0
 */
MusicPtr LoadMusicFromMemory(const char* inMemory, int inMemorySize);
MusicPtr LoadMusicFromFile(const char* inFile);

/**
 * @brief 청크(효과음)를 로드합니다.
 *
 * @param inMemory 메모리
 * @param inMemorySize 메모리 사이즈
 *
 * @return 성공시 청크 실패시 0
 */
ChunkPtr LoadChunkFromMemory(const char* inMemory, int inMemorySize);
ChunkPtr LoadChunkFromFile(const char* inFile);
/**
 * @brief 음악 을 종료합니다.
 *
 * @param inChunk
 */
void FreeChunk(ChunkPtr inChunk);

/**
 * @brief 뮤직 을 종료합니다.
 *
 * @param inChunk
 */
void FreeMusic(MusicPtr inMusic);

/**
 * @brief 오디오를 오픈합니다.
 *
 * @return 성공시 true 실패시 false
 */
bool OpenAudio();

/**
 * @brief 오디오 닫습니다..
 */
void CloseAudio();

/**
 * @brief 음악을 플레이 합니다.
 *
 * @param inMusic 음악
 * @param inRepeatCount 음악 재생 카운트입니다. 만약 -1일경우 무한히
 * 반복재생합니다. 만약 0일경우 음악을 0 번 재생합니다.
 */
void PlayMusic(MusicPtr inMusic, int inRepeatCount);

/**
 * @brief 음악을 멈춥니다.
 */
void PauseMusic();

/**
 * @brief 음악을 재개합니다.
 */
void ResumeMusic();

/**
 * @brief 음악이 플레이 중인지 확인합니다.
 *
 * @return 플레이 중일시 true 아닐시 false
 */
bool IsPlayingMusic();

/**
 * @brief 음악이 멈친지 확인합니다.
 *
 * @return 멈춤일경우 true 아닐시 false
 */
bool IsPausedMusic();

/**
 * @brief Chunk를 플레이 합니다.
 * 참조 https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_28.html
 *
 * @param inChannel 채널
 * @param inChunk
 * @param inLoop
 */
void PlayChannel(int inChannel, ChunkPtr inChunk, int inLoop );

/**
 * @brief 볼륨을 설정합니다.
 *
 * @param inChannel 설정할 볼륨 채널, 만약 -1일경우 모든 채널에 해당 볼륨을 설정합니다.
 *
 * @param inVolume 1~ 126최대치 의 값을 입력받습니다. 
 * 사용할 볼륨은 0에서 MIX_MAX_VOLUME(128)까지입니다.
 * MIX_MAX_VOLUME보다 크면
 * 그러면 MIX_MAX_VOLUME으로 설정됩니다.
 * 0보다 작으면 볼륨이 설정되지 않습니다.
 */
void SetVolume( int inChannel, int inVolume );

}  // namespace platform
