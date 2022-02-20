#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace widget {

void Board::Render(const TexturePtr& inParentTexture) const {
  mBoardImage->Render( inParentTexture, mPosition );
}

WidgetPtr CreateBoard(const Rect& inPosition, ImagePtr& inBoardImage) {

    // return WidgetPtr( new Board(inPosition, inBoardImage) );
    return WidgetPtr( new class Board( inPosition, inBoardImage) );
}


}  // namespace widget
}  // namespace sg_media
