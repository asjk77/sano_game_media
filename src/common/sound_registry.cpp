#include <sano_game_media_pch.hpp>

namespace sg_media {
std::unique_ptr<SoundRegistry> SoundRegistry::sInstance;
void SoundRegistry::RegisterChunk(SoundKey& inKey, const ChunkPtr& inChunk) {
  mChunks[inKey] = inChunk;
}
void SoundRegistry::RegisterMusic(SoundKey& inKey, const MusicPtr& inMusic) {
  mMusics[inKey] = inMusic;
}

const ChunkPtr& SoundRegistry::GetChunk(const SoundKey& inKey) {
  return mChunks[inKey];
}
const MusicPtr& SoundRegistry::GetMusic(const SoundKey& inKey) {
  return mMusics[inKey];
}

void CreateMusicAndRegisterFromFile(SoundKey&& inKey, const char* inFile) {
  auto&& music_ptr = CreateMusicFromFile(inFile);

  // TODO Music이 없을시 로그를 작성합니다.
  SoundRegistry::sInstance->RegisterMusic(inKey, music_ptr);
}
void CreateChunkAndRegisterFromFile(SoundKey&& inKey, const char* inFile) {
  auto&& chunk_ptr = CreateChunkFromFile(inFile);
  // TODO Chunk이 없을시 로그를 작성합니다.
  SoundRegistry::sInstance->RegisterChunk(inKey, chunk_ptr);
}

}  // namespace sg_media
