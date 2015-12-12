#include <SDL.h>

#include <vector>

class FrequencyLine {
  private:
    size_t m_binCount;
    std::vector<double> m_bins;
    double m_minFrequency;
    double m_maxFrequency;
    double m_minValue;
    double m_maxValue;

  public:
    FrequencyLine(size_t binCount, double minFrequency, double maxFrequency, double minValue, double maxValue);
    void addPoint(double frequency, double value);
    int render(SDL_Renderer* renderer);
};
