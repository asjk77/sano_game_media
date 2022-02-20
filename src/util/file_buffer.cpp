#include <fstream>
#include <sano_game_media_pch.hpp>

using namespace std;
namespace sg_media {
namespace util {
void ConstFileBuffer::LoadFile(const char* inFileName) {
  std::ifstream is(inFileName, std::fstream::binary);

  if (is.is_open()) {
    // 파일
    is.seekg(0, is.end);
    mMemorySize = is.tellg();
    is.seekg(0, is.beg);

    // allocate memory:
    mMemory= static_cast<char *> (malloc( mMemorySize ));

    // read data as a block:
    is.read(mMemory , mMemorySize );
  }
}

void ConstFileBuffer::Release() {
  if (mMemory) 
      free( mMemory );
}
}  // namespace util
}  // namespace sg_media
