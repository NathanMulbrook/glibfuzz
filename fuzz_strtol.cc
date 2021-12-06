#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  auto data1 = provider.ConsumeBytesAsString(size);
  char *ptr;
  std::strtol(data1.c_str(), &ptr, 10);
return 0;
}
