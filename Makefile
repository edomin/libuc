cmake_build:
	mkdir cmake_build

refresh_debug: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Debug -DUC_CODE_COVERAGE=ON \
     -DUC_MORE_WARNINGS=ON -DUC_WERROR=ON

refresh_release: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Release -DUC_BUILD_DOC=ON

build:
	cmake --build cmake_build

build_debug: refresh_debug build
	cd cmake_build; ctest -V; make test_coverage

build_release: refresh_release build

install:
	cmake --build cmake_build --target install

install_debug: build_debug install

install_release: build_release install

clean:
	-rm -r -f ./cmake_build
