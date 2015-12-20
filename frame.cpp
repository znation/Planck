#include "frame.h"

void TimeDomainSample::init(float left, float right) {
  this->first = left;
  this->second = right;
}

TimeDomainSample::TimeDomainSample() {
  this->init(0.0, 0.0);
};

TimeDomainSample::TimeDomainSample(float left, float right) {
  this->init(left, right);
}
