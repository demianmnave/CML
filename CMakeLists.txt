# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

# Set the minimum CMake version:
cmake_minimum_required(VERSION 3.15)

# Policies:
cmake_policy(SET CMP0091 NEW) # Enable MSVC ABI selection

# Enable solution folders globally:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Just enable Debug and Release for multi-config generators:
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# The project name:
project(CML)

# Path to the project source tree:
set(CML_ROOT "${CML_SOURCE_DIR}")

# Path to project-specific configuration files:
list(APPEND CMAKE_MODULE_PATH ${CML_ROOT}/CMake)
include(CMLBuildMacros)

include(CMakeDependentOption)

if(NOT DEFINED BUILD_SHARED_LIBS)
  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

if(NOT DEFINED BUILD_STATIC_RUNTIME)
  cmake_dependent_option(BUILD_STATIC_RUNTIME
    "Build against a static runtime"
    ON # Default if shown when...
    "NOT BUILD_SHARED_LIBS"
    OFF # Default if not shown
  )
endif()

# Determine the default runtime library for MSVC-like compilers:
if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
  if(BUILD_STATIC_RUNTIME)
    set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  else()
    set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  endif()
endif()

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug/bin)
endif()

if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug/lib)
endif()

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG)
  # Put debug DLLs into debug/bin for WIN32 systems:
  if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug/bin)
  else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug/lib)
  endif()
endif()

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
endif()

if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
endif()

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE)
  # Put release DLLs into bin for WIN32 systems:
  if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
  else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
  endif()
endif()

# Figure out which version of CML is being built by parsing CML/version.h (this
# is from the root Boost.CMake CMakeLists.txt file):
cml_version_from_file(
  ${CML_ROOT}/cml/version.h # Path to version.h
  "CML_VERSION" # The macro name to find
  CML_VERSION_MAJOR # Parsed major version
  CML_VERSION_MINOR # Parsed minor version
  CML_VERSION_PATCH # Parsed patch version
  CML_VERSION # String MM.mm.pp
)
message(STATUS "Building CML ${CML_VERSION}")

# Create the CML interface library:
include(CML.cmake)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# Installation and packaging:
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/cml-config-version.cmake
  VERSION ${CML_VERSION}
  COMPATIBILITY ExactVersion
)

include(GNUInstallDirs)
install(TARGETS cml DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT cml-targets)
install(EXPORT cml-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cml FILE cml-targets.cmake)
install(DIRECTORY cml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*")
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cml-config-version.cmake
  CMake/cml-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cml
)

export(EXPORT cml-targets FILE cml-config.cmake)