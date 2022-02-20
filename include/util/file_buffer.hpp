
/**
 * @brief 파일버퍼입니다.
 * 바이너리 
 * 소멸자로 인하여 자동으로 해당 버퍼는 삭제됩니다.
 * NOTE 해당 파일 버퍼로 FONT를 로드할 경우 예기치 못한 동작이 발생됨
 * Font가 로드될때 정확히 어떠한 동작을 하는지 모르겠음
 * 또한 다른 것들도 마찬가지임 Texture 는 해당 버퍼로 로드하였을때 잘 동작하였으나
 * Music, Chunk, Font 등은 잘 동작하지 않고 예기치 못한 동작이 발생될 확률이 있음
 * 이것을 사용하여 파일을 로드하는 것보다. Native라이브러리에서 지원하는 파일 로드 함수를
 * 이용하여 파일을 로드하는 것을 추천
 * ConstFileBuffer 는 사용 X
 */

class ConstFileBuffer {
public:
    ConstFileBuffer( const char * inFileName ) { LoadFile( inFileName ); }
    ~ConstFileBuffer() { Release(); }

    char * GetMemory() const { return mMemory;}
    size_t GetMemorySize() const { return mMemorySize; }

    bool IsInit() const { return mMemory; }
private:
    void LoadFile( const char * inFileName );
    void Release();
private:
    char * mMemory = nullptr;
    size_t mMemorySize = 0;
};
