## Configurable Math Library

For CML version 1, please see https://github.com/demianmnave/CML1.

## License

The Configurable Math Library (CML) is released under the [Boost Software
License, Version 1.0.](http://www.boost.org/LICENSE_1_0.txt).


## Status

[![Build status](https://ci.appveyor.com/api/projects/status/r3l3xnhxe8djjimg/branch/master?svg=true)](https://ci.appveyor.com/project/demianmnave/cml/branch/master)
[![Build Status](https://travis-ci.com/demianmnave/CML.svg?branch=master)](https://travis-ci.com/github/demianmnave/CML)


## Using the CML

As it is header-only, it is simple enough to copy the `cml` header directory into your project and setup your build to reference it. Users of CMake 3.15+ can also leverage [`cmake --install ...`](make.org/cmake/help/v3.15/manual/cmake.1.html#install-a-project) and [`find_package(CML CONFIG)`](https://cmake.org/cmake/help/v3.15/command/find_package.html) to integrate CML into a CMake project.

## Running Tests

To run the test suite from a command prompt using a Makefile-like generator, start in your build directory and execute:

`cmake . -G<generator name> -DCML_BUILD_TESTING=On -DCML_BUILD_TYPE=RELEASE`

Then, to build the tests (again from your build directory):

`cmake --build . --config Release`

You can run the full test suite from your build directory by executing:

`ctest -C Release`

If you have multiple CPUs (e.g. 4 in this case), you can speed things up a bit using, for example:

`cmake --build . --config Release -- -j4`

`ctest -C Release -j4`

See .travis.yml for supported XCode, Clang, and GCC versions, and .appveyor.yml for supported Visual Studio versions.
