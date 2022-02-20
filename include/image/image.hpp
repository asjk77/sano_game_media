/**
 * @brief 이미지 객체입니다.
 * 여기서 이미지는 텍스처의 한 부분( 사각영역) 을 의미합니다.
 */
class Image {
public:
    Image( TexturePtr& inBoard, Rect& inFocusRect) : mBoard( inBoard ), mFocusRect(inFocusRect) {}
    virtual ~Image() {}    


    /**
     * @brief 목적지 텍스처에 이미지를 랜더링합니다.
     *
     * @param inDest 화면상의 사각형
     */
    void Render( const TexturePtr& inDest, const Rect & inDestRect ) const;
    void Render( const TexturePtr& inDest, const RectF& inDestRect ) const;
    
    /**
     * @brief 현제 화면에 텍스처를 랜더링합니다.
     *
     * @param inDestRect
     */
    void Render( const Rect& inDestRect ) const;
    
    /**
     * @brief 이미지를 업데이트 합니다.
     * 만약 하위 클레스의 업데이트 기능이 있을 경우 재정의하십시오
     * 
     * @param inSpeed 업데이트 스피드를 입력합니다.
     * 만약 speed 값을 2.0f 로 설정할경우 2배의 속도를 가집니다.
     */
    virtual void Update( float inSpeed = 1.0f ) {}
    const Rect& GetFocusRect() const { return mFocusRect; }

    /**
     * @brief 이미지가 만료되었을 경우 true
     *
     * @return 
     */
    bool IsExpired() { return mIsExpired; }
    void SetIsExpired( bool inIsExpired ) { mIsExpired = inIsExpired; }
protected:
    /**
     * @brief 만료시킵니다.
     */
    void Expire() { mIsExpired = true; }

    TexturePtr mBoard;
    Rect mFocusRect;
private:
    bool mIsExpired = true;
};

typedef std::shared_ptr<Image> ImagePtr;

/**
 * @brief 이미지를 생성합니다.
 *
 * @param inBoard 보드텍스처
 * @param inFocusRect 이미지의 Rect
 *
 * @return 이미지 객체를 반환합니다.
 */
ImagePtr CreateImage( TexturePtr & inBoard, Rect& inFocusRect );

/**
 * @brief 이미지를 생성합니다.
 * FocusRect는 자동으로 texture의 크기만큼 설정됩니다.
 *
 * @param inBoard 보드 텍스처 
 *
 * @return 이미지 객체를 반환합니다.
 */
ImagePtr CreateImage( TexturePtr & inBoard );
