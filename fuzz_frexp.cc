#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <math.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeFloatingPoint<double>();
  auto data2 = provider.ConsumeFloatingPoint<float>();
  auto data3 = provider.ConsumeFloatingPoint<long double>();
  auto data4 = provider.ConsumeIntegral<long long int>();

  int *exp1;
  int *exp2;
  int *exp3;
  int *exp4;

  frexp(data1, exp1);
  frexp(data2, exp2);
  frexp(data3, exp3);
  frexp(data4, exp4);




return 0;
}
