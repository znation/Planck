#include "fps.h"

class UI {
  private:
    FPS m_fps;

  public:
    void render(SDL_Renderer *renderer);
};
