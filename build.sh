git submodule init
git submodule update
git submodule foreach git pull
mkdir corpus
cp -r libfastjson-corpus/corpus corpus
rm CMakeCache.txt
cmake . 
make clean
make -j 20

#export AFL_QEMU_PERSISTENT_ADDR=0x$(nm fuzz_cos | grep "T LLVMFuzzerTestOneInput" | awk '{print $1}')
#export AFL_QEMU_PERSISTENT_HOOK=/home/admin/software/fuzzing/AFLplusplus/utils/aflpp_driver/aflpp_qemu_driver_hook.so /home/admin/software/fuzzing/AFLplusplus/afl-fuzz -Q ... -- ./fuzz_cos'
