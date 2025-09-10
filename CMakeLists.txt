# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

set(CML_ROOT "${CMAKE_CURRENT_LIST_DIR}")
list(APPEND CMAKE_MODULE_PATH ${CML_ROOT}/cmake)
include(CMakeDependentOption)
include(CMLBuildMacros)

# Set the minimum CMake version:
cmake_minimum_required(VERSION 3.25)

# Policies:
cmake_policy(SET CMP0091 NEW) # Enable MSVC ABI selection

# Enable solution folders globally:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Just enable Debug and Release for multi-config generators:
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Set the project version:
cml_version_from_file(
  ${CML_ROOT}/cml/version.h # Path to version.h
  "CML_VERSION" # The macro name to find
  _CML_VERSION_MAJOR # Parsed major version
  _CML_VERSION_MINOR # Parsed minor version
  _CML_VERSION_PATCH # Parsed patch version
  _CML_VERSION # String MM.mm.pp
)
project(CML VERSION ${_CML_VERSION})

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
if(MSVC)
  if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
    if(BUILD_STATIC_RUNTIME)
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif()
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
  cmake/cml-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cml
)

export(EXPORT cml-targets FILE cml-config.cmake)