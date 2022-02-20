#include <sano_game_media_pch.hpp>

namespace sg_media {
void KeyInputManager::SetKey(KeyCode inCode, ActionFunc inAction) {
    mActionList[inCode] = inAction;
}
void KeyInputManager::DoAction( key::KeyCode inCode ) {
    auto& action = mActionList[inCode];

    if ( action == nullptr )
        return;

    // 엑션을 실행합니다.
    action();
}


}
