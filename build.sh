git submodule init
git submodule update
git submodule foreach git pull
mkdir build
cd build
rm CMakeCache.txt
cmake .. 
make clean
make install -j 30
