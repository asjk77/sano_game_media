

/**
 * @brief StaticWidget을 생성합니다.
 *
 * @param inPosX 생성할 좌표X
 * @param inPosY 생성할 좌표Y
 * @param inFont 폰트
 * @param inString_UTF8 문자열(UTF8)
 * @param inColor 생성될 StaticWidget의 색을 구합니다.
 *
 * @return Widget Handle
 */
WidgetPtr CreateStaticWidget(int inPosX, int inPosY, FontPtr& inFont,
                             const char* inString_UTF8, Color& inColor);

/**
 * @brief 기본 폰트, 기본 글자색으로 StringWidget을 생성합니다.
 *
 * @param inPosX 생성할 좌표X
 * @param inPosY 생성할 좌표Y
 * @param inString_UTF8 UTF8
 *
 * @return
 */
WidgetPtr CreateStaticWidget(int inPosX, int inPosY, const char* inString_UTF8);

