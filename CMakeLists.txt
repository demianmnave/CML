# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Set the minimum CMake version:
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Allow solution folders:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# The project name:
project(CML)

# Path to the project source tree:
set(CML_ROOT "${CML_SOURCE_DIR}")

# Path to project-specific configuration files:
list(APPEND CMAKE_MODULE_PATH ${CML_ROOT}/CMake)

# Search for a Boost installation:
find_package(Boost 1.56 REQUIRED)

# Include project macros:
include(CMLBuildMacros)

# Figure out which version of CML is being built by parsing CML/version.h (this
# is from the root Boost.CMake CMakeLists.txt file):
CML_VERSION_FROM_FILE(
  ${CML_ROOT}/cml/version.h		# Path to version.h
  "CML_VERSION"				# The macro name to find
  CML_VERSION_MAJOR			# Parsed major version
  CML_VERSION_MINOR			# Parsed minor version
  CML_VERSION_PATCH			# Parsed patch version
  CML_VERSION				# String MM.mm.pp
  )
message(STATUS "Building CML ${CML_VERSION}")


# Modify build settings locally for static linking of tests and examples:
if(MINGW)

  # Convert compiler command lines to lists for easier manipulation:
  separate_arguments(CMAKE_CXX_FLAGS)

  # Enforce common compiler settings:
  list(APPEND CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
elseif(MSVC)

  # Convert compiler command lines to lists for easier manipulation:
  separate_arguments(CMAKE_CXX_FLAGS_DEBUG)
  separate_arguments(CMAKE_CXX_FLAGS_RELEASE)

  ## Remove runtime flags:
  set(runtime_flags /MD /MT /MTd /MDd)
  list(REMOVE_ITEM CMAKE_CXX_FLAGS ${runtime_flags})
  list(REMOVE_ITEM CMAKE_CXX_FLAGS_DEBUG ${runtime_flags})
  list(REMOVE_ITEM CMAKE_CXX_FLAGS_RELEASE ${runtime_flags})

  # Enforce common compiler settings:
  list(APPEND CMAKE_CXX_FLAGS_DEBUG "/MTd")
  list(APPEND CMAKE_CXX_FLAGS_RELEASE "/MT")
else()
  message(FATAL_ERROR "Unknown compiler")
endif()
list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS)
list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_RELEASE)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")



## Optional configuration:

# Enable tests if requested:
option(CML_BUILD_TESTING "Build CML tests" ON)
if(CML_BUILD_TESTING)
  include(CMLTestMacros)
  enable_testing()
endif()


## PATH CONFIGURATION ##

# Include directories:
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CML_ROOT})

# Output paths:
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


## Build subdirectories:

# Build tests if requested:
if(CML_BUILD_TESTING)
  add_subdirectory(tests)
endif()

# --------------------------------------------------------------------------
# vim:ft=cmake
