#!/usr/bin/env bash

./config.sh

_term() {
    pkill -P $$
}


trap _term SIGTERM

builds=$(pwd)/build.sh
fuzzer=$1
if [ -f "$builds" ]
then
    cd build/run/
    echo "Moving to Run Dir"
    ./runfuzzer.sh $fuzzer
else
    if [ -z ${fuzzer} ]
    then
        for dir in */; do
                    echo "----Launching ${dir::-1}"

            ./runfuzzer.sh ${dir::-1} &
            sleep 5
        done
    else

            cd $fuzzer
            echo "--------------Launching $fuzzer"
            pwd
            export AFL_QEMU_PERSISTENT_ADDR=0x$(nm $fuzzer | grep "T LLVMFuzzerTestOneInput" | awk '{print $1}')
            export AFL_QEMU_PERSISTENT_HOOK=$AFL_ROOT/utils/aflpp_driver/aflpp_qemu_driver_hook.so


            AFL_QEMU_PERSISTENT_GPR=1 AFL_QEMU_PERSISTENT_MEM=1 AFL_FORKSRV_INIT_TMOUT=60000  AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 $AFL_ROOT/afl-fuzz -Q -i input -o output ./$fuzzer
    fi
fi