#ifndef _text_h
#define _text_h

#include <SDL.h>
#include "SDL_ttf.h"

class Text {
  public:
    static void render(
      SDL_Renderer *renderer,
      size_t x,
      size_t y,
      const char *message,
      SDL_Color color = { 255, 255, 255, 255 },
      size_t fontSize = 14,
      const char *fontFile = "./SourceSansPro-Regular.ttf"
    );
};

#endif
