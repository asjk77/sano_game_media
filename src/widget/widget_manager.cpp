#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {
std::unique_ptr<WidgetManager> WidgetManager::sInstance;

void WidgetManager::StaticInit() {
    auto&& base_widget = CreateWidget(); // 기본 위젯을 설정합니다.
    sInstance.reset( new WidgetManager( base_widget ));
    LOG(LogLevel::Info, ls::widget::WIDGET_MANAGER_INIT_COMPLETION);
}

void WidgetManager::RegisterWidget(WidgetKey& inKey, WidgetPtr& inWidget) {
  auto&& dest_widget = mWidgetMap[inKey];
  if (dest_widget) {  // 값이 있을 경우
    LOG(LogLevel::Warn, ls::widget::WIDGET_MANAGER_WIDGET_DUPLICATE_REGISTER_, inKey.c_str());
  }
  dest_widget = inWidget; 
}
WidgetPtr& WidgetManager::GetWidget(WidgetKey& inKey) {
  auto&& widget_iter = mWidgetMap.find(inKey);

  if (widget_iter == mWidgetMap.end()) {  // not found
    return mBaseWidget;
  }

  return widget_iter->second;
}

WidgetPtr CreateWidgetAndRegister(const Rect& inPosition, WidgetKey& inKey) {
    auto && widget_ptr = CreateWidget( inPosition );
    WidgetManager::sInstance->RegisterWidget( inKey , widget_ptr );
    return WidgetPtr( widget_ptr );
}

WidgetPtr CreateBoardAndRegister(const Rect& inPosition, ImagePtr& inBoardImage, WidgetKey& inKey) {
    auto && widget_ptr = CreateBoard( inPosition, inBoardImage );
    WidgetManager::sInstance->RegisterWidget( inKey, widget_ptr );
    return WidgetPtr( widget_ptr );
}

WidgetPtr CreateBaseButtonAndRegister( const Rect& inPosition, ClickFunc inClickFunc, WidgetKey& inKey ) {
    auto && widget_ptr = CreateBaseButton( inPosition, inClickFunc );
    WidgetManager::sInstance->RegisterWidget( inKey, widget_ptr );
    return WidgetPtr(widget_ptr);
}

WidgetPtr CreateStaticWidgetAndRegister(int inPosX, int inPosY, FontPtr& inFont,
                                        const char* inString_UTF8,
                                        Color& inColor, WidgetKey& inKey) {
    auto&& static_widget = CreateStaticWidget( inPosX, inPosY, inFont, inString_UTF8, inColor );
    WidgetManager::sInstance->RegisterWidget( inKey, static_widget );

    return WidgetPtr( static_widget );
}

}  // namespace widget
}  // namespace sg_media
