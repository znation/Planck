#ifndef _channel_h
#define _channel_h

#include "constants.h"

#include <SDL.h>

#include <vector>

class Channel : public std::vector<float> {
  private:
    float m_minY;
    float m_maxY;

  public:
    Channel();
    Channel(size_t size, float value);
    int render(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b) const;
};

#endif
