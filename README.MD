Library for working with text in various encodings. Currently supported
encodings:

* UTF-8
* UCS-4

#### Building release version
CMake required
```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
```

#### Installing
```
$ cd build
$ make install
```

#### Build debug version and running tests
CMocka required
lcov required
```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DTEST_CODE_COVERAGE=ON
$ make
$ ctest -V
$ make test_coverage
```

#### Usage
Look in [uc.h](https://github.com/edomin/libuconvert/tree/master/include/uc.h)

#### Copying

* Source code of library is under CC0. Read [LICENSE](https://github.com/edomin/libuconvert/tree/master/LICENSE) file
* File cmake/CodeCoverage.cmake is under BSL 1.0. Read [third_party_licenses/LICENSE_1_0.txt](https://github.com/edomin/libuconvert/tree/master/third_party_licenses/LICENSE_1_0.txt) file
