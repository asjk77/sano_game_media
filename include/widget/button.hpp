
// Widget(const Rect& inPosition)
// : mPosition(inPosition), mParentWidgetPointer(nullptr) {}

/**
 * @brief 클릭함수의 정의
 *
 * @param void
 *
 * @return void
 */
typedef void (*ClickFunc)();

class BaseButton : public Widget {
 public:
  BaseButton(const Rect& inPosition, ClickFunc inClickFunc)
      : Widget(inPosition), mClickFunc(inClickFunc), mIsHover(false) {}

  virtual void Render(const TexturePtr& inParentTexture) const override;
  virtual void OnClick() override;
  virtual void OnMouseHover() override;
  virtual void OnMouseUnHover() override;

 protected:
  ClickFunc mClickFunc;
  bool mIsHover;
};

/**
 * @brief 기본 버튼 위젯을 생성합니다.
 *
 * @param inPosition 버튼 위치
 * @param inClickFunc 클릭시 호출될 함수
 *
 * @return 버튼 위젯 핸들
 */
WidgetPtr CreateBaseButton(const Rect& inPosition, ClickFunc inClickFunc);

/**
 * @brief 버튼 위젯을 정의합니다.
 * 기본적으로 일반 버튼은 Nomal이미지, Hover 이미지를 요구합니다.
 */
class Button : public BaseButton {
 public:
  Button(const Rect& inPosition, ClickFunc inClickFunc, ImagePtr& inNomalImage,
         ImagePtr& inHoverImage)
      : BaseButton(inPosition, inClickFunc),
        mNomalImage(inNomalImage),
        mHoverImage(inHoverImage) {}
  virtual ~Button() {}

  virtual void Render(const TexturePtr& inParentTexture) const override;

 protected:
  ImagePtr mNomalImage;
  ImagePtr mHoverImage;
};

/**
 * @brief 버튼을 생성합니다.
 *
 * @param inPosition 버튼 위치
 * @param inClickFunc 버튼 클릭 함수
 * @param inNomalImage 노말 이미지
 * @param inHoverImage Hovering 이미지
 *
 * @return 새로 생성될 버튼 위젯 함수
 */
WidgetPtr CreateButton(const Rect& inPosition, ClickFunc inClickFunc,
                       ImagePtr& inNomalImage, ImagePtr& inHoverImage);

WidgetPtr CreateButton_s(const Rect& inPosition, ClickFunc inClickFunc,
                         ImagePtr& inNomalImage, ImagePtr& inHoverImage);
