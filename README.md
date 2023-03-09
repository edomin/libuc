Library for working with text in various encodings. Currently supported
encodings:

* UTF-8
* UCS-2
* UCS-4

#### Prerequisites
All prerequisites are optional. Library (without tests and documentation) may
be builded manually from commandline using any compiler.

For manual basic building without extra tools:

* C89-compiler (tested on gcc-10.2.1, mingw-10.x, tcc-0.9.27 and clang-11.0.1-2)

For basic building:

* UNIX envioronment (currently tested on Linux only)
* C89-compiler (tested on gcc-10.2.1, mingw-10.x, tcc-0.9.27 and clang-11.0.1-2)
* make
* CMake >= 3.11
* [cmake_barebones](https://github.com/edomin/cmake_barebones)

Also for building tests:

* C99-compiler
* Cmocka
* lcov
* [CodeCoverage.cmake](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake) installed in <prefix>/lib/cmake/cmake-modules

Also for static analysing code:

* clang-tidy
* include-what-you-use

Also for building documentation:

* Doxygen

Also for analysing cmake-files:

* [cmakelint](https://pypi.org/project/cmakelint/)

#### Building debug version
```
$ make debug [toolchain={<predefined>|<file>}] [nowerror=1] [onejob=1] \
[prefix=<install_dir>]
```
Additional options:

* toolchain=`{<predefined>|<file>}` - use one of predefined toolchain
configurations or your toolchain file.
* nowerror=1 - compile sources without -Werror compiler option
* onejob=1 - don't build in parallel mode
* prefix=<install_dir> - set installation prefix (default is /usr/local on UNIX)

#### Building release version
```
make release [toolchain={<predefined>|<file>}] [builddoc=1] [devmode=1] \
[nowerror=1] [onejob=1] [prefix=<install_dir>]
```
Additional options:

* toolchain=`{<predefined>|<file>}` - use one of predefined toolchain
configurations or your toolchain file.
* builddoc=1 - build documentation
* devmode=1 - enable verbose output and compile with huge amount of warnings
and -Werror
* nowerror=1 - if devmode=1 option is active don't use -Werror compiler option
* onejob=1 - don't build in parallel mode
* prefix=<install_dir> - set installation prefix (default is /usr/local on UNIX)

#### Installing
```
# make install
```

#### Lint
```
$ make lint [toolchain={<predefined>|<file>}] [nowerror=1] [onejob=1]
```
Additional options:

* toolchain=`{<predefined>|<file>}` - use one of predefined toolchain
configurations or your toolchain file.
* nowerror=1 - compile sources without -Werror compiler option
* onejob=1 - don't build in parallel mode

#### Build code-coverage version and run tests
```
$ make coverage [toolchain={<predefined>|<file>}] [nowerror=1] [onejob=1]
```
Additional options:

* toolchain=`{<predefined>|<file>}` - use one of predefined toolchain
configurations or your toolchain file.
* nowerror=1 - compile sources without -Werror compiler option
* onejob=1 - don't build in parallel mode

#### Analyze Cmakelists.txt
```
$ make lint_build
```

#### Build it manually without cmake and other fancy tools
Example command for building with gcc:
```
$ gcc -O2 -Iinclude -c -o uc.o src/uc.c
$ ar rcs libuc.a uc.o
```
You can build library manually using any your favorite compiler. Let me know
if errors or warnings will be occured during compilation with your compiler.

#### Usage
Look in [uc.h](https://github.com/edomin/libuconvert/tree/master/include/uc/uc.h).
Also build and look documentation using doxygen. Online documentation will be
soon.

#### Copying

* Source code of library is under CC0. Read [COPYING](https://github.com/edomin/libuconvert/tree/master/COPYING) file
