#include "frame.h"

void Frame::insert(size_t i, float leftValue, float rightValue) {
  left[i] = leftValue;
  right[i] = rightValue;
}
