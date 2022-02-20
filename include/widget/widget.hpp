
#define SN_WIDGET_CLASS_IDENTIFIER_SUPER(c) SN_CLASS_IDENTIFIER_SUPER( WidgetClass, c )
#define SN_WIDGET_CLASS_IDENTIFIER_SUB(c) SN_CLASS_IDENTIFIER_SUB( WidgetClass, c )


typedef sg_media::util::DebuggableWidget DebuggableWidget;
/**
 * @brief 위젯의 추상 클레스입니다.
 * 위젯은 기본적으로 자식 노드를 가질 수 있습니다. 위젯의 자식 노드는
 * std::weeak_ptr 로 구성되었습니다.
 * 위젯은 추가적으로 다음 기능들을 제정의 하여 사용 할 수 있습니다.
 *
 * Render 위젯을 랜더링합니다.
 * Update 위젯을 업데이트 합니다.
 *
 * Widget은 현제 텍스처를 가지고 있습니다.
 */
class Widget : public DebuggableWidget {
 public:
  typedef std::shared_ptr<Widget> WidgetPtr;
  typedef std::vector<WidgetPtr> WidgetList;

  friend class GuiEngine;
  SN_WIDGET_CLASS_IDENTIFIER_SUPER(WidgetClass::Widget)

  /**
   * @brief 위젯을 생성합니다.
   * 위젯의 기본 텍스처도 생성합니다.
   *
   * @param inPosition
   * @param inIsActivate
   * @param inIsFocusable
   */
  Widget(const Rect& inPosition, bool inIsActivate, bool inIsFocusable);
  /**
   * @brief 위젯을 초기화 합니다.
   *
   * @param inPosition 위젯의 위치 값을 지정합니다.
   */
  Widget(const Rect& inPosition) : Widget(inPosition, true, true) {}

  virtual ~Widget() {}

  /**
   * @brief 부모 텍스처에 Widget을 렌더링합니다.
   *
   * @param inParentTexture 부모 텍스처
   * @param inDrawPosX 그릴 좌표X
   * @param inDrawPosY 그릴 좌표Y
   */
  virtual void Render(const TexturePtr& inParentTexture ) const;

  /**
   * @brief 위젯을 업데이트 합니다.
   */
  virtual void Update() { }

  /**
   * @brief GUI_Engine으로부터 이벤트를 전달받습니다.
   * NOTE GUI_Engine이 호출합니다.
   *
   * @param 이벤트 객체
   */
  void ForwardEvent( const Event& inEvent );

  /**
   * @brief 클릭 이벤트를 정의합니다.
   *
   * @param inMousePosX 마우스 X 위치
   * @param inMousePosY 마우스 Y 위치
   */
  virtual void OnClick() {}
  virtual void OnMouseHover() {}
  virtual void OnMouseUnHover() {}
  virtual void OnFocus() { Expire(); }
  virtual void OnUnFocus() { Expire(); }


  /**
   * @brief 이벤트를 핸들링합니다.
   *
   * @param inEvent
   */
  virtual void HandleEvent(const Event& inEvent) {}

  /**
   * @brief 현제 위젯에 자식위젯(노드) 를 추가합니다.
   *
   * @param inWidget
   */
  void AddChildWidget(const WidgetPtr& inWidget);

  const Rect& GetRect() const { return mPosition; }
  int GetPosX() const { return mPosition.mX; }
  int GetPosY() const { return mPosition.mY; }
  int GetWidth() const { return mPosition.mWidth; }
  int GetHeight() const { return mPosition.mHeight; }

  // 위젯을 X,Y 축으로 이동합니다.
  void Move(int inRelXPos, int inRelYPos) { mPosition.mX += inRelXPos; mPosition.mY += inRelYPos;}

  const WidgetList& GetChildrenWidget() const { return mChildren; }

  bool IsFocusable() { return mIsFocusable; }
  bool IsActivate() { return mIsActivate; }
  bool IsExpired() { return mIsExpired; }

  bool& GetIsExpiredRef() { return mIsExpired; }

  Widget* GetParentWidget() { return mParentWidget; }
  TexturePtr& GetTexture() { return mTexture; }

  /**
   * @brief 활성화 토글 함수입니다.
   * 만약 해당 위젯이 활성화 되어있다면 비활성화 시킵니다.
   *
   */
  void ActivateToggle() { mIsActivate = !mIsActivate; }

  /**
   * @brief 해당 위젯을 만료 시킵니다. 부모 위젯까지 만료 메세지가 전파됩니다.
   */
  void Expire();

 private:
 protected:
  Rect mPosition;                   // 위젯의 위치 정보
  WidgetList mChildren;             // 자식 위젯 틀
  TexturePtr mTexture;              // 위젯의 텍스쳐
  Widget* mParentWidget = nullptr;  // 부모 위젯

  bool mIsActivate;   // 활성화되면 True
  bool mIsFocusable;  // 포커스를 잡을 수 있는 위젯이면 True
  bool mIsExpired = true; // 만약 Widget이 만료되었을경우 True ( 다시 그려야 할 경우 )
 
};

typedef std::shared_ptr<Widget> WidgetPtr;

/**
 * @brief 위젯을 생성합니다.
 *
 * @param inPosition 위젯의 위치
 *
 * @return 위젯 핸들러
 */
WidgetPtr CreateWidget(const Rect& inPosition);

/**
 * @brief RootWidget을 생성합니다. 이제는 사용하지 마십시오
 *
 * @return 위젯 핸들러
 */
WidgetPtr CreateWidget();

/**
 * @brief 윈도우 사이즈 위젯을 생성합니다. 
 *
 * @return 
 */
WidgetPtr CreateWindowSizeWidget();

