#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<float>();
  auto data1a = provider.ConsumeFloatingPoint<float>();
  auto data2 = provider.ConsumeFloatingPoint<double>();
  auto data2a = provider.ConsumeFloatingPoint<double>();
  auto data3 = provider.ConsumeFloatingPoint<long double>();
  auto data3a = provider.ConsumeFloatingPoint<long double>();
  auto data4 = provider.ConsumeIntegral<long long int>();
  auto data4a = provider.ConsumeIntegral<long long int>();

  int *quot1;
  int *quot2;
  int *quot3;
  int *quot4;

  remquo(data1, data1a, quot1);
  remquo(data2, data2a, quot2);
  remquo(data3, data3a, quot3);
  remquo(data4, data4a, quot4);

  return 0;
}