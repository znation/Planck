#include "fps.h"

#include <chrono>
#include <cmath>

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
