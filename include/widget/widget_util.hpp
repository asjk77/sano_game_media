namespace util {

typedef void (*ExcuteFunction)(WidgetPtr& inWidget, const Event& inEvent);

/**
 * @brief 점과 위젯의 충돌을 찾고 찾은위젯을 실행시킵니다. (단 한개의 위젯을
 * 찾습니다.)
 *
 * @param inRoot 최상위 위젯
 * @param inPointPosX 점 x
 * @param inPointPosY 점 y
 * @param inExcute 실행 함수
 * @param inEvent 실행 함수에 들어갈 이벤트
 */
void FindCollisionWidgetToDotAndExcute(const WidgetPtr& inRoot,
                                       int inPointPosX, int inPointPosY,
                                       ExcuteFunction inExcute, const Event& inEvent);

/**
 * @brief 재귀적으로 부모에게 만료 메세지를 전달합니다.
 *
 * @param inWidget
 */
void ForwardExpiredMessageRecursive(const Widget::WidgetPtr& inWidget);

/**
 * @brief 위젯을 랜더링 합니다.
 *
 * @param inWidget 위젯을
 */
void RenderWidget(const WidgetPtr& inRoot);

/**
 * @brief 위젯을 업데이트 합니다.
 *
 * @param inWidget 위젯
 */
void UpdateWidget(const WidgetPtr& inWidget);

/**
 * @brief 재귀적으로 위젯을 만료시킵니다.
 * 만료된 위젯은 RenderWidget에서 다시 그려야 합니다.
 *
 * @param inParent
 */
void ExpireRecursive(Widget* inParent);


}  // namespace util
