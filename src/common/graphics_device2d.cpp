#include <sano_game_media_pch.hpp>

namespace sg_media {
std::unique_ptr<GraphicsDevice2d> GraphicsDevice2d::sInstance;
void GraphicsDevice2d::StaticInit() {
  if (!WindowManager::sInstance) {
    LOG(LogLevel::Fatal,
        ls::GRAPHICS_DEVICE2D_INIT_ERROR_REQUIRED_WINDOW_MANAGER);
    throw Exception(ls::GRAPHICS_DEVICE2D_INIT_ERROR);
  }

  auto& window = WindowManager::sInstance->GetWindow();
  auto& window_ptr = window->GetWindow();

  platform::RendererPtr&& renderer_ptr = platform::CreateRenderer(window_ptr);

  if (!renderer_ptr) {
    LOG(LogLevel::Fatal, platform::GetLastError());
    throw Exception(ls::GRAPHICS_DEVICE2D_INIT_ERROR);
  }

  sInstance.reset(new GraphicsDevice2d(renderer_ptr));
  LOG(LogLevel::Info, ls::GRAPHICS_DEVICE2D_INIT_COMPLETION);
}

void GraphicsDevice2d::Clear() { platform::RenderClear(mRenderer); }
void GraphicsDevice2d::Present() { platform::RenderPresent(mRenderer); }

void GraphicsDevice2d::SetRenderColor(const Color& inColor) {
  platform::SetRenderDrawColor(mRenderer, inColor.r, inColor.g, inColor.b,
                               inColor.a);
}
void GraphicsDevice2d::GetRenderColor(Color& outColor) const {
  platform::GetRenderDrawColor(mRenderer, &outColor.r, &outColor.g, &outColor.b,
                               &outColor.a);
}

void GraphicsDevice2d::RenderRect(const Rect& inRect) {
  platform::RenderRect(mRenderer, inRect);
}
void GraphicsDevice2d::RenderTexture(const TexturePtr& inTexture,
                                     const Rect& inSrcRect,
                                     const Rect& inDestRect) {
  platform::RenderCopy(mRenderer, inTexture->GetTexture(), inSrcRect,
                       inDestRect);
}
void GraphicsDevice2d::RenderTexture(const TexturePtr& inTexture,
                                     const Rect& inSrcRect,
                                     const RectF& inDestRect) {
  platform::RenderCopy(mRenderer, inTexture->GetTexture(), inSrcRect,
                       inDestRect);
}
void GraphicsDevice2d::RenderFillRect(const Rect& inRect) {
  platform::RenderFillRect(mRenderer, inRect);
}
void GraphicsDevice2d::Release() {
  if (mRenderer) platform::DestroyRenderer(mRenderer);
}

void GraphicsDevice2d::SetRenderTarget(const platform::TexturePtr& inT) {
  platform::SetRenderTarget(mRenderer, inT);
}

void GraphicsDevice2d::GetRenderTarget(platform::TexturePtr& outT) {
  outT = platform::GetRenderTarget(mRenderer);
}

void RenderTextureToTexture(const TexturePtr& inSrcTexture,
                            const Rect& inSrcRect,
                            const TexturePtr& inDestTexture,
                            const Rect& inDestRect) {
  // GetOldRenderTarget;
  platform::TexturePtr old_render_target = nullptr;
  GraphicsDevice2d::sInstance->GetRenderTarget(old_render_target);

  // SetDestTexture;
  GraphicsDevice2d::sInstance->SetRenderTarget(
      static_cast<platform::TexturePtr>(inDestTexture->GetTexture()));

  GraphicsDevice2d::sInstance->RenderTexture(inSrcTexture, inSrcRect,
                                             inDestRect);

  GraphicsDevice2d::sInstance->SetRenderTarget(old_render_target);
}

void RenderTextureToTexture(const TexturePtr& inSrcTexture,
                            const Rect& inSrcRect,
                            const TexturePtr& inDestTexture,
                            const RectF& inDestRect) {
  // GetOldRenderTarget;
  platform::TexturePtr old_render_target = nullptr;
  GraphicsDevice2d::sInstance->GetRenderTarget(old_render_target);

  // SetDestTexture;
  GraphicsDevice2d::sInstance->SetRenderTarget(
      static_cast<platform::TexturePtr>(inDestTexture->GetTexture()));

  GraphicsDevice2d::sInstance->RenderTexture(inSrcTexture, inSrcRect,
                                             inDestRect);

  GraphicsDevice2d::sInstance->SetRenderTarget(old_render_target);
}

void RenderRectToTexture(const Rect& inRect, const TexturePtr& inDestTexture) {
  platform::TexturePtr old_render_target = nullptr;
  GraphicsDevice2d::sInstance->GetRenderTarget(old_render_target);

  // SetDestTexture;
  GraphicsDevice2d::sInstance->SetRenderTarget(
      static_cast<platform::TexturePtr>(inDestTexture->GetTexture()));

  GraphicsDevice2d::sInstance->RenderRect(inRect);

  GraphicsDevice2d::sInstance->SetRenderTarget(old_render_target);
}

void RenderRectToTextureWithColor(const Rect& inRect,
                                  const TexturePtr& inDestTexture,
                                  const Color& inColor) {
  Color old_color;
  GraphicsDevice2d::sInstance->GetRenderColor(old_color);

  GraphicsDevice2d::sInstance->SetRenderColor(inColor);
  RenderRectToTexture(inRect, inDestTexture);

  GraphicsDevice2d::sInstance->SetRenderColor(old_color);
}

void RenderFillRectToTexture(const Rect& inRect,
                             const TexturePtr& inDestTexture) {
  platform::TexturePtr old_render_target = nullptr;
  GraphicsDevice2d::sInstance->GetRenderTarget(old_render_target);

  // SetDestTexture;
  GraphicsDevice2d::sInstance->SetRenderTarget(
      static_cast<platform::TexturePtr>(inDestTexture->GetTexture()));

  GraphicsDevice2d::sInstance->RenderFillRect(inRect);

  GraphicsDevice2d::sInstance->SetRenderTarget(old_render_target);
}

void RenderFillRectToTextureWithColor(const Rect& inRect,
                                  const TexturePtr& inDestTexture,
                                  const Color& inColor) {
  Color old_color;
  GraphicsDevice2d::sInstance->GetRenderColor(old_color);

  GraphicsDevice2d::sInstance->SetRenderColor(inColor);
  RenderFillRectToTexture(inRect, inDestTexture);

  GraphicsDevice2d::sInstance->SetRenderColor(old_color);
}

void ClearTexture(const TexturePtr& inDestTexture) {
    RectEx clear_rect(0,0,0,0);
    ColorEx clear_color(0,0,0,0);
    inDestTexture->GetInfo(clear_rect.mWidth, clear_rect.mHeight);

    RenderFillRectToTextureWithColor(clear_rect, inDestTexture, clear_color);
}
}  // namespace sg_media
