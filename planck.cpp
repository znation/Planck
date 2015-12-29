#include "constants.h"
#include "frame.h"
#include "planck.h"

#include "SDL_ttf.h"

#include <cstdlib>
#include <random>

int Planck::run() {
  SDL_Event event;

  // init
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw SDL_GetError();
  }
  SDL_Window *win = SDL_CreateWindow("Planck", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    SDL_Quit();
    throw SDL_GetError();
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    SDL_DestroyWindow(win);
    SDL_Quit();
    throw SDL_GetError();
  }

  if (TTF_Init() != 0) {
    SDL_Quit();
    throw "TTF_Init";
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> real;

  while (m_running) {
    while (SDL_PollEvent(&event)) {
      // process events
      if (event.type == SDL_QUIT) {
        m_running = false;
      }
    }

    // process loop logic
    TimeDomainFrame frame = m_mic.sample();

    // render
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    if (frame.left.render(renderer, 255, 150, 150) != 0) { return 6; }
    m_ui.render(renderer);

    SDL_RenderPresent(renderer);
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}
 
int main(int argc, char* argv[]) {
  Planck p;
  return p.run();
}
