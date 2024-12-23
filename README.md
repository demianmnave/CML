[![msvc-latest](https://github.com/demianmnave/CML/actions/workflows/msvc-latest.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/msvc-latest.yml)
[![msvc-clangcl-latest](https://github.com/demianmnave/CML/actions/workflows/msvc-clangcl-latest.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/msvc-clangcl-latest.yml)
[![msvc-17-10](https://github.com/demianmnave/CML/actions/workflows/msvc-17-10.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/msvc-17-10.yml)

## Configurable Math Library
For CML version 1, please see https://github.com/demianmnave/CML1.
## License
The Configurable Math Library (CML) is released under the [Boost Software
License, Version 1.0.](http://www.boost.org/LICENSE_1_0.txt).
## Using the CML
As it is header-only, it is simple enough to copy the `cml` header directory into your project and setup your build to reference it. Users of CMake 3.15+ can also leverage [`cmake --install ...`](make.org/cmake/help/v3.15/manual/cmake.1.html#install-a-project) and [`find_package(CML CONFIG)`](https://cmake.org/cmake/help/v3.15/command/find_package.html) to integrate CML into a CMake project.
## Compiler requirements
The CML requires a compiler with C++17 support.
## Building and Running Tests
### With plain CMake
To run the test suite from a command prompt using a Makefile-like generator, start in your build directory and execute:
```bash
cmake -S \<path to cml-root\> -G{generator name} -DBUILD_TESTING=On -DCMAKE_BUILD_TYPE=Release
```
Then, to build the tests (again from your build directory):
```bash
cmake --build . --config Release
```
You can run the full test suite from your build directory by executing:
```bash
ctest -C Release
```
If you have multiple CPUs (e.g. 4 in this case), you can speed things up a bit using, for example:
```bash
cmake --build . --config Release -- -j4
ctest -C Release -j4
```
### With CMake presets
See _CMakePresets.json_ for the default base presets, as well as the predefined configure and build presets. Note that all of the predefined configure presets generate a build system under _\<cml-root\>/.build_/\<preset-name\>.

To see the available configure presets, execute:
```bash
cmake --list-presets
```
To see the available build presets, execute:
```bash
cmake --build --list-presets
```
To use one of the predefined configure presets, for example _cml-dev-msvc17-clangcl-mt-s_ to use the Visual Studio 2022 IDE with ClangCL:
```bash
cmake --preset=cml-dev-msvc17-clangcl-mt-s
```