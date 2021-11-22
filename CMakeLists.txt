cmake_minimum_required(VERSION 3.19)
project(fuzz_libfastjson)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++   -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_C_FLAGS  " -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-instr-generate -fcoverage-mapping")

FILE(GLOB C_FILES *.c)
FILE(GLOB H_FILES *.h)
FILE(GLOB C_FILES2 utils/*.c)
FILE(GLOB H_FILES2 utils/*.h)


# FILE(GLOB_RECURSE MATH_C_FILES /home/admin/software/fuzzing/glibc/*.c)
# FILE(GLOB_RECURSE MATH_H_FILES /home/admin/software/fuzzing/glibc/*.h)

# add_library(math STATIC
#     ${MATH_C_FILES}
#     ${MATH_H_FILES}
# )

add_executable(fuzz_cos fuzz_cos.cc ${C_FILES} ${H_FILES} ${C_FILES2} ${H_FILES2})
