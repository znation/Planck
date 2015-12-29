#include "button.h"
#include "text.h"

#include <cmath>

Button::Button(
  size_t x,
  size_t y,
  //size_t width,
  //size_t height,
  const char* text
  //bool enabled
) :
  m_x(x),
  m_y(y),
  //m_width(width),
  //m_height(height),
  m_text(text)
  //m_enabled(enabled)
{}

void Button::render(SDL_Renderer *renderer, double opacity) {
  SDL_Color color = { 255, 255, 255, static_cast<uint8_t>(
    std::round(opacity * 255.0)
  )};
  // TODO draw a rectangle below
  // TODO take m_enabled into account and make buttons clickable
  Text::render(renderer, m_x, m_y, m_text, color);
}
