#include <sano_game_media_pch.hpp>

namespace sg_media {

namespace widget {

namespace {
ColorEx black_color(0, 0, 0);
ColorEx blue_color(0, 0, 255);
}  // namespace

/**
 * 마우스가 호버링 되었을경우 blue_color를 드로우하고
 * 아닐경우 black_color로 위젯을 랜더링 합니다.
 */
void BaseButton::Render(const TexturePtr& inParentTexture) const {
  Color old_render_color;
  GraphicsDevice2d::sInstance->GetRenderColor(old_render_color);

  Color& draw_color = mIsHover ? blue_color : black_color;
  GraphicsDevice2d::sInstance->SetRenderColor(draw_color);
  Widget::Render( inParentTexture );


  GraphicsDevice2d::sInstance->SetRenderColor(old_render_color);
}
void BaseButton::OnMouseHover() {
    mIsHover = true;
    Expire();
}
void BaseButton::OnMouseUnHover() {
    mIsHover = false;
    Expire();
}

WidgetPtr CreateBaseButton(const Rect& inPosition, ClickFunc inClickFunc) {
  return WidgetPtr(new BaseButton(inPosition, inClickFunc));
}

void BaseButton::OnClick() {
    if ( mClickFunc )
        mClickFunc();
}
void Button::Render(const TexturePtr& inParentTexture ) const {
    // 호러링 일때는 hoverImage를 랜더링하고 아닐때는 NomalImage를 랜더링 합니다.
    if ( mIsHover ) {
        mHoverImage->Render( inParentTexture, mPosition );
    } else {
        mNomalImage->Render( inParentTexture, mPosition );
    }
}

}  // namespace widget
}  // namespace sg_media
