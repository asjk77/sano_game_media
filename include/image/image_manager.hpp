typedef string ImageKey; 

/**
 * @brief 이미지를 관리하는 전역 관리자 입니다.
 */
class ImageManager
{
public:
    ImageManager( ImagePtr & inBaseImage ) : mBaseImage( inBaseImage ) {}
    virtual ~ImageManager() {}

    static std::unique_ptr< ImageManager > sInstance;

    /**
     * @brief 이미지 관리자를 초기화 합니다.
     */
    static void StaticInit();
    static void StaticRelease() { sInstance.reset(); }
    /**
     * @brief 이미지 키를 이용해서 이미지를 얻습니다. 
     *
     * @param inKey 이미지 키 
     *
     * @return 이미지 객체
     */
    ImagePtr& GetImage( ImageKey& inKey );

    /**
     * @brief 이미지를 등록합니다.
     *
     * @param inKey 키
     * @param inImage 이미지
     */
    void RegisterImage( ImageKey& inKey, ImagePtr& inImage );

    ImagePtr& GetBaseImage() { return mBaseImage; }
    const ImagePtr& GetBaseImage() const { return mBaseImage; };

private:
    typedef std::unordered_map< ImageKey, ImagePtr > ImageKeyToImagePtrMap;
    ImageKeyToImagePtrMap mImageMap;

    ImagePtr mBaseImage;
};
