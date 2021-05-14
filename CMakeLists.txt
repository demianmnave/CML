# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Set the minimum CMake version:
cmake_minimum_required(VERSION 3.15)

# Allow solution folders:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# The project name:
project(CML)

# Path to the project source tree:
set(CML_ROOT "${CML_SOURCE_DIR}")

# Path to project-specific configuration files:
list(APPEND CMAKE_MODULE_PATH ${CML_ROOT}/CMake)

# Include project macros:
include(CMLBuildMacros)

# Figure out which version of CML is being built by parsing CML/version.h (this
# is from the root Boost.CMake CMakeLists.txt file):
cml_version_from_file(
  ${CML_ROOT}/cml/version.h		# Path to version.h
  "CML_VERSION"				    # The macro name to find
  CML_VERSION_MAJOR			    # Parsed major version
  CML_VERSION_MINOR			    # Parsed minor version
  CML_VERSION_PATCH			    # Parsed patch version
  CML_VERSION				    # String MM.mm.pp
  )
message(STATUS "Building CML ${CML_VERSION}")

# Create the CML interface library: 
include(CML.cmake)

# Build tests if requested:
option(CML_BUILD_TESTING "Build CML tests" OFF)
if(CML_BUILD_TESTING)
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