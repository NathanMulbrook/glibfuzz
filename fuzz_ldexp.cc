#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<float>();
  auto data1a = provider.ConsumeIntegral<long int>();
  auto data2 = provider.ConsumeFloatingPoint<double>();
  auto data2a = provider.ConsumeIntegral<long int>();
  auto data3 = provider.ConsumeFloatingPoint<long double>();
  auto data3a = provider.ConsumeIntegral<long int>();
  auto data4 = provider.ConsumeIntegral<long long int>();
  auto data4a = provider.ConsumeIntegral<long int>();

  ldexp(data1, data1a);
  ldexp(data2, data2a);
  ldexp(data3, data3a);
  ldexp(data4, data4a);

  return 0;
}