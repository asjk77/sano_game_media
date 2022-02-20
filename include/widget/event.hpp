/**
 * 위젯 이벤트를 정의합니다.
 */
enum class EventType : uint32_t {
  UNKNOWN, // 알수 없는 이벤트입니다.

  // mouse event type
  MOUSE_BUTTON_DOWN,   // LEFT BUTTON_DOWN 이벤트입니다.
  MOUSE_BUTTON_UP,     // 마우스 래프트 버튼 이벤트입니다.

  // MouseMotionEvent
  MOUSE_MOTION,           // 마우스 모션 이벤트입니다.

  // mout wheel event
  MOUSE_WHEEL,              // 키보드 흴 이벤트입니다.

  // keyboard event type
  KEYBOARD_KEY_UP,    // 키보드 키 UP 이벤트입니다. 
  KEYBOARD_KEY_DOWN,  // 키보드 키 Down 이벤트입니다.

  // 지금 부터 발생하는 이벤트들은 따로 인자 없이 발생됩니다.
  HOVER,      // 마우스에 위젯이 Hover 되었을 경우 발생합니다. 
  UNHOVER,     // 마우스에 위젯이 UnHover 되었을 경우 발생합니다.

  ON_FOCUS,         // 위젯이 포커스를 가질때 발생합니다.
  ON_UNFOCUS,       // 위젯이 포커스를 가지지 않을때 발생합니다.
  ON_CLICK          // 클릭 이벤트 를 발생시킵니다. // MouseButtonUp/Down 과 다른 이벤트입니다.
};


struct MouseMotionEvent {
    EventType type;
    uint32_t x; // 창에 대한 마우스의 x 좌표
    uint32_t y; // 창에 대한 마우스의 y 좌표
    uint32_t rel_x; // 상대 x 좌표
    uint32_t rel_y; // 상대 y 좌표
};

enum class MouseButton : uint8_t {
    BUTTON_LEFT,    // 왼쪽 버튼
    BUTTON_MIDDLE,  // 중앙 버튼
    BUTTON_RIGHT,   // 오른쪽 버튼
    BUTTON_X1,      // 마우스 버튼 x1 (보통 게이밍 마우스 사이드 버튼 )
    BUTTON_X2,      // 마우스 버튼 x2
};

struct MouseEvent {
    EventType type;
    uint32_t x;         // 창에 대한 마우스의 좌표 x
    uint32_t y;         // 창에 대한 마우스의 좌표 y
    MouseButton button; // 어느 마우스 버튼인가? 
};

struct KeyBoardEvent {
    EventType type;
    key::Scancode scan_code; // os 에 가공되지 않은 키값
    key::KeyCode key_code; // os 에 가공된 키값
};


/**
 * @brief Widget Event 공용체입니다.
 */
union Event {
    EventType type;
    struct MouseEvent mouse;
    struct MouseMotionEvent mouse_motion;

    struct KeyBoardEvent keyboard;
};
