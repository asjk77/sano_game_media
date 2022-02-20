
/**
 * @brief 윈도우의 래퍼 클래스입니다.
 */
class Window {
public:
    Window( platform::WindowPtr inW ): mW( inW ){}
    ~Window() { Release(); }

    platform::WindowPtr& GetWindow() { return mW; }

    void GetWindowSize(int& outWidth, int& outHeight);
private:
    void Release() noexcept; // 윈도우를 자동으로 제거합니다.
private:
    platform::WindowPtr mW;
};

typedef std::shared_ptr<Window> WindowPtr;
/**
 * @brief 윈도우를 생성합니다.
 *
 * @param inTitle 윈도우 타이틀을 입력합니다.
 * @param inWidth 윈도우 너비를 입력합니다.
 * @param inHeight 윈도우 높이를 입력시킵니다.
 *
 * @return 윈도우 객체를 반환합니다.
 */
WindowPtr CreateWindow(const char* inTitle, const int inWidth, const int inHeight );

/**
 * @brief 윈도우를 관리하는 전역 관리자 입니다.
 *
 */
class WindowManager {
public:
    WindowManager( WindowPtr &inWindow ) : mWindow( inWindow ) {}
    ~WindowManager() {}

    static std::unique_ptr< WindowManager > sInstance;

    /**
     * @brief 윈도우 관리자를 초기화 합니다.
     *
     * @param inTitle 윈도우의 제목을 입력합니다.
     * @param inWidth 윈도우의 너비를 입력합니다.
     * @param inHeight 윈도우의 높이를 입력합니다.
     */
    static void StaticInit( const char * inTitle, const int inWidth, const int inHeight );
    static void StaticRelease() { sInstance.reset(); }

    /**
     * @brief 윈도우를 얻습니다.
     * 윈도우 객체는 윈도우 포인터가 아닙니다.
     * 
     * @return 윈도우 객체
     */
    const WindowPtr GetWindow() const { return mWindow; } 


    /**
     * @brief 기본 윈도우를 반환합니다.
     */
    WindowPtr& GetWindow() { return mWindow; }
private:
    WindowPtr mWindow;
};
