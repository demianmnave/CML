## Configurable Math Library
[![linux-ninja-clang](https://github.com/demianmnave/CML/actions/workflows/linux-ninja-clang.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/linux-ninja-clang.yml)
[![linux-ninja-gcc](https://github.com/demianmnave/CML/actions/workflows/linux-ninja-gcc.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/linux-ninja-gcc.yml)
[![windows-ninja-clangcl](https://github.com/demianmnave/CML/actions/workflows/windows-ninja-clangcl.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/windows-ninja-clangcl.yml)
[![windows-msbuild-msvc-17](https://github.com/demianmnave/CML/actions/workflows/windows-msbuild-msvc-17.yml/badge.svg)](https://github.com/demianmnave/CML/actions/workflows/windows-msbuild-msvc-17.yml)

A header-only library of C++ vector, matrix, and quaternion math expression templates and related functions
## License
The Configurable Math Library (CML) is released under the [Boost Software
License, Version 1.0.](http://www.boost.org/LICENSE_1_0.txt).
## Using the CML
As it is header-only, it is simple enough to copy the `cml` header directory into your project and setup your build to reference it. Users of CMake 3.15+ can also use [`cmake --install ...`](https://cmake.org/cmake/help/v3.15/manual/cmake.1.html#install-a-project) and [`find_package(cml CONFIG)`](https://cmake.org/cmake/help/v3.15/command/find_package.html) to integrate CML into a CMake project.
## Compiler requirements
The CML requires a compiler with C++17 support.
## Building and Running Tests
### With plain CMake
To run the test suite from a command prompt using a Makefile-like generator, start in your build directory and execute:
```bash
cmake -S <path to cml-root> -G{generator name} -DBUILD_TESTING=On -DCMAKE_BUILD_TYPE=Release
```
Note that this will download a compatible [Catch2](https://github.com/catchorg/Catch2) version used by the test suite. To build the tests (again from your build directory):
```bash
cmake --build . --config Release
```
You can run the full test suite from your build directory by executing:
```bash
ctest -C Release
```
If you have multiple CPUs, you can speed things up a bit; e.g.:
```bash
cmake --build . --config Release -- -j4
ctest -C Release -j4
```
### With CMake presets
See _CMakePresets.json_ for the default configure, build, test, and workflow presets. Additional inheritable presets can be found in _cmake/presets/\*.json_ for customization in [_CMakeUserPresets.json_](https://cmake.org/cmake/help/v3.28/manual/cmake-presets.7.html). Note that all of the predefined configure presets create a build directory under _\<cml-root\>/.build_, and those ending in _-vcpkg_ require [vcpkg](https://github.com/microsoft/vcpkg) to be cloned under _\<cml-root\>/vcpkg_.

To see the available presets by type, execute [`cmake --list-presets=<type>`](https://cmake.org/cmake/help/v3.28/manual/cmake.1.html#cmdoption-cmake-list-presets), where type can be `configure`, `build`, `test`, `workflow`, or `all`; e.g. to see the list of invocable presets when calling `cmake` on Windows:
```bash
> cmake --list-presets=all
Available configure presets:

  "windows-ninja-clangcl-mt-s-vcpkg"
  "windows-msbuild-msvc-17-mt-s-vcpkg"
  "windows-msbuild-clangcl-17-mt-s-vcpkg"

Available build presets:

  "windows-ninja-clangcl-mt-s-vcpkg-release"
  "windows-msbuild-msvc-17-mt-s-vcpkg-release"

Available test presets:

  "windows-ninja-clangcl-mt-s-vcpkg-test"
  "windows-msbuild-msvc-17-mt-s-vcpkg-test"

Available workflow presets:

  "windows-ninja-clangcl-mt-s-vcpkg"
  "windows-msbuild-msvc-17-mt-s-vcpkg"
  "linux-ninja-clang-s-vcpkg"
  "linux-ninja-gcc-s-vcpkg"
```
Note that all workflow presets will be shown even if not applicable to the running system (https://gitlab.kitware.com/cmake/cmake/-/issues/26236, https://discourse.cmake.org/t/condition-field-for-workflow-presets/6934).