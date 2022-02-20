#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {
    Widget::Widget(const Rect& inPosition, bool inIsActivate, bool inIsFocusable)
        : mPosition( inPosition ) , mIsActivate( inIsActivate ), mIsFocusable( inIsFocusable )
{
    mTexture = CreateBlendModeTexture( inPosition.mWidth, inPosition.mHeight );
    if ( ! mTexture->IsInit() ) {
        LOG(LogLevel::Warn, "Widget의텍스처가 생성되지 않았습니다.");
    } 
}


void Widget::Render(const TexturePtr& inParentTexture) const {
    ColorEx focus_color(243,34,34);
    ColorEx background_color(0,0,0);
    const auto& focus_widget = GuiEngine::sInstance->GetFocusWidget();

    RenderFillRectToTextureWithColor(mPosition, inParentTexture, background_color );
    if ( focus_widget.get() == this ) {
        RenderRectToTextureWithColor(mPosition,inParentTexture,focus_color);
    } else {
        RenderRectToTexture(mPosition,inParentTexture);
    }
}

void Widget::ForwardEvent( const Event& inEvent ) {
    switch( inEvent.type ) {
        case EventType::ON_CLICK:
            OnClick();
            break;
        case EventType::ON_FOCUS:
            OnFocus();
            break;
        case EventType::ON_UNFOCUS:
            OnUnFocus();
            break;
        case EventType::HOVER:
            OnMouseHover();
            break;
        case EventType::UNHOVER:
            OnMouseUnHover(); 
            break;
        default:
            HandleEvent( inEvent );
            break;
    }
}

void Widget::AddChildWidget(const WidgetPtr& inWidget) {
  if ( inWidget == nullptr ) {
      return; 
  }

  auto&& child_widget = inWidget; 
  child_widget->mParentWidget = this;

  mChildren.push_back(child_widget);
}

void Widget::Expire() {
    util::ExpireRecursive( this );
}

WidgetPtr CreateWidget(const Rect& inPosition) {
  return WidgetPtr(new Widget(inPosition));
}

WidgetPtr CreateWidget() {
  RectEx rect(0, 0, 1000, 1000);
  return CreateWidget(rect);
}

WidgetPtr CreateWindowSizeWidget() {
  auto& window_ptr= WindowManager::sInstance->GetWindow();

  int window_width = 0;
  int window_height = 0 ;

  window_ptr->GetWindowSize(window_width, window_height );

  RectEx rect(0, 0, window_width, window_height);
  return CreateWidget(rect);
}
}  // namespace widget
}  // namespace sg_media
