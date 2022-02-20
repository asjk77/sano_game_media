class Font {
 public:
  Font(platform::FontPtr& inFont) : mF(inFont) {}
  ~Font() { Release(); }

  /**
   * @brief 문자열 텍스처를 생성합니다. UTF8
   *
   * @return 문자열 텍스처
   */
  TexturePtr CreateTextureString(const char* inString_UTF8, Color& inColor);

  /**
   * @brief 폰트가 존재하는지 확인합니다.
   *
   * @return 만약 폰트가 존재할 경우 True
   */
  bool IsInit() { return mF != nullptr; }

 private:
  void Release();
  platform::FontPtr mF;
};

typedef std::shared_ptr<Font> FontPtr;

FontPtr CreateFontFromMemory(const char* inMemory, size_t inMemorySize,
                             size_t inFontSize);
FontPtr CreateFontFromFile(const char* inFileName, size_t inFontSize);

typedef std::string FontKey;
/**
 * @brief 폰트를 관리하는 전역 관리자 입니다.
 */
class FontManager {
 public:
  FontManager(FontPtr& inBaseFont) : mBaseFont(inBaseFont) {}
  virtual ~FontManager() {}

  static std::unique_ptr<FontManager> sInstance;
  static void StaticInit();
  static void StaticRelease() { sInstance.reset(); }

  FontPtr& GetBaseFont() { return mBaseFont; }

  const FontPtr& GetBaseFont() const { return mBaseFont; }

  /**
   * @brief 기본 폰트를 설정합니다.
   */
  void SetBaseFont(const FontPtr& inFont) { mBaseFont = inFont; }

  void RegisterFont(const FontKey& inKey, FontPtr& inFont);
  /**
   * @brief 폰트 키를 이용해서 폰트를 얻습니다.
   * 만약 해당 폰트가 없을 경우 기본 폰트를 반환합니다.
   */
  const FontPtr& GetFont(const FontKey& inKey) const;

 private:
  FontPtr mBaseFont;
  typedef std::unordered_map<FontKey, FontPtr> FontKeyToFontPtrMap;
  FontKeyToFontPtrMap mFonts;
};

/**
 * @brief 폰트를 파일에서 생성하고 등록합니다.
 *
 * @param inFileName 파일 이름
 * @param inFontSize 폰트 크기
 */
void CreateFontAndRegisterFromFile(FontKey&& inKey, std::string&& inFileName,
                                   size_t inFontSize);

/**
 * @brief 폰트 키를 이용하여 기본 폰트를 설정합니다.
 *
 * @param inKey 기본 폰트가 될 폰트 키
 */
void SetBaseFontFromKey(FontKey&& inKey);
