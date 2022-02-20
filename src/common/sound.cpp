#include <sano_game_media_pch.hpp>

namespace sg_media {
void Music::Release() {
  if (mM) platform::FreeMusic(mM);
}
void Chunk::Release() {
  if (mC) platform::FreeChunk(mC);
}

MusicPtr CreateMusicFromMemory(const char* inMemory, size_t inMemorySize) {
  auto music_ptr = platform::LoadMusicFromMemory(inMemory, inMemorySize);

  return MusicPtr(new Music(music_ptr));
}

MusicPtr CreateMusicFromFile(const char* inFile) {
    auto music_ptr = platform::LoadMusicFromFile( inFile );

  return MusicPtr( new Music( music_ptr ));
}

ChunkPtr CreateChunkFromMemory(const char* inMemory, size_t inMemorySize) {
  auto chunk_ptr = platform::LoadChunkFromMemory(inMemory, inMemorySize);

  return ChunkPtr(new Chunk(chunk_ptr));
}

ChunkPtr CreateChunkFromFile(const char* inFile) {
  auto chunk_ptr = platform::LoadChunkFromFile( inFile );

  return ChunkPtr(new Chunk(chunk_ptr));
}

}  // namespace sg_media
