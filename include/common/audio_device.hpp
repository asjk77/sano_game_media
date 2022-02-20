
/**
 * @brief Audio 장치입니다. 해당 클래스는 전역 클래스입니다.
 * 이 클래스는 오디오 의 인터페이스 입니다.
 */
class AudioDevice {
 public:
  AudioDevice() {}
  ~AudioDevice() {}

  static std::unique_ptr<AudioDevice> sInstance;
  static void StaticInit();
  static void StaticRelease();

  /**
   * @brief 음악을 재생합니다.
   * @param inMusic
   * @param inRepeatCount 음악 재생 카운트입니다. 만약 -1일경우 무한히
   * 반복재생합니다. 만약 0일경우 음악을 0 번 재생합니다.
   */
  void PlayMusic(const MusicPtr& inMusic, int inRepeatCount = -1);

  /**
   * @brief 효과음(청크)를 재생합니다.
   *
   * @param inMusic 청크
   * @param inChannel 채널 -1 일경우 가장 가까운 채널
   * @param inLoop 루프 수입니다. 만약 -1은 무한 루프입니다. 하나를1을 전달하면 1루프 즉 두번 재생합니다.
   */
  void PlayChannel(const ChunkPtr& inChunk, int inChannel = -1, int inLoop = 0);
  /**
   * @brief 음악을 정지합니다.
   */
  void PauseMusic();

  bool IsPausedMusic();

  bool IsPlayingMusic();

  /**
   * TODO CHUNK를 재생하는 인터페이스를 추가합니다.
   */
  void SetVolume();
};

/**
 * @brief 음악을 재생합니다.
 *
 * @param inKey
 */
void PlayMusicFromKey( const SoundKey&& inKey );

