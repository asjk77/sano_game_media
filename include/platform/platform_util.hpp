
namespace platform {
namespace util {
typedef void (*QuitEventFunc)();
typedef void (*InputEventFunc)();

struct EventHandler {
    QuitEventFunc mQuitEventHandler;
};

/**
 * @brief 이벤트를 처리합니다.
 * 이 함수는 이벤트가 없을경우 Non Blocking 됩니다.
 *
 * @param inEventHandler 이벤트 핸들러를 정의
 */
void ProcessPollEventAdapter(const EventHandler& inEventHandler) noexcept;

/**
 * @brief 이벤트를 처리합니다. 
 * 이 함수는 이벤트가 없을경우 Blockng 이 됩니다.
 * 만약 게임 프로젝트가 아닐경우 이 함수를 사용해서 자원을 아낄수 있습니다.
 *
 * @param inEventHandler
 */
void ProcessWaitEventAdapter(const EventHandler& inEventHandler) noexcept;
}  // namespace util
}  // namespace platform
