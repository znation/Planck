#include "input.h"

class Mic : public Input {
  private:
    TimeDomainFrame m_frame;
    PaStream *m_stream;

  public:
    Mic();
    ~Mic();
    virtual TimeDomainFrame sample() const;
};
