#include "circularbuffer.h"

#include <cstdint>

class FPS {
  private:
    uint64_t m_previousTime;

  public:
    size_t get();
};
