// FFT implementation based on
// https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm

#include "constants.h"
#include "frame.h"

#include <cassert>
#include <complex>

const static std::complex<float> PI(std::acos(-1.0), 0.0);
const static std::complex<float> i(0.0, 1.0);
const static std::complex<float> neg_two(-2.0, 0.0);
const static std::complex<float> neg_two_pi_I = i * neg_two * PI;

std::vector<std::complex<float>> fft(const float* input, size_t n, size_t s) {
  if (n == 1) {
    return std::vector<std::complex<float>>(1, input[0]);
  }

  assert((n / 2) * 2 == n); // make sure n is a power of 2
  std::vector<std::complex<float>> X = fft(input, n / 2, 2 * s);
  std::vector<std::complex<float>> result2 = fft(input + s, n / 2, 2 * s);
  X.insert( X.end(), result2.begin(), result2.end() );
  std::complex<float> n_c(n, 0.0);
  for (size_t k=0; k<(n/2); k++) {
    std::complex<float> t = X[k];
    std::complex<float> k_c(k, 0.0);
    X[k] = t + exp((neg_two_pi_I * k_c) / n_c) * X[k+(n/2)];
    X[k+(n/2)] = t - exp((neg_two_pi_I * k_c) / n_c) * X[k+(n/2)];
  }
  return X;
}

Channel fft(const Channel& input) {
  size_t n = input.size();
  std::vector<std::complex<float>> output = fft(input.data(), n, 1);
  assert(output.size() == input.size());
  // throw away imaginary portion
  Channel realOutput(n/2, 0.0);
  for (size_t i=0; i<n/2; i++) {
    realOutput[i] = output[i].real();
  }
  return realOutput;
}
