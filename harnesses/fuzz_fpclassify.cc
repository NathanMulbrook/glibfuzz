#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<float>();
  auto data2 = provider.ConsumeFloatingPoint<double>();
  auto data3 = provider.ConsumeFloatingPoint<long double>();

  fpclassify(data1);
  fpclassify(data2);
  fpclassify(data3);

  return 0;
}