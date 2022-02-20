/**
 * @brief 위젯 클레스 아이디를 정의합니다.
 */
enum class WidgetClass  {
    Widget,
    Board,
    Moveable,
    BaseButton,
    Button,
    UNKNOWN
};

const char * GetWidgetClassString();
