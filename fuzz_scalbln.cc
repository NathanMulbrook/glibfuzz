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

  scalbln(data1, data1a);
  scalbln(data2, data2a);
  scalbln(data3, data3a);
  scalbln(data4, data4a);

  return 0;
}