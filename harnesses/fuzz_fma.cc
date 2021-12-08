#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<float>();
  auto data1a = provider.ConsumeFloatingPoint<float>();
  auto data1b = provider.ConsumeFloatingPoint<float>();

  auto data2 = provider.ConsumeFloatingPoint<double>();
  auto data2a = provider.ConsumeFloatingPoint<double>();
  auto data2b = provider.ConsumeFloatingPoint<double>();

  auto data3 = provider.ConsumeFloatingPoint<long double>();
  auto data3a = provider.ConsumeFloatingPoint<long double>();
  auto data3b = provider.ConsumeFloatingPoint<long double>();

  auto data4 = provider.ConsumeIntegral<long long int>();
  auto data4a = provider.ConsumeIntegral<long long int>();
  auto data4b = provider.ConsumeIntegral<long long int>();

  fma(data1, data1a, data1b);
  fma(data2, data2a, data2b);
  fma(data3, data3a, data3b);
  fma(data4, data4a, data4b);

  return 0;
}