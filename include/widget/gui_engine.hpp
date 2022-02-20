/**
 * @brief GuiEngine 입니다.
 */
class GuiEngine {
 public:
  GuiEngine(WidgetPtr& inRootWidget)
      : mRootWidget(inRootWidget), mFocusWidget(inRootWidget) {}
  virtual ~GuiEngine() {}

  static std::unique_ptr<GuiEngine> sInstance;

  /**
   * @brief  GuiEngine을 초기화 합니다.
   */
  static void StaticInit();
  static void StaticRelease() { sInstance.reset(); }

  /**
   * @brief 루트 위젯을 얻습니다.
   *, mTargetWidget(this)
   * @return 위젯
   */
  WidgetPtr& GetRootWidget() { return mRootWidget; }

  /**
   * @brief 루트 위젯 을 바꿉니다.
   * 현제 GUIEngine의 포커스를 다시 설정합니다.
   * 모든 캐쉬를 삭제합니다.
   * @param inRootWidget 루트 위젯
   */
  void Reset(WidgetPtr& inRootWidget);

  // 포커스 위젯을 설정합니다.
  void SetFocusWidget(WidgetPtr& inFocusWidget) {
    mFocusWidget = inFocusWidget;
  }
  WidgetPtr& GetFocusWidget() { return mFocusWidget; }

  /**
   * @brief 이벤트를 처리합니다.
   * NOTE 이 함수는 이벤트 루프에서 실행되어야 합니다.
   *
   * @param inEvent
   */
  void HandleEvent(const Event& inEvent);

 public:
  /**
   * @brief 이벤트를 처리합니다.
   * 각 이벤트 처리 함수입니다.
   */
  void HandleMouseMotionEvent(const Event& inEvent);
  void HandleMouseButtonEvent(const Event& inEvent);

 public:
  /**
   * @brief 최상위 위젯을 랜더링 합니다.
   */
  void RenderRootWidget();

  /**
   * @brief 최상위 위젯을 업데이트 합니다.
   */
  void UpdateRootWidget();

 public:
  bool& GetIsMouseLeftButtonDownRef() { return mIsMouseLeftButtonDown; }

 private:
  void SetIsMouseLeftButtonDownState(const Event& inEvent);

 private:
  bool mIsMouseLeftButtonDown = false;  // 마우스 버튼이 다운되었을경우 True

  /**
   * @brief 위젯들의 캐쉬
   *
   * 예를들어
   * MouseButtonDown 이벤트가 호출되면 해당 Widget객체를 캐쉬 해놓아야 한다.
   * 안그러면 MouseButtonUp이벤트가 발생하였시 MouseButtonDown 이벤트를 받은
   * 위젯을 초기화 시켜줘야 하는데 캐쉬가 없을경우 MouseButtonDown 위젯을 찾기
   * 위해서 트리를 순회해야한다.
   *
   * MouseDown 이벤트시  MouseButtonCache 에 해당 값을 저장합니다. 그리고
   * ProcessMouseDownEvent 를 widget 에 전달합니다. MouseUp 이벤트시
   * MouseKeyCache 에 있는 값과 현제 Down된 widget을 비교합니다. 그리고
   * ProcessMouseUpEvent를 전달하고 WidgetCache를 초기화 합니다.
   *
   * MouseMove 이벤트 발생시 현제 호버링된 위젯을 구하여 mHoveringCache랑
   * 비교하여 다를 경우 해당 ProcessUnHoveringEvent이벤트를 전달합니다 그리고
   * mHoveringCache를 다시 캐싱합니다 같을경우 아무 이벤트도 전달하지 않습니다.
   */

  WidgetPtr mMouseClickCacheWidget = nullptr;  // 마우스 키 캐쉬 위젯입니다.
  WidgetPtr mMouseHoveringCacheWidget = nullptr;  // 마우스 호버링 캐쉬 위젯입니다.

 public:
  WidgetPtr& GetMouseClickCacheWidget() { return mMouseClickCacheWidget; }
  void SetMouseClickCacheWidget(WidgetPtr& inWidget) {
    mMouseClickCacheWidget = inWidget;
  }

  WidgetPtr& GetMouseHoveringCacheWidget() { return mMouseHoveringCacheWidget; }
  void SetMouseHoveringCacheWidget(WidgetPtr& inWidget) {
    mMouseHoveringCacheWidget = inWidget;
  }

 public:
 private:
  WidgetPtr mRootWidget;   // 현제 최상위 위젯입니다.
  WidgetPtr mFocusWidget;  // 현제 포커스된 위젯입니다.
};
