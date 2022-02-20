typedef std::string SoundKey;

class SoundRegistry {
 public:
  SoundRegistry() {}
  ~SoundRegistry() {}

  static std::unique_ptr<SoundRegistry> sInstance;
  static void StaticInit() { sInstance.reset(new SoundRegistry()); }
  static void StaticRelease() { sInstance.reset(); }

  /**
   * @brief Chunk 를 저장합니다.
   *
   * @param inKey
   * @param inMusic
   */
  void RegisterChunk(SoundKey& inKey, const ChunkPtr& inChunk);

  /**
   * @brief Music 를 저장합니다.
   *
   * @param inKey
   * @param inMusic
   */
  void RegisterMusic(SoundKey& inKey, const MusicPtr& inMusic);

  /**
   * @brief Chunk를 얻습니다.
   *
   * @param inKey 
   *
   * @return Chunk 객체
   */
  const ChunkPtr& GetChunk(const SoundKey& inKey);

  /**
   * @brief Music를 얻습니다.
   *
   * @param inKey
   *
   * @return 음악 객체
   */
  const MusicPtr& GetMusic(const SoundKey& inKey);

 private:
  typedef std::unordered_map<SoundKey, MusicPtr> SoundKeyToMusicMap;
  typedef std::unordered_map<SoundKey, ChunkPtr> SoundKeyToChunkMap;

  SoundKeyToChunkMap mChunks;
  SoundKeyToMusicMap mMusics;
};


/**
 * @brief Music을 파일에서 생성및 등록합니다.
 *
 * @param inKey 등록할 키
 * @param inFile 파일 경로
 *
 * @return 성공시 true 실패시 false
 */
void CreateMusicAndRegisterFromFile( SoundKey&& inKey, const char * inFile );

/**
 * @brief Chunk(wav)을 파일에서 생성및 등록합니다.
 *
 * @param inKey 등록할 키
 * @param inFile 파일 경로
 *
 * @return 성공시 true 실패시 false
 */
void CreateChunkAndRegisterFromFile( SoundKey&& inKey, const char * inFile );
