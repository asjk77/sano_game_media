typedef string WidgetKey;
/**
 * @brief 위젯을 관리하는 전역 관리자 입니다.
 *
 */
class WidgetManager
{
public:
    WidgetManager( WidgetPtr& inBaseWidget ) : mBaseWidget(inBaseWidget) {}
    ~WidgetManager() {}

    static std::unique_ptr< WidgetManager > sInstance;

    static void StaticInit();
    static void StaticRelease() { sInstance.reset(); }
    /**
     * @brief 위젯을 등록합니다. 
     */
    void RegisterWidget( WidgetKey& inKey, WidgetPtr& inWidget );
    void RegisterWidget( WidgetKey&& inKey, WidgetPtr& inWidget ) { RegisterWidget( inKey, inWidget ); }
    /**
     * @brief 위젯의을 얻습니다.
     *
     * @param inKey
     *
     * @return 
     */
    WidgetPtr& GetWidget( WidgetKey& inKey );

    const WidgetPtr& GetBaseWidget() const { return mBaseWidget; } 

private:
    /**
     * @brief 기본 위젯입니다.
     */
    WidgetPtr mBaseWidget;

    typedef std::vector< WidgetPtr > WidgetList;
    typedef std::unordered_map< WidgetKey, WidgetPtr > WidgetKeyToWidgetPtrMap;
    WidgetKeyToWidgetPtrMap mWidgetMap;
};

/**
 * @brief 위젯을 생성하고 등록합니다.
 *
 * @param inPosition 위젯의 위치
 * @param inKey 위젯의 키
 *
 */

WidgetPtr CreateWidgetAndRegister(const Rect& inPosition, WidgetKey& inKey);
inline WidgetPtr CreateWidgetAndRegister(const Rect&& inPosition, WidgetKey&& inKey) {
    return CreateWidgetAndRegister( inPosition, inKey );
}
/**
 * @brief 보드 위젯을 생성하고 등록합니다.
 *
 * @param inPosition 위젯의위치
 * @param inBoardImage 보드이미지
 * @param inKey 위젯의 키
 *
 */
WidgetPtr CreateBoardAndRegister(const Rect& inPosition, ImagePtr& inBoardImage, WidgetKey& inKey);
inline WidgetPtr CreateBoardAndRegister(const Rect&& inPosition, ImagePtr&& inBoardImage, WidgetKey&& inKey) {
    return CreateBoardAndRegister( inPosition, inBoardImage, inKey );
}
inline WidgetPtr CreateBoardAndRegister(const Rect&& inPosition, ImagePtr& inBoardImage, WidgetKey&& inKey) {
    return CreateBoardAndRegister( inPosition, inBoardImage, inKey );
}

/**
 * @brief 버튼 위젯을 생성하고 등록합니다.
 *
 * @param inPosition 버튼 위치
 * @param inClickFunc 클릭시 호출될 함수
 *
 * @return 버튼 위젯 핸들
 */
WidgetPtr CreateBaseButtonAndRegister( const Rect& inPosition, ClickFunc inClickFunc, WidgetKey& inKey );
inline WidgetPtr CreateBaseButtonAndRegister( const Rect&& inPosition, ClickFunc inClickFunc, WidgetKey&& inKey ) {
    return CreateBaseButtonAndRegister( inPosition, inClickFunc, inKey );
}

/**
 * @brief 위젯을 생성하고 등록합니다.
 *
 * @param inPosX inPosX 생성할 좌표X
 * @param inPosY inPosY 생성할 좌표Y
 * @param inFont 폰트
 * @param inString_UTF8 문자열 (UTF8)
 * @param inColor 생성될 StaticWidget의 색
 * @param inKey 등록할 키를 정의합니다.
 *
 * @return
 */
WidgetPtr CreateStaticWidgetAndRegister(int inPosX, int inPosY, FontPtr& inFont,
                                        const char* inString_UTF8,
                                        Color& inColor, WidgetKey& inKey);

