typedef sg_global::Exception Exception;
typedef sg_global::Logger Logger;
typedef sg_global::LogLevel LogLevel;

typedef std::string string;

inline Logger& gLogger = sg_global::gLogger;

typedef sg_global::time_point time_point;

namespace external {
    typedef sg_global::LogListener LogListener;
}

inline time_point GetTime() { return sg_global::GetTime(); }

namespace widget {
    class Widget;
}

struct Rect {
  int mX;
  int mY;
  int mWidth;
  int mHeight;
};

class RectEx : public Rect {
 public:
  RectEx(int inX, int inY, int inWidth, int inHeight) {
    mX = inX;
    mY = inY;
    mWidth = inWidth;
    mHeight = inHeight;
  }
  ~RectEx() {}

  void GetCenterPos(int& outPosX, int& outPosY) {
    outPosX = mX + (mWidth / 2);
    outPosY = mY + (mHeight / 2);
  }
  bool IsCollide(int inPosX, int inPosY) {
    if (mX > inPosX) return false;
    if (mX + mWidth < inPosX) return false;
    if (mY > inPosY) return false;
    if (mY + mHeight < inPosY) return false;

    return true;
  }
  // Rect 를 이동합니다.
  void Move(int inPosX, int inPosY) {
      mX = mX + inPosX;
      mY = mY + inPosY;
  }
};

struct RectF {
  float mX;
  float mY;
  float mWidth;
  float mHeight;
};

class RectFEx : public RectF {
 public:
  RectFEx(float inX, float inY, float inWidth, float inHeight) {
    mX = inX;
    mY = inY;
    mWidth = inWidth;
    mHeight = inHeight;
  }
  ~RectFEx() {}

  void GetCenterPos(float& outPosX, float& outPosY) {
    outPosX = mX + (mWidth / 2);
    outPosY = mY + (mHeight / 2);
  }
  bool IsCollide(float inPosX, float inPosY) {
    // if (mX > inPosX) return false;
    // if (mX + mWidth < inPosX) return false;
    // if (mY > inPosY) return false;
    // if (mY + mHeight < inPosY) return false;

    if (inPosX < mX) return false;
    if (mX + mWidth < inPosX) return false;
    if (inPosY < mY) return false;
    if (mY + mHeight < inPosY) return false;
    return true;
  }
};

// Color
struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

class ColorEx : public Color {
 public:
  ColorEx(uint8_t inR, uint8_t inG, uint8_t inB, uint8_t inA = 255) {
    r = inR;
    g = inG;
    b = inB;
    a = inA;
  }
};
