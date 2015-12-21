#include "../frame.h"

#include <portaudio.h>

class Mic {
  private:
    TimeDomainFrame m_frame;
    PaStream *m_stream;

  public:
    Mic();
    ~Mic();
    Mic(const Mic&) = delete;
    Mic& operator=(const Mic&) = delete;
    Mic(const Mic&&) = delete;
    Mic& operator=(const Mic&&) = delete;
    TimeDomainFrame sample() const;
};
