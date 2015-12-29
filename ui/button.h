#ifndef _button_h
#define _button_h

#include <SDL.h>

class Button {
  private:
    size_t m_x;
    size_t m_y;
    //size_t m_width;
    //size_t m_height;
    const char* m_text;
    //bool m_enabled;

  public:
    Button(
      size_t x,
      size_t y,
      //size_t width,
      //size_t height,
      const char* text
      //bool enabled
    );
    void render(SDL_Renderer *renderer, double opacity);
};

#endif
