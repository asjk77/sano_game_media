
/**
 * @brief 그래픽 장치의 인터페이스 입니다. 전역객체 입니다.
 */
class GraphicsDevice2d {
 public:
  GraphicsDevice2d(platform::RendererPtr& inRenderer) : mRenderer(inRenderer) {}
  ~GraphicsDevice2d() { Release(); }

  static std::unique_ptr<GraphicsDevice2d> sInstance;
  /**
   * @brief 그래픽 디바이스를 초기화합니다.
   * 초기화 하기 위해서는 WindowManager가 먼저 초기화 되어야 합니다.
   */
  static void StaticInit();
  static void StaticRelease() { sInstance.reset(); }

  /**
   * @brief 화면을 지웁니다.
   */
  void Clear();

  /**
   * @brief 버퍼에서 화면 버퍼로 복사합니다.
   */
  void Present();

  void SetRenderColor(const Color& inColor);
  void GetRenderColor(Color& outColor) const;
  /**
   * @brief 사각형을 그립니다.
   */
  void RenderRect(const Rect& inRect);
  void RenderRect(const RectF& inRect);
  /**
   * @brief 텍스처를 랜더링 합니다.
   *
   * @param inTexture 텍스처
   * @param inSrcRect 텍스처의 소스 직사각형
   * @param inDestRect 텍스처의 목적지 직사각형
   */
  void RenderTexture(const TexturePtr& inTexture, const Rect& inSrcRect,
                     const Rect& inDestRect);

  void RenderTexture(const TexturePtr& inTexture, const Rect& inSrcRect,
                     const RectF& inDestRect);

  /**
   * @brief 사각형을 채웁니다. RenderColor로
   *
   * @param inRect
   */
  void RenderFillRect(const Rect& inRect);

  /**
   * NOTE SetRenderTarget과 GetRenderTarget이TexturePtr이 아닌
   * platform::TexturePtr 의 요구하는 이유는 Native 함수가 실질적으로 요구하는
   * 것은 platform의 텍스처 객체이고 인수를 TexturePtr로 할경우 실제로 현제
   * RenderTarget을 얻는다고 해도 TextureManager에서 관리하는 TexturePtr이
   * 아니므로 의도치 않은 매모리 해제를 할 수 있습니다.
   */
  /**
   * @brief 랜더 타겟을 설정합니다.
   *
   * @param inTexture
   */
  void SetRenderTarget(const platform::TexturePtr& inT);

  /**
   * @brief 랜더 타겟을 얻습니다.
   *
   * @param outTexture
   */
  void GetRenderTarget(platform::TexturePtr& outT);

  const platform::RendererPtr GetRendererPtr() const { return mRenderer; };

 private:
  /**
   * @brief 그래픽 장치를 제거합니다.
   */
  void Release();  // 그래픽 장치를 제거합니다.
 private:
  platform::RendererPtr mRenderer;
};

/**
 * @brief Texture에서 Texture로 복사합니다.
 *
 * @param inTexture
 * @param Unknown
 */
void RenderTextureToTexture(const TexturePtr& inSrcTexture,
                            const Rect& inSrcRect, const TexturePtr& inTexture,
                            const Rect& inDestRect);

void RenderTextureToTexture(const TexturePtr& inSrcTexture,
                            const Rect& inSrcRect, const TexturePtr& inTexture,
                            const RectF& inDestRect);

/**
 * @brief Rect를 텍스처로 그립니다.
 *
 * @param inRect 사각형  
 * @param inDestTexture 목적지 텍스처
 */
void RenderRectToTexture(const Rect& inRect, const TexturePtr& inDestTexture );

/**
 * @brief Rect 를 컬러와 함께 그립니다.
 *
 * @param inDestTexture
 * @param inColor
 */
void RenderRectToTextureWithColor(const Rect& inRect, const TexturePtr& inDestTexture, const Color& inColor);
void RenderFillRectToTexture( const Rect& inRect, const TexturePtr& inDestTexture );

void RenderFillRectToTextureWithColor( const Rect& inRect, const TexturePtr& inDestTexture, const Color& inColor);

/**
 * @brief 텍스처를 지웁니다. RGBA(0,0,0,0)
 *
 * @param inDestTexture
 */
void ClearTexture(const TexturePtr& inDestTexture);

