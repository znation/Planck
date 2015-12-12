#include "constants.h"
#include "frequencyline.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

FrequencyLine::FrequencyLine(
  size_t binCount,
  double minFrequency,
  double maxFrequency,
  double minValue,
  double maxValue) :
  m_binCount(binCount),
  m_bins(std::vector<double>(binCount, minValue)),
  m_minFrequency(minFrequency),
  m_maxFrequency(maxFrequency),
  m_minValue(minValue),
  m_maxValue(maxValue)
{}

void FrequencyLine::addPoint(double frequency, double value) {
  assert(frequency >= m_minFrequency);
  assert(frequency <= m_maxFrequency);
  assert(value >= m_minValue);
  assert(value <= m_maxValue);
  double scalar = (frequency - m_minFrequency) / (m_maxFrequency - m_minFrequency);
  size_t binIdx = static_cast<size_t>(
    std::round(scalar * static_cast<double>(m_binCount))
  );
  if (binIdx == m_binCount) {
    binIdx--;
  }
  assert(binIdx < m_binCount);
  m_bins[binIdx] = std::max(m_bins[binIdx], value);
}

int FrequencyLine::render(SDL_Renderer *renderer) {
  size_t err;
  if ((err = SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE)) != 0) {
    return err;
  };
  for (size_t i=0; i<m_bins.size(); i++) {
    size_t bottom = (SCREEN_HEIGHT / 2) + 100;
    size_t top = bottom - 200;
    double value = m_bins[i];
    double scalar = (value - m_minValue) / (m_maxValue - m_minValue);
    size_t y = static_cast<size_t>(
      std::round(bottom - (scalar * (bottom - top)))
    );
    std::cout << "Drawing point ";
    std::cout << i << ", " << y << "." << std::endl;
    if ((err = SDL_RenderDrawPoint(renderer, i, y)) != 0) {
      return err;
    }
  }
  return 0;
};
