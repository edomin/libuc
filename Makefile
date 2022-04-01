ifdef TOOLCHAIN
    ifneq (,$(wildcard ./cmake/toolchains/$(TOOLCHAIN).cmake))
        TOOLCHAIN_OPT+=-DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/$(TOOLCHAIN).cmake
    endif
    CODECOV_ENABLED=OFF
endif

cmake_build:
	mkdir cmake_build

refresh_debug: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Debug \
	 -DUC_CODE_COVERAGE=$(CODECOV_ENABLED) -DUC_MORE_WARNINGS=ON -DUC_WERROR=ON \
	 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON $(TOOLCHAIN_OPT)

refresh_release: cmake_build
	cd cmake_build; cmake .. -DCMAKE_BUILD_TYPE=Release -DUC_BUILD_DOC=ON \
     -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON $(TOOLCHAIN_OPT)

build:
	cmake --build cmake_build

build_debug: refresh_debug build
ifndef TOOLCHAIN
	cd cmake_build; ctest -V; make test_coverage
endif

build_release: refresh_release build

install:
	cmake --build cmake_build --target install

install_debug: build_debug install

install_release: build_release install

clean:
	-rm -r -f ./cmake_build
