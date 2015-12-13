#include "circularbuffer.h"

#include <cstdint>

class FPS {
  private:
    uint64_t m_previousTime;
    size_t m_frameCounter;
    size_t m_fps;

  public:
    size_t get();
};
