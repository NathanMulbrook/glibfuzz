#!/bin/bash

_term() {
    for fuzzerpid in $puzzerpids; do
        kill -TERM "$fuzzerpid" 2>/dev/null
    done
    exit
}


trap _term SIGTERM

pids=()

source ./config.sh
echo "$INSTALLED_FUZZER"
builds=$(pwd)/build.sh


while getopts ":f:a:e:" opt; do
  case $opt in
    f)
      fuzzer=$OPTARG
      ;;
    a)
      fuzzer_args=$OPTARG
      ;;
    e)
      fuzzer_env_vars=$OPTARG
      ;;
  esac
done




if [ -f "$builds" ]
then
    cd build/run/
    echo "Moving to Run Dir"
    ./runfuzzer.sh $@
else
    if [ -z ${fuzzer} ]
    then
        for dir in */; do
                    echo "----Launching ${dir::-1}"

            ./runfuzzer.sh -f ${dir::-1} $@ &
            fuzzerpids+=($!)

            if [ $INSTALLED_FUZZER == "afl" ] 
            then
                sleep 4
            fi

        done
    else



        cd $fuzzer
        echo "--------------Launching $fuzzer"
        if [ $INSTALLED_FUZZER == "afl" ] 
        then
        #########AFL
            export AFL_QEMU_PERSISTENT_ADDR=0x$(nm $fuzzer | grep "T LLVMFuzzerTestOneInput" | awk '{print $1}')
            export AFL_QEMU_PERSISTENT_HOOK=$AFL_ROOT/utils/aflpp_driver/aflpp_qemu_driver_hook.so
            ${fuzzer_env_vars} AFL_QEMU_PERSISTENT_GPR=1 AFL_QEMU_PERSISTENT_MEM=1 AFL_FORKSRV_INIT_TMOUT=60000  AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 $AFL_ROOT/afl-fuzz -Q -i input -o output ${fuzzer_args} ./$fuzzer
        else
        ######Libfuzzer
            ${fuzzer_env_vars} ./$fuzzer ./corpus -use_counters=0 ${fuzzer_args}
        fi          
    

    fi
fi
while :
do
    sleep 5     
done