#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<double>();
  auto data2 = provider.ConsumeFloatingPoint<float>();
  auto data3 = provider.ConsumeFloatingPoint<long double>();
  auto data4 = provider.ConsumeIntegral<long long int>();


  erf(data1);
  erf(data2);
  erf(data3);
  erf(data4);


  return 0;
}