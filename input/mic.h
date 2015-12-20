#include "../frame.h"

#include <portaudio.h>

class Mic {
  private:
    Frame m_frame;
    PaStream *m_stream;

  public:
    Mic();
    ~Mic();
    Mic(const Mic&) = delete;
    Mic& operator=(const Mic&) = delete;
    Mic(const Mic&&) = delete;
    Mic& operator=(const Mic&&) = delete;
    const Frame& sample() const;
};
