#include <sano_game_media_pch.hpp>

namespace sg_media {

std::unique_ptr<AudioDevice> AudioDevice::sInstance;
void AudioDevice::StaticInit() {
  // AudioDevice를 초기화 합니다.
  bool result = platform::OpenAudio();

  if ( result == false ) {
    LOG(LogLevel::Info, ls::AUDIO_DEVICE_INIT_ERROR );
    throw Exception(ls::AUDIO_DEVICE_INIT_ERROR);
  }
  sInstance.reset(new AudioDevice());
  LOG(LogLevel::Info, ls::AUDIO_DEVICE_INIT_COMPLETION);
}
void AudioDevice::StaticRelease() {
    // 오디오를 닫습니다.
    platform::CloseAudio();
    sInstance.reset();
}

void AudioDevice::PlayMusic( const MusicPtr& inMusic, int inRepeatCount ) {
    if ( inMusic == nullptr ) return;
    platform::PlayMusic( inMusic->mM, inRepeatCount );
}

void AudioDevice::PlayChannel(const ChunkPtr& inChunk, int inChannel, int inLoop) {
    if ( inChunk == nullptr ) return;
    platform::PlayChannel(inChannel, inChunk->mC, inLoop );
}
void AudioDevice::PauseMusic() {
    platform::PauseMusic();
}

bool AudioDevice::IsPausedMusic() {
    return platform::IsPausedMusic();
}


bool AudioDevice::IsPlayingMusic() {
    return platform::IsPlayingMusic();
}

void PlayMusicFromKey( const SoundKey&& inKey ) {
    auto&& music_ptr = SoundRegistry::sInstance->GetMusic( inKey );
    
    if ( music_ptr == nullptr ) {
        return;
    }
    AudioDevice::sInstance->PlayMusic( music_ptr );
}


}  // namespace sg_media
