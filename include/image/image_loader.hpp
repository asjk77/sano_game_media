typedef std::vector<ImagePtr> ImageList;

/**
 * @brief 이미지 로더입니다.
 * 이미지로더가 하는일은 Texture를 일정한 크기만큼 쪼개어서
 * 여러개개의 Image 를 생성합니다. 
 */
class ImageLoader {
 public:
  /**
   * @brief 이미지 로더를 초기화합니다.
   *
   * @param inTarget 타겟 텍스처입니다.
   * @param inCellWidth 셀의 너비
   * @param inCellHeight 셀의 높이
   * @param inStartOffsetX 시작 Offset X
   * @param inStartOffsetY 시작 Offset Y
   * @param inMaxCell 셀의 수 텍스처를 몇개의 Image를 ₩ 
   * @param inMaxCellRowCount 
   * @param inMaxCollCount 셀의 Colum 수
   */
  ImageLoader(TexturePtr& inTarget, uint32_t inCellWidth, uint32_t inCellHeight,
              uint32_t inStartOffsetX, uint32_t inStartOffsetY,
              uint32_t inMaxCellCount, uint32_t inMaxCellRowCount,
              uint32_t inMaxCellColCount)
      : mTarget(inTarget),
        mCellWidth(inCellWidth),
        mCellHeight(inCellHeight),
        mStartOffsetX(inStartOffsetX),
        mStartOffsetY(inStartOffsetY),
        mMaxCellCount(inMaxCellCount),
        mMaxCellRowCount(inMaxCellRowCount),
        mMaxCellColCount(inMaxCellColCount) {}
  virtual ~ImageLoader() {}

  bool LoadImageList(ImageList& outImageList);

  
 protected:
  
  /**
   * @brief 모든 Cell을 처리합니다.
   *
   * @param outImageList
   */
  void ProcessCellList(ImageList& outImageList);

  /**
   * @brief Cell을 처리합니다.
   *
   * @param outImageList 출력할 이미지들
   * @param inCurrentOffsetX 현제 Cell의 offsetX
   * @param inCurrentOffsetY 현제 Cell의 offsetY
   */
  virtual void ProcessCell(ImageList& outImageList, uint32_t inCurrentOffsetX,
                       uint32_t inCurrentOffsetY);

 private:
  TexturePtr mTarget;
  uint32_t mCellWidth;
  uint32_t mCellHeight;

  uint32_t mStartOffsetX;
  uint32_t mStartOffsetY;

  uint32_t mMaxCellCount;     // 전체 Cell 이 몇개인지 
  uint32_t mMaxCellRowCount;  // 행에 몇개의 Cell 이 들어갈지
  uint32_t mMaxCellColCount;  // 열에 몇개의 Cell 이 들어갈지
};

