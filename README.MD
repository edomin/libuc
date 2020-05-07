Library for working with text in various encodings. Currently supported
encodings:

* UTF-8
* UCS-4

#### Prerequisites
All prerequisites are optional. Library (without tests and documentation) may 
be builded manually from commandline using any compiler. 
For basic building: 
 * UNIX envioronment (currently tested on Linux only)
 * gcc
 * make
 * CMake

Also for building tests: 
 * Cmocka
 * lcov

Also for building documentation: 
 * Doxygen

#### Building debug version
Remove -DUC_MORE_WARNINGS=ON for disabling huge list of warning options when 
runing gcc. Disable -DUC_WERROR=ON if you want to build with warnings if 
warnings will be occured
```
$ mkdir cmake_build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DUC_MORE_WARNINGS=ON -DUC_WERROR=ON
$ cmake --build cmake_build
```

Also there is shortcut (this also will build and run tests):
```
$ make build_debug
```

#### Building release version
Remove -DUC_BUILD_DOC=ON option if you need not to build documentation. After 
building documentation will be appeared in <libuc_dir>/cmake_build/doc/html.
```
$ mkdir cmake_build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DUC_BUILD_DOC=ON
$ cmake --build cmake_build
```

#### Installing
```
$ cmake --build cmake_build --target install
```

Also there is shortcut:
```
$ make install
```

#### Build debug version and running tests
```
$ mkdir cmake_build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DUC_CODE_COVERAGE=ON
$ cmake --build cmake_build
$ ctest -V
$ make test_coverage
```

Also there is shortcut:
```
$ make build_debug
```

#### Build it manually
Build using gcc: 
```
$ gcc -O2 -Iinclude -c -o uc.o src/uc.c
$ ar rcs libuc.a uc.o
```
You can build library manually using any your favorite compiler. Let me know 
if errors or warnings will be occured during compilation with your compiler.

#### Usage
Look in [uc.h](https://github.com/edomin/libuconvert/tree/master/include/uc.h). 
Also build and look documentation using doxygen. Online documentation will be 
soon.

#### Copying

* Source code of library is under CC0. Read [COPYING](https://github.com/edomin/libuconvert/tree/master/COPYING) file
* File cmake/CodeCoverage.cmake is under BSL 1.0. Read [third_party_licenses/LICENSE_1_0.txt](https://github.com/edomin/libuconvert/tree/master/third_party_licenses/LICENSE_1_0.txt) file
