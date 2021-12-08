git submodule init
git submodule update
git submodule foreach git pull origin master
mkdir build

source config.sh

cd build
rm CMakeCache.txt

case "$1" in
    clean|c)
        cd ..
        rm -r ./build
        exit
        ;;
    libfuzz|l)
        cmake -DBUILD_LIBFUZZER=true ..
        ;;
    afl|a)
        cmake -DBUILD_AFL=true ..
        ;;
    *)
        cmake -DBUILD_LIBFUZZER=true ..
        ;; 
esac
make clean
make install -j 30
