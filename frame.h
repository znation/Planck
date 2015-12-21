#ifndef _frame_h
#define _frame_h

#include "constants.h"

#include <SDL.h>

#include "channel.h"

class Frame {
  public:
    Channel left;
    Channel right;
    void insert(size_t i, float leftValue, float rightValue);
};

class TimeDomainFrame : public Frame {};

class FrequencyDomainFrame : public Frame {};

#endif
