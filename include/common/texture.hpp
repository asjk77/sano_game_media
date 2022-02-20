#ifndef SANO_GAME_MEDIA_TEXTURE_HPP
#define SANO_GAME_MEDIA_TEXTURE_HPP

class Texture {
 public:
     Texture( platform::TexturePtr inT ) : mT(inT) {}
     virtual ~Texture() { Release(); }

     const platform::TexturePtr GetTexture() const { return mT; }

     /**
      * @brief Texture 가 존재하는지 확인합니다.
      *
      * @return 만약 텍스처가 존재할 경우 True
      */
     bool IsInit() const { return mT != nullptr; }


     /**
      * @brief Width 값과 Height 값을 얻습니다.
      *
      * @param outWidth Width 값
      * @param outHeight Height 값
      */
     void GetInfo(int& outWidth, int& outHeight);
     
 private:
     void Release() noexcept;
     platform::TexturePtr mT;
};

typedef std::shared_ptr<Texture> TexturePtr;

/**
 * @brief 텍스처객체를 매모리로부터 생성합니다.
 *
 * @param inMemory 메모리 주소
 * @param inMemorySize 메모리 사이즈
 *
 * @return 텍스처 객체 
 */
TexturePtr CreateTextureFromMemory(const char * inMemory, size_t inMemorySize );

TexturePtr CreateTextureFromFile(const char * inFileName);
/**
 * @brief 텍스처를 생성합니다.
 * RGBA8888
 * TargetAble
 * @param inWidth
 * @param inHeight
 *
 * @return 텍스처 핸들
 */
TexturePtr CreateTexture( int inWidth, int inHeight );


/**
 * @brief 혼합 모드가 적용된 텍스처를 생성합니다.
 *
 * @param inWidth 너비
 * @param inHeight 높이
 *
 * @return 텍스처 핸들
 */
TexturePtr CreateBlendModeTexture( int inWidth, int inHeight );

#endif /* SANO_GAME_MEDIA_TEXTURE_HPP */
