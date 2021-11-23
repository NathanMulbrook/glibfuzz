export AFL_QEMU_PERSISTENT_ADDR=0x$(nm fuzz_cos | grep "T LLVMFuzzerTestOneInput" | awk '{print $1}')
export AFL_QEMU_PERSISTENT_HOOK=/home/admin/software/fuzzing/AFLplusplus/utils/aflpp_driver/aflpp_qemu_driver_hook.so


AFL_QEMU_PERSISTENT_GPR=1 AFL_QEMU_PERSISTENT_MEM=1 AFL_FORKSRV_INIT_TMOUT=60000  AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 /home/admin/software/fuzzing/AFLplusplus/afl-fuzz -Q -i input -o output ./fuzz_cos
