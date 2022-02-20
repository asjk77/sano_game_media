typedef std::vector<Rect> RectList;
/**
 * @brief 이미지 스플라이트 애니메이션
 */
class ImageSpriteAnimation : public Image {
 public:
  /**
   * @brief 이미지 스플라이트 에니메이션을 초기화 합니다.
   *
   * @param inBoard 원본이 되는 텍스처입니다.
   * @param inFrameRectList 프레임별로 텍스처의 Rect의 리스트를 넣어줍니다.
   */
  ImageSpriteAnimation(TexturePtr& inBoard, RectList& inFrameRectList,
                       time_point inDuration)
      : Image(inBoard, inFrameRectList[0]),
        mFrameRectList(inFrameRectList),
        mDuration(inDuration),
        mCurrentFrameIndex(0),
        mMaxFrameIndex(inFrameRectList.size()-1)
    {}

  virtual ~ImageSpriteAnimation() {}

  virtual void Update(float inSpeed = 1.0f) override;

 private:
  time_point mDuration;     // 업데이트 지연값입니다.
  RectList mFrameRectList;  // 프레임 사각형입니다.

  uint32_t mCurrentFrameIndex; // 현제 프레임 인덱SDL2_MIXER_LIBRARIES스입니다.
  uint32_t mMaxFrameIndex; // 프레임의 최댓값입니다.
 private:
  time_point mNextConvertFrameTime = 0.0f; // 다음 프레임이 변경될 시간입니다.
};

inline ImagePtr CreateImageSpriteAnimation(TexturePtr& inBoard, RectList& inFrameRectList,
                       time_point inDuration) {
    return ImagePtr( new ImageSpriteAnimation(inBoard, inFrameRectList, inDuration) );
}
