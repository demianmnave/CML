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

project(CML VERSION 2.4.1 LANGUAGES CXX)
message(STATUS "Building ${PROJECT_NAME} ${CML_VERSION}")

if(NOT DEFINED CMAKE_CXX_COMPILER_ID)
  message(FATAL_ERROR "${PROJECT_NAME} requires a C++ compiler")
endif()

# Standard includes:
include(CMakeDependentOption)

# Disable SIMD:
if(NOT DEFINED CML_DISABLE_SIMD)
  option(CML_DISABLE_SIMD "Disable vectorization (also disables timing tests)" OFF)
endif()

# Build tests if requested:
if(NOT DEFINED BUILD_TESTING)
  option(BUILD_TESTING "Build CML tests" OFF)
endif()

if(NOT DEFINED BUILD_TIMING)
  cmake_dependent_option(BUILD_TIMING
    "Build timing tests (requires SIMD)" OFF 
    "CML_DISABLE_SIMD" OFF
  )
endif()

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
    "Make test executable paths relative to CMAKE_BINARY_DIR" OFF
    "BUILD_TESTING" OFF
  )
endif()

if(NOT DEFINED CML_CXX_STD)
  set(CML_CXX_STD cxx_std_17)
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(default-paths)
include(configure-compiler)

# Create the CML interface library:
add_subdirectory(cml)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(NOT DEFINED CML_INSTALL_CMAKEDIR)
   set(CML_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/cml"
       CACHE STRING "Path to CML CMake files")
endif()

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/CMLConfigVersion.cmake"
    COMPATIBILITY ExactVersion
    )
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMLConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/CMLConfig.cmake"
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
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/CMLConfig.cmake"
    "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/CMLConfigVersion.cmake"
  DESTINATION "${CML_INSTALL_CMAKEDIR}"
  COMPONENT "Development"
  )

# Support use directly from the build directory:
export(
  EXPORT Targets
  FILE "${CMAKE_BINARY_DIR}/${CML_INSTALL_CMAKEDIR}/${_TARGET_FILE}"
  )