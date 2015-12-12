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
  uint64_t currentTime = timestamp();
  uint64_t diff = currentTime - m_previousTime;
  m_previousTime = currentTime;
  size_t fps = 1.0 /
    (static_cast<double>(diff) * 0.001);
  return static_cast<size_t>(std::round(fps));
}
