#include "channel.h"

#include "fft.h"

#include <cmath>

Channel::Channel() :
  std::vector<float>(SAMPLES_PER_FRAME),
  m_minY(-1.0),
  m_maxY(1.0)
{}
Channel::Channel(size_t size, float value) : std::vector<float>(size, value) {}

int Channel::render(SDL_Renderer* renderer) const {
  size_t err;
  if ((err = SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE)) != 0) {
    return err;
  };

  Channel result = fft(*this);

  for (size_t i=0; i<result.size(); i++) {
    float point = result[i];
    float minX = 0.0;
    float maxX = static_cast<float>(result.size());
    size_t x = static_cast<size_t>(std::round((
        (static_cast<float>(i) - minX) / (maxX - minX)
    ) * SCREEN_WIDTH));
    size_t y = static_cast<size_t>(std::round((
        (point - m_minY) / (m_maxY - m_minY)
    ) * SCREEN_HEIGHT));
    if ((err = SDL_RenderDrawPoint(renderer, x, y)) != 0) {
      return err;
    }
  }
  return 0;
}
