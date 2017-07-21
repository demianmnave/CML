## Configurable Math Library v2

## License

The Configurable Math Library (CML) is released under the [Boost Software
License, Version 1.0.](http://www.boost.org/LICENSE_1_0.txt).


## Status

[![Build status](https://ci.appveyor.com/api/projects/status/r3l3xnhxe8djjimg/branch/cml2?svg=true)](https://ci.appveyor.com/project/demianmnave/cml/branch/cml2)
[![Build Status](https://travis-ci.org/demianmnave/CML.svg?branch=cml2)](https://travis-ci.org/demianmnave/CML)


## Using the CML

Currently, CML2 does not have a `make install` option.  As it is header-only, it is simple enough to copy the `cml` header directory into your project, and setup your build to reference it.


## Running Tests

To build and run the CML test suite, you will need a local Boost installation having at least Boost.Test.  The tests should work with Boost 1.54 and higher, but Boost 1.60 and higher is suggested. From the command line, start in your build directory and execute:

`cmake . -G<generator name> -DCML_BUILD_TESTING:Bool=On`

Then, to build the tests (again from your build directory):

`cmake --build . --config Release`

You can run the full test suite from your build directory by executing:

`ctest -C Release`

If you have multiple CPUs (e.g. 4 in this case), you can speed things up a bit using:

`ctest -C Release -j4`

If `cmake-gui` is available, you can use it to set CML_BUILD_TESTING to On.  A command prompt is still required to execute `ctest`, however.
