typedef string TextureKey;
/**
 * @brief 텍스처 관리자 입니다. 전역 객체입니다.
 */
class TextureManager {
 public:
  TextureManager(TexturePtr& inBaseTexture): mBaseTexture( inBaseTexture ) {}
  virtual ~TextureManager() {}

  static std::unique_ptr<TextureManager> sInstance;

  /**
   * @brief 텍스처 관리자를 초기화 합니다.
   */
  static void StaticInit();
  static void StaticRelease() { sInstance.reset(); }

  /**
   * @brief 텍스처 키를 이용하여 텍스쳐를 얻습니다.
   * 만약 텍스처가 없을경우 기본 텍스처를 반환합니다.
   *
   * @param inKey 키
   *
   * @return 텍스처 핸들
   */
  TexturePtr& GetTexture(TextureKey& inKey);


  /**
   * @brief 기본 텍스처를 얻습니다.
   *
   * @return 기본 텍스처 핸들
   */
  TexturePtr& GetBaseTexture() { return mBaseTexture; }
  const TexturePtr& GetBaseTexture() const { return mBaseTexture; }

  /**
   * @brief 텍스처를 등록합니다.
   * 만약 기존에 텍스처가 존재할 경우 덮어쓰기를 진행합니다.
   *
   * @param inKey 텍스처 키
   * @param inTexture 텍스처
   */
  void RegisterTexture(TextureKey& inKey, TexturePtr& inTexture);
  inline void RegisterTexture(TextureKey&& inKey, TexturePtr& inTexture) {
      RegisterTexture( inKey, inTexture );
  }
 private:
  typedef std::unordered_map<TextureKey, TexturePtr> TextureKeyToTexturePtrMap;
  TextureKeyToTexturePtrMap mTextureMap;

  TexturePtr mBaseTexture;
};

