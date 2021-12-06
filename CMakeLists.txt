#if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/run/" CACHE PATH "..." FORCE)
#endif()
message("${CMAKE_INSTALL_PREFIX}")
set(VERBOSE)

cmake_minimum_required(VERSION 3.19)
project(fuzz_libfastjson)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE INTERNAL "")


# set(CMAKE_C_COMPILER "/home/admin/software/fuzzing/AFLplusplus/afl-clang-fast" CACHE INTERNAL "")
# set(CMAKE_CXX_COMPILER "/home/admin/software/fuzzing/AFLplusplus/afl-clang-fast++" CACHE INTERNAL "")


# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_FLAGS " -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
# set(CMAKE_C_FLAGS  " -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
# set(CMAKE_EXE_LINKER_FLAGS " -fprofile-instr-generate")


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "/home/admin/software/fuzzing/AFLplusplus/libAFLQemuDriver.a -O2 -g")
set(CMAKE_C_FLAGS  "/home/admin/software/fuzzing/AFLplusplus/libAFLQemuDriver.a -O2 -g")
set(CMAKE_EXE_LINKER_FLAGS "")

FILE(GLOB C_FILES *.c)
FILE(GLOB H_FILES *.h)
FILE(GLOB C_FILES2 utils/*.c)
FILE(GLOB H_FILES2 utils/*.h)

FILE(GLOB TARGETS fuzz_*.cc)

foreach(TARGET ${TARGETS})
    message(STATUS  "------------${TARGET}")
    get_filename_component(TARGET_NAME ${TARGET} NAME_WLE)
    message(STATUS  "-----${TARGET_NAME}")
    add_executable("${TARGET_NAME}" "${TARGET}" ${C_FILES} ${H_FILES} ${C_FILES2} ${H_FILES2})


    make_directory("${TARGET_NAME}")
    make_directory("${TARGET_NAME}/input")
    make_directory("${TARGET_NAME}/output")
    install(TARGETS "${TARGET_NAME}"
        DESTINATION "${TARGET_NAME}/")
    install(DIRECTORY "corpus/glibc/${TARGET_NAME}/"
        DESTINATION "${TARGET_NAME}/input/"
        MESSAGE_NEVER )
endforeach()