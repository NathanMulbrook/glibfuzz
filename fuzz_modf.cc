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

  float *exp1;
  double *exp2;
  long double *exp3;
  double *exp4;

  modf(data1, exp1);
  modf(data2, exp2);
  modf(data3, exp3);
  modf(data4, exp4);




return 0;
}
