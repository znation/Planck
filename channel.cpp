#include "channel.h"

#include "fft.h"

#include <cmath>

static Channel logScale(const Channel& input) {
  // scales amplitude to log_10
  Channel output(input.size(), 0.0);
  for (size_t i=0; i<input.size(); i++) {
    auto val = std::abs(input[i]) + 1;
    assert(val >= 1);
    output[i] = std::log10(val);
  }
  return output;
}

Channel::Channel() :
  std::vector<float>(SAMPLES_PER_FRAME),
  m_minY(-1.0),
  m_maxY(1.0)
{}
Channel::Channel(size_t size, float value) : std::vector<float>(size, value) {}

int Channel::render(SDL_Renderer* renderer) const {
  size_t err;

  Channel result = fft(*this);
  Channel scaled = logScale(result);

  for (size_t i=0; i<scaled.size(); i++) {
    float point = scaled[i];
    float minX = 0.0;
    float maxX = static_cast<float>(scaled.size());
    size_t x = static_cast<size_t>(std::round((
        (static_cast<float>(i) - minX) / (maxX - minX)
    ) * SCREEN_WIDTH));
    size_t y = (SCREEN_HEIGHT - static_cast<size_t>(std::round(
      point * static_cast<float>(SCREEN_HEIGHT)
    ))) - 20;
    if ((err = SDL_SetRenderDrawColor(renderer, 255, 150, 150, 150)) != 0) {
      return err;
    };
    if ((err = SDL_RenderDrawPoint(renderer, x, y)) != 0) {
      return err;
    }
    if ((err = SDL_SetRenderDrawColor(renderer, 255, 150, 150, 75)) != 0) {
      return err;
    };
    if ((err = SDL_RenderDrawPoint(renderer, x+1, y)) != 0) {
      return err;
    }
    if ((err = SDL_RenderDrawPoint(renderer, x-1, y)) != 0) {
      return err;
    }
    if ((err = SDL_RenderDrawPoint(renderer, x, y+1)) != 0) {
      return err;
    }
    if ((err = SDL_RenderDrawPoint(renderer, x, y-1)) != 0) {
      return err;
    }
  }
  return 0;
}
