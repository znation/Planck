#ifndef _motion_h
#define _motion_h

#include <SDL.h>

#include <cassert>
#include <chrono>

template<typename T>
class Motion {
  private:
    T& m_renderable;
    size_t m_duration;
    double m_startValue;
    double m_endValue;
    size_t m_t = 0;
    bool m_initialized = false;

    double ease() {
      // linear easing, for now
      if (m_t >= m_duration) {
        return m_endValue;
      }
      double t = m_t++;
      double d = m_duration;
      assert(t <= d);
      return ((t / d) * (m_endValue - m_startValue)) + m_startValue;
    }

  public:
    Motion(T& renderable) : m_renderable(renderable)
    { }

    void init(
      size_t frames,
      double start,
      double end
    ) {
      m_t = 0;
      m_initialized = true;
      m_duration = frames;
      m_startValue = start;
      m_endValue = end;
    }

    void render(SDL_Renderer *renderer) {
      // eases between start and end, using a cubic easing function,
      // and passes the resulting value to the underlying renderable.
      m_renderable.render(renderer, this->ease());
    }
};

#endif
