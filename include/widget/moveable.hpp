
/**
 * @brief Moveable 위젯
 * NOTE Moveable위젯은 해당 위젯이 클릭후 mouse_down 이 발생할 경우
 * 마우스 클릭후 마우스 모션 발생시 모션값에 따라서 TargetWidget의 위치를
 * 이동시킵니다. TargetWidget 을 이동시킬 수 있는 위젯입니다.
 */
class Moveable : public Widget {
 public:
  SN_WIDGET_CLASS_IDENTIFIER_SUB(WidgetClass::Moveable)
  /**
   * @brief 기본적으로 위젯은 타겟을 가질 수 없습니다.
   */
  Moveable(const Rect& inPosition, Widget* inTargetWidget)
      : Widget(inPosition, true, true), mTargetWidget(inTargetWidget) {}
  Moveable(const Rect& inPosition) 
      : Moveable( inPosition, this ) {}
  virtual ~Moveable() {}

 private:
  /**
   * @brief 이벤트를 핸들링합니다.
   *
   * @param inEvent
   */
  virtual void HandleEvent(const Event& inEvent) override;

 private:
  virtual void OnMouseHover() override { mIsMouseHover = true; }
  virtual void OnMouseUnHover() override { mIsMouseHover= false; }

  void HandleMouseMotionEvent(const Event& inEvent);

  // 타겟을 RelX, RelY 만큼 이동합니다.
  void MoveTarget(int inRelX, int inRelY);
 private:
  Widget* mTargetWidget;
  bool mIsMouseHover= false; 
};

WidgetPtr CreateMoveable(const Rect& inPosition, Widget* inTarget);

WidgetPtr CreateMoveable(const Rect& inPosition);
