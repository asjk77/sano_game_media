
/**
 * @brief Board 위젯
 * 이미지를 가지고 있는 위젯입니다.
 */
// Widget(const Rect& inPosition)
// : mPosition(inPosition), mParentWidgetPointer(nullptr) {}

class Board : public Widget {
 public:
  Board(const Rect& inPosition, ImagePtr& inBoardImage)
      : Widget(inPosition), mBoardImage(inBoardImage) {}
  virtual ~Board() {}

  virtual void Render(const TexturePtr& inParentTexture) const override;

 private:
  ImagePtr mBoardImage;
};

/**
 * @brief 보드 위젯을 생성합니다.
 *
 * @param inPosition 위젯의 위치
 * @param inBoardImage 보드이미지
 *
 * @return 보드 위젯 핸들
 */
WidgetPtr CreateBoard(const Rect& inPosition, ImagePtr& inBoardImage);

