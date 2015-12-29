#include "fps.h"
#include "text.h"

#include <chrono>
#include <cmath>
#include <sstream>

// debug
#include <iostream>

static uint64_t timestamp() {
  auto ms = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  return ms.count();
}

size_t FPS::get() {
  m_frameCounter++;
  uint64_t currentTime = timestamp();
  uint64_t diff = currentTime - m_previousTime;
  if (diff < 1000) {
    // don't update more often than this
    return m_fps;
  }

  m_previousTime = currentTime;
  size_t fps = static_cast<double>(m_frameCounter) /
    (static_cast<double>(diff) * 0.001);
  m_fps = static_cast<size_t>(std::round(fps));
  m_frameCounter = 0;
  return m_fps;
}

void FPS::render(SDL_Renderer *renderer, double opacity) {
  size_t fps = this->get();
  uint8_t alpha = static_cast<uint8_t>(std::round(255.0 * opacity));
  SDL_Color color = { 210, 210, 210, alpha };
  std::ostringstream ss;
  ss << fps;
  ss << " fps";
  Text::render(renderer, 10, 10, ss.str().c_str(), color);
}
