
/**
 * @brief 키보드 입력 관리자입니다.
 * 키코드에 엑션을 실행시켜서 실행합니다.
 * sano_game_media 에서 사용받아서 실행합니다.
 * relation : KeyInputableWidget
 */
class KeyInputManager {
 public:
  typedef void (*ActionFunc)();
  typedef key::KeyCode KeyCode;
  KeyInputManager() { }
  virtual ~KeyInputManager() {}

  void SetKey(KeyCode inCode, ActionFunc inAction);

  /**
   * @brief 키코드에 대한 엑션을 수행합니다.
   */
  void DoAction( KeyCode inCode );
 protected:
  // 키코드를 인덱스로 사용하는 ActionFunc의 리스트입니다.
  typedef std::unordered_map<KeyCode, ActionFunc> KeyCodeToActionFuncList;
  KeyCodeToActionFuncList mActionList;
};

