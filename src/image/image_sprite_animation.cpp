#include <sano_game_media_pch.hpp>

namespace sg_media {

void ImageSpriteAnimation::Update(float inSpeed) {
    time_point current_time = GetTime();

    // 현제 시간이 다음 지연 시간 보다 클 경우 업데이트를 진행합니다.
    if ( current_time > mNextConvertFrameTime )  {
        mNextConvertFrameTime = current_time + ( mDuration * inSpeed );
        // 프레임을 1 증가시킨다.
        mCurrentFrameIndex = mCurrentFrameIndex + 1;
        // 만약 맥스 프레임 보다 현제 프레임이 클경우
        if ( mCurrentFrameIndex > mMaxFrameIndex ) {
            // 현제 프레임을 0초기화 시킨다.
            mCurrentFrameIndex = 0;
        }

        mFocusRect = mFrameRectList[ mCurrentFrameIndex ];
        Expire(); // 해당 위젯을 만료 시킵니다.
    }

}

}
