#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

double sin(double data1);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1= provider.ConsumeFloatingPoint<double>();
cos(data1);
return 0;
}