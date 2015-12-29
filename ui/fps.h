#ifndef _fps_h
#define _fps_h

#include <SDL.h>

#include <cstdint>

class FPS {
  private:
    uint64_t m_previousTime;
    size_t m_frameCounter;
    size_t m_fps;
    size_t get();

  public:
    void render(SDL_Renderer *renderer);
};

#endif
