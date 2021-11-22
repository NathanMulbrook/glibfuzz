git submodule init
git submodule update
git submodule foreach git pull
mkdir corpus
cp -r libfastjson-corpus/corpus corpus
rm CMakeCache.txt
cmake . 
make clean
make -j 20