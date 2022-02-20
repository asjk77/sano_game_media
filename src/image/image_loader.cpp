#include <sano_game_media_pch.hpp>

namespace sg_media {

bool ImageLoader::LoadImageList(ImageList& outImageList) {
  if (!mTarget) return false;

  ProcessCellList(outImageList);
  return true;
}

void ImageLoader::ProcessCellList(ImageList& outImageList) {
  uint32_t cell_count = 0;
  uint32_t current_offset_x = mStartOffsetX;
  uint32_t current_offset_y = mStartOffsetY;

  for (uint32_t col_count = 0; col_count < mMaxCellColCount; ++col_count) {
    for (uint32_t row_count = 0; row_count < mMaxCellRowCount; ++row_count) {
      ProcessCell(outImageList, current_offset_x, current_offset_y);
      current_offset_x = current_offset_x + mCellWidth;
      ++cell_count;

      // 현제 셀 카운트가 맥스 카운터보다 크다면
      if (cell_count > mMaxCellCount) {
        return;
      }
    }

    // 한바뀌 순회시 y offset은 증가하고 x는 초기화 합니다.
    current_offset_x = mStartOffsetX ;
    current_offset_y = current_offset_y + mCellHeight ;
  }
}
void ImageLoader::ProcessCell(ImageList& outImageList,
                              uint32_t inCurrentOffsetX,
                              uint32_t inCurrentOffsetY) {

    RectEx rect( inCurrentOffsetX, inCurrentOffsetY, mCellWidth, mCellHeight );
    auto&& image = CreateImage( mTarget, rect );
    // 이미지를 추가합니다.
    outImageList.emplace_back( image );
}

}  // namespace sg_media
