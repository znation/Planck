#include "event.h"
#include "ui.h"

UI::UI() {
  m_animated.init(360, 1.0, 0.0);
  Event::observe(
    SDL_MOUSEMOTION,
    [this](const SDL_Event&) {
      m_animated.init(120, 1.0, 0.0);
    }
  );
}

void UI::render(SDL_Renderer *renderer) {
  m_animated.render(renderer);
}


void UI::render(SDL_Renderer *renderer, double opacity) {
  m_fps.render(renderer, opacity);
}
