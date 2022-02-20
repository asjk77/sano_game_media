
/**
 * @brief 키 입력 가능한 위젯입니다.
 * 기본적으로 키 입력 관리자를 포함합니다.
 */
class KeyInputable : public Widget {
 public:
  // 기본적으로 KeyInputableWidget은
  KeyInputable(const Rect& inPosition) : Widget(inPosition, true, true) {}
  virtual ~KeyInputable() {}

  KeyInputManager& GetKeyInputManager() { return mKeyInputManager; }

  /**
   * @brief 이벤트를 핸들링합니다.
   *
   * @param inEvent
   */
  virtual void HandleEvent(const Event& inEvent) override;
 private:

  /**
   * @brief 키Down을 처리합니다.
   * 실제로 하는 일은 KeyInputManager에 키 값에 맞는 액션을 실행합니다.
   *
   * @param inEvent
   */
  void ProcessKeyDown( const Event& inEvent );
 private:
  KeyInputManager mKeyInputManager;
};

inline WidgetPtr CreateKeyInputable(const Rect& inPosition) {
    return WidgetPtr( new KeyInputable( inPosition ) );
} 

// KeyInputableWidget 의 포인터도 얻습니다.
inline WidgetPtr CreateKeyInputable(const Rect& inPosition, KeyInputable*& outNewWidget) {
    outNewWidget = new KeyInputable( inPosition );
    return WidgetPtr( outNewWidget );
}

WidgetPtr CreateWindowSizeKeyInputable(KeyInputable*& outNewWidget );

