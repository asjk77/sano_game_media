// DEBUG 뷰를정의합니다.
class DebugView {
 public:
  DebugView() {}
  virtual ~DebugView() {}

  static std::unique_ptr<DebugView> sInstance;
  static void StaticInit() { sInstance.reset(new DebugView()); }
  static void StaticRelease() { sInstance.reset(); }

  virtual void Render();
  virtual void Update();

  void SetDebugTarget(Debuggable* inTarget) { mDebugTarget = inTarget; }
 protected:
  void RenderMousePos(int inDrawPosX, int inDrawPosY);

  /**
   * @brief 태겟을 랜더링합니다. DebugView를 상속받으십시오
   *
   */
  void RenderTarget(int inDrawPosX, int inDrawPosY);
  void RenderWidgetInfo(widget::Widget* inWidget, int inDrawPosX, int inDrawPosY);

  void RenderLastLog(int inDrawPosX, int inDrawPosY);
 protected:
  Debuggable* mDebugTarget = nullptr;
};

