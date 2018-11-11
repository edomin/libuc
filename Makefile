all: clean refresh build

cmake_build:
	mkdir cmake_build

refresh: cmake_build
	cd cmake_build;cmake $(CMAKE_FLAGS) ..

build: refresh
	cd cmake_build; make

cmake_build/test_uconvert: build

run: cmake_build/test_uconvert
	cmake_build/test_uconvert

clean:
	rm -r -f ./cmake_build

rebuild: clean build
