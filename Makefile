build_release:
	mkdir build
	cd build; cmake .. -DCMAKE_BUILD_TYPE=Release; make

install:
	cd build; make install

build_test:
	mkdir build
	cd build; cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON \
     -DTEST_CODE_COVERAGE=ON; make; ctest -V; make test_coverage

clean:
	rm -r -f ./build

rebuild_test: clean build_test
