#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto base = provider.ConsumeIntegral<int>();
  auto string = provider.ConsumeRandomLengthString(2048);
  //auto data1 = provider.ConsumeBytesAsString(size);
  char *ptr;
  std::strtol(string.c_str(), &ptr, base);
return 0;
}
