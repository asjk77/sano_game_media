#include <sano_game_media_pch.hpp>

namespace sg_media {
void Image::Render( const TexturePtr& inDest, const Rect& inDestRect ) const {
    RenderTextureToTexture(mBoard, mFocusRect, inDest, inDestRect );
}

void Image::Render( const TexturePtr& inDest, const RectF& inDestRect ) const {
    RenderTextureToTexture(mBoard, mFocusRect, inDest, inDestRect );
}

void Image::Render( const Rect& inDestRect ) const {
    GraphicsDevice2d::sInstance->RenderTexture(mBoard, mFocusRect, inDestRect);
}

ImagePtr CreateImage(TexturePtr& inBoard, Rect& inFocusRect) {
  return ImagePtr(new Image(inBoard, inFocusRect));
}

ImagePtr CreateImage(TexturePtr& inBoard) {
  int board_width = 0;
  int board_height = 0;
  inBoard->GetInfo(board_width, board_height);

  RectEx focus_rect(0, 0, board_width, board_height);

  return CreateImage(inBoard, focus_rect);
}

}  // namespace sg_media
