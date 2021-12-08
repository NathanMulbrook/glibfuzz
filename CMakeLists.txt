#if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/run/" CACHE PATH "..." FORCE)
#endif()
message("${CMAKE_INSTALL_PREFIX}")
set(VERBOSE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.sh
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

cmake_minimum_required(VERSION 3.19)
project(fuzz_libfastjson)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE INTERNAL "")

if(BUILD_LIBFUZZER)
    set(CMAKE_CXX_FLAGS " -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_C_FLAGS  " -fsanitize=fuzzer,address,undefined  -O2 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_EXE_LINKER_FLAGS " -fprofile-instr-generate")
    file(APPEND ${CMAKE_BINARY_DIR}/config.sh
        "export INSTALLED_FUZZER=libfuzzer
        ")
endif(BUILD_LIBFUZZER)


if(BUILD_AFL)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS "$ENV{AFL_ROOT}/libAFLQemuDriver.a -O2 -g")
    set(CMAKE_C_FLAGS  "$ENV{AFL_ROOT}/libAFLQemuDriver.a -O2 -g")
    file(APPEND ${CMAKE_BINARY_DIR}/config.sh
        "export INSTALLED_FUZZER="afl"
        ")
endif(BUILD_AFL)


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
    install(TARGETS "${TARGET_NAME}"
        DESTINATION "${TARGET_NAME}/")

    if(BUILD_LIBFUZZER)
        install(DIRECTORY "corpus/glibc/${TARGET_NAME}/"
        DESTINATION "${TARGET_NAME}/corpus/"
        MESSAGE_NEVER )
    endif(BUILD_LIBFUZZER)
    if(BUILD_AFL)
        make_directory("${CMAKE_INSTALL_PREFIX}/${TARGET_NAME}/output")
        install(DIRECTORY "corpus/glibc/${TARGET_NAME}/"
        DESTINATION "${TARGET_NAME}/input/"
        MESSAGE_NEVER )
    endif(BUILD_AFL)
endforeach()
install(FILES runfuzzer.sh build/config.sh
    DESTINATION ./
    PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE)