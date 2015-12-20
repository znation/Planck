#ifndef _frame_h
#define _frame_h

#include "circularbuffer.h"
#include "constants.h"

// TODO needs locking for thread safety?
class TimeDomainSample : std::pair<float, float> {
  private:
    void init(float left, float right);

  public:
    TimeDomainSample();
    TimeDomainSample(float left, float right);
    float left() const;
    float right() const;
};

typedef CircularBuffer<TimeDomainSample, SAMPLES_PER_SECOND> Frame;

#endif
