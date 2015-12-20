#ifndef _circularbuffer_h
#define _circularbuffer_h

#include <vector>

template<typename T, size_t SIZE>
class CircularBuffer {
  private:
    size_t m_idx = 0;
    std::vector<T> m_buffer = std::vector<T>(SIZE);

  public:
    /* inserts a new T, returns the previous T at that slot */
    T insert(T t) {
      T ret = m_buffer[m_idx];
      m_buffer[m_idx] = t;
      m_idx = (m_idx + 1) % SIZE;
      return ret;
    }
};

#endif
