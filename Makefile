rebuild: clean build

cmake_build:
	mkdir cmake_build

refresh_debug_coverage: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF \
     -DUC_CODE_COVERAGE=ON

refresh_debug_static: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF

refresh_debug_shared: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON

build:
	cmake --build cmake_build

build_debug_coverage: refresh_debug_coverage build
	cd cmake_build; ctest -V; make test_coverage

build_debug_static: refresh_debug_static build

build_debug_shared: refresh_debug_shared build

install_debug_static: refresh_debug_static
	cmake --build cmake_build --target install

install_debug_shared: refresh_debug_shared
	cmake --build cmake_build --target install

clean:
	-rm -r -f ./cmake_build
