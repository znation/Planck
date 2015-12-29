#include "fps.h"
#include "motion.h"

class UI {
  private:
    Motion<UI> m_animated = Motion<UI>(*this);
    FPS m_fps;

  public:
    UI();
    void render(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, double opacity);
};
