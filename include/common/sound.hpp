/**
 * @brief 음악 객체입니다.
 * 백그라운드 음악으로 사용할 수 있습니다.
 * mp3 파일을 이용하여 생성할 수 있습니다.
 */
class Music {
 public:
     Music( platform::MusicPtr inM ) : mM(inM) {}
     ~Music() {Release();}
     friend class AudioDevice;

     void Release();
 private:
  platform::MusicPtr mM;
};

typedef std::shared_ptr< Music > MusicPtr;

/**
 * @brief 메모리로부터 Music 객체를 생성합니다.
 *
 * @param inMemory 메모리
 * @param inMemorySize 메모리의 사이즈
 *
 * @return 
 */
MusicPtr CreateMusicFromMemory(const char * inMemory, size_t inMemorySize );
MusicPtr CreateMusicFromFile(const char * inFile);
/**
 * @brief 효과음(청크) 객체입니다.
 */
class Chunk {
 public:
     Chunk(platform::ChunkPtr inC) : mC(inC) {}
     ~Chunk() { Release(); }
     friend class AudioDevice;

     void Release();
 private:
  platform::ChunkPtr mC;
};

typedef std::shared_ptr<Chunk> ChunkPtr;

/**
 * @brief 청크를 메모리로부터 로드합니다.
 *
 * @param inMemory 메모리
 * @param inMemorySize 메모리 사이즈
 *
 * @return 
 */
ChunkPtr CreateChunkFromMemory(const char * inMemory, size_t inMemorySize );
ChunkPtr CreateChunkFromFile(const char * inFile);
