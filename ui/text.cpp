#include "text.h"

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


void Text::render(
  SDL_Renderer *renderer,
  size_t x,
  size_t y,
  const char *message,
  SDL_Color color,
  size_t fontSize,
  const char *fontFile
) {
  //Open the font
  TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
  if (font == nullptr) {
    throw "TTF_OpenFont";
  }
  //We need to first render to a surface as that's what TTF_RenderText
  //returns, then load that surface into a texture
  SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
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

  renderTexture(texture, renderer, x, y);
  // TODO -- free the texture?
}
