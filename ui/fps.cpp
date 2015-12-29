#include "fps.h"

#include "SDL_ttf.h"

#include <chrono>
#include <cmath>
#include <sstream>

// debug
#include <iostream>

// Changes a surface's alpha value, by altering per-pixel alpha if necessary.
// from http://stackoverflow.com/a/12773144
static void SetSurfaceAlpha(SDL_Surface *surface, Uint8 alpha)
{
  SDL_PixelFormat* fmt = surface->format;

  unsigned bpp = fmt->BytesPerPixel;
  // Scaling factor to clamp alpha to [0, alpha].
  float scale = alpha / 255.0f;

  SDL_LockSurface(surface);

  for (int y = 0; y < surface->h; ++y)  {
    for (int x = 0; x < surface->w; ++x) {
      // Get a pointer to the current pixel.
      Uint32* pixel_ptr = (Uint32 *)(
              (Uint8 *)surface->pixels
              + y * surface->pitch
              + x * bpp
              );

      // Get the old pixel components.
      Uint8 r, g, b, a;
      SDL_GetRGBA( *pixel_ptr, fmt, &r, &g, &b, &a );

      // Set the pixel with the new alpha.
      *pixel_ptr = SDL_MapRGBA( fmt, r, g, b, scale * a );
    }
  }

  SDL_UnlockSurface(surface);
}

static void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr){
  SDL_RenderCopy(ren, tex, clip, &dst);
}
static void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr){
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr){
    dst.w = clip->w;
    dst.h = clip->h;
  }
  else {
    SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
  }
  renderTexture(tex, ren, dst, clip);
}


static SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
  SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
  //Open the font
  TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
  if (font == nullptr) {
    throw "TTF_OpenFont";
  }
  //We need to first render to a surface as that's what TTF_RenderText
  //returns, then load that surface into a texture
  SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
  if (surf == nullptr){
    TTF_CloseFont(font);
    throw "TTF_RenderText";
  }
  SetSurfaceAlpha(surf, color.a);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
  if (texture == nullptr){
    throw "CreateTexture";
  }
  //Clean up the surface and font
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  return texture;
}

static uint64_t timestamp() {
  auto ms = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  return ms.count();
}

size_t FPS::get() {
  m_frameCounter++;
  uint64_t currentTime = timestamp();
  uint64_t diff = currentTime - m_previousTime;
  if (diff < 1000) {
    // don't update more often than this
    return m_fps;
  }

  m_previousTime = currentTime;
  size_t fps = static_cast<double>(m_frameCounter) /
    (static_cast<double>(diff) * 0.001);
  m_fps = static_cast<size_t>(std::round(fps));
  m_frameCounter = 0;
  return m_fps;
}

void FPS::render(SDL_Renderer *renderer, double opacity) {
  size_t fps = this->get();
  uint8_t alpha = static_cast<uint8_t>(std::round(255.0 * opacity));
  SDL_Color color = { 210, 210, 210, alpha };
  std::ostringstream ss;
  ss << fps;
  ss << " fps";
  SDL_Texture *image = renderText(ss.str(), "./SourceSansPro-Regular.ttf",
    color, 14, renderer);
  if (image == nullptr) {
    TTF_Quit();
    SDL_Quit();
    throw "Unable to render image from FPS.";
  }
  renderTexture(image, renderer, 10, 10);
}
