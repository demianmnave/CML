# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

# Set the minimum CMake version:
cmake_minimum_required(VERSION 3.28)

# Policies:
cmake_policy(SET CMP0022 NEW) # Export interface libraries
cmake_policy(SET CMP0048 NEW) # Enable VERSION variables
cmake_policy(SET CMP0091 NEW) # Enable MSVC ABI selection

# Enable solution folders globally:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(build-macros)

# Set the project version:
cml_version_from_file(
  ${CMAKE_CURRENT_LIST_DIR}/cml/version.h # Path to version.h
  "CML_VERSION" # The macro name to find
  _CML_VERSION_MAJOR # Parsed major version
  _CML_VERSION_MINOR # Parsed minor version
  _CML_VERSION_PATCH # Parsed patch version
  _CML_VERSION # String MM.mm.pp
)
project(cml VERSION ${_CML_VERSION} LANGUAGES CXX)
message(STATUS "Building ${PROJECT_NAME} ${CML_VERSION}")

if(NOT DEFINED CMAKE_CXX_COMPILER_ID)
  message(FATAL_ERROR "${PROJECT_NAME} requires a C++ compiler")
endif()

# Standard includes:
include(CMakeDependentOption)

if(NOT DEFINED BUILD_SHARED_LIBS)
  option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

if(NOT DEFINED BUILD_STATIC_RUNTIME)
  cmake_dependent_option(BUILD_STATIC_RUNTIME
    "Build against a static runtime" ON
    "NOT BUILD_SHARED_LIBS" OFF
  )
endif()

if(NOT DEFINED CML_ENABLE_RELATIVE_TEST_PATHS)
  # Force CTest to use relative paths. Primarily for automated testing:
  cmake_dependent_option(CML_ENABLE_RELATIVE_TEST_PATHS
    "Make test executable paths relative to CMAKE_BINARY_DIR"
    OFF  # Show and default to OFF if...
    "BUILD_TESTING"
    OFF  # Otherwise, default to OFF.
  )
endif()

if(NOT DEFINED CML_CXX_STD)
  set(CML_CXX_STD cxx_std_17)
endif()

include(default-paths)
include(${CMAKE_CXX_COMPILER_ID}-compiler)

# Create the CML interface library:
add_subdirectory(cml)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# # Installation and packaging:
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#   ${CMAKE_CURRENT_BINARY_DIR}/cml-config-version.cmake
#   VERSION ${CML_VERSION}
#   COMPATIBILITY ExactVersion
# )

# include(GNUInstallDirs)
# install(TARGETS cml DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT cml-targets)
# install(EXPORT cml-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cml FILE cml-targets.cmake)
# install(DIRECTORY cml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*")
# install(FILES
#   ${CMAKE_CURRENT_BINARY_DIR}/cml-config-version.cmake
#   cmake/cml-config.cmake
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cml
# )

# export(EXPORT cml-targets FILE cml-config.cmake)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(NOT DEFINED CML_INSTALL_CMAKEDIR)
   set(CML_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/cml"
       CACHE STRING "Path to CML CMake files")
endif()

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/cml-config-version.cmake"
    COMPATIBILITY ExactVersion
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cml-config.cmake.in"
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/cml-config.cmake"
    INSTALL_DESTINATION "${CML_INSTALL_CMAKEDIR}"
    )

set(_TARGET_FILE "cml-targets.cmake")

# Installation rules:
install(
  EXPORT Targets
  DESTINATION "${CML_INSTALL_CMAKEDIR}"
  FILE "${_TARGET_FILE}"
  COMPONENT "Development"
  )

install(
  FILES
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/cml-config.cmake"
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/cml-config-version.cmake"
  DESTINATION "${CML_INSTALL_CMAKEDIR}"
  COMPONENT "Development"
  )

# Support use directly from the build directory:
export(
  EXPORT Targets
  FILE "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/${_TARGET_FILE}"
  )