fuzz:
	#git submodule init
	#git submodule update
	#git submodule foreach git pull
	mkdir -p build
	cd build
	rm -f CMakeCache.txt
	cmake ..
	make clean
	make install -j$(NUM_PROCESSORS)

clean:
	rm -r build/

