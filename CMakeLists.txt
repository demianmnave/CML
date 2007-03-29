# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
PROJECT(CML)

# CML version number:
SET(CML_VERSION_MAJOR 1)
SET(CML_VERSION_MINOR 0)
SET(CML_VERSION_PATCH 0)
SET(CML_VERSION "${CML_VERSION_MAJOR}")
SET(CML_VERSION "${CML_VERSION}.${CML_VERSION_MINOR}")
SET(CML_VERSION "${CML_VERSION}.${CML_VERSION_PATCH}")

# Path to the CML source and binary directories:
SET(CML_SRC_ROOT ${CMAKE_SOURCE_DIR})
SET(CML_BUILD_ROOT ${CMAKE_BINARY_DIR})

# Add the toplevel CMake directory for searching:
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# Set the global location for libraries:
SET(LIBRARY_OUTPUT_PATH ${CML_BUILD_ROOT}/lib)


# Don't build tests by default:
OPTION(BUILD_TESTS "Build CML tests." OFF)
SET(CML_BUILD_TESTS ${BUILD_TESTS})

# Add the toplevel directory to all includes:
INCLUDE_DIRECTORIES(BEFORE ${CML_SRC_ROOT} ${CML_BUILD_ROOT})


# Record the installation paths (these are also used in subdirectory
# INSTALL rules, and must be here before any ADD_SUBDIRECTORY command):
IF(WIN32)

  # On Windows, put everything under the same installation directory:
  IF(NOT CMAKE_INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX "C:/Program Files/CML ${CML_VERSION}")
  ENDIF(NOT CMAKE_INSTALL_PREFIX)

  # The subdirectory under CMAKE_INSTALL_PREFIX into which the current
  # build goes:
  SET(CML_DIR "")

  # The directory into which build-specific files are installed:
  SET(CML_BUILD_PATH "${CML_DIR}")

  # Where to find CMLConfig.cmake, UseCML.cmake, and
  # CMLConfigLibraries.cmake:
  SET(CML_CONFIG_PATH "${CML_BUILD_PATH}")

  # Where to find the installed libraries:
  SET(CML_LIBRARY_PATH "${CML_BUILD_PATH}")

  # Include directory, common to all installed builds:
  SET(CML_HEADER_PATH "${CML_DIR}")

  # Set the library build output path:
  SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${CML_BUILD_PATH}")
ELSE(WIN32)

  # This is less important on UNIX, since most people know about
  # installations:
  IF(NOT CMAKE_INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX "/usr/local")
  ENDIF(NOT CMAKE_INSTALL_PREFIX)

  # The subdirectory under CMAKE_INSTALL_PREFIX into which the current
  # build goes:
  SET(CML_DIR "lib/cml")

  # The subdirectory under CMAKE_INSTALL_PREFIX into which the current
  # build goes:
  SET(CML_LIBRARY_ROOT "${CML_DIR}")

  # The subdirectory under CMAKE_INSTALL_PREFIX into which the headers
  # for the current build go:
  SET(CML_HEADER_ROOT "include")

  # The directory into which build-specific files are installed:
  SET(CML_BUILD_PATH "${CML_LIBRARY_ROOT}")

  # Where to find CMLConfig.cmake, UseCML.cmake, and
  # CMLConfigLibraries.cmake:
  SET(CML_CONFIG_PATH "${CML_BUILD_PATH}")

  # Where to find the installed libraries:
  SET(CML_LIBRARY_PATH "${CML_BUILD_PATH}")

  # Boost include directory, common to all installed builds:
  SET(CML_HEADER_PATH "${CML_HEADER_ROOT}")

  # Set the library build output path:
  SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
ENDIF(WIN32)

# Subdirectories to build:
ADD_SUBDIRECTORY(cml)
IF(CML_BUILD_TESTS)
  ADD_SUBDIRECTORY(tests)
ENDIF(CML_BUILD_TESTS)


# Setup config file names:

# This is the file that the FIND_PACKAGECML NO_MODULE) command
# finds. It sets up variables required by UseCML.cmake:
SET(CML_CONFIG_FILE CMLConfig.cmake)

# This is the file that is included from the project CMakeLists.txt after
# CMLConfig.cmake has been found:
SET(CML_USE_FILE UseCML.cmake)

# The settings used to build the current installation:
SET(CML_BUILD_SETTINGS_FILE CMLBuildSettings.cmake)


#-- # Configure the global config.h file (it will be installed by
#-- # systools/CMakeLists.txt):
#-- CONFIGURE_FILE(
#--   ${CMAKE_SOURCE_DIR}/config.h.in
#--   ${CMAKE_BINARY_DIR}/cml/config.h
#--   @ONLY)

# Configure and install the main config file:
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/${CML_CONFIG_FILE}.in
  ${LIBRARY_OUTPUT_PATH}/${CML_CONFIG_FILE}
  @ONLY)
INSTALL(
  FILES ${LIBRARY_OUTPUT_PATH}/${CML_CONFIG_FILE}
  DESTINATION ${CML_CONFIG_PATH})

# Configure and install the per-project configuration file (generally
# included from a project's top-level CMakeLists.txt):
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/${CML_USE_FILE}.in
  ${LIBRARY_OUTPUT_PATH}/${CML_USE_FILE}
  COPYONLY)
INSTALL(
  FILES ${LIBRARY_OUTPUT_PATH}/${CML_USE_FILE}
  DESTINATION ${CML_CONFIG_PATH})

# Export and install the build settings:
INCLUDE(CMakeExportBuildSettings)
CMAKE_EXPORT_BUILD_SETTINGS(
  ${LIBRARY_OUTPUT_PATH}/${CML_BUILD_SETTINGS_FILE})
INSTALL(
  FILES ${LIBRARY_OUTPUT_PATH}/${CML_BUILD_SETTINGS_FILE}
  DESTINATION ${CML_CONFIG_PATH})

# --------------------------------------------------------------------------
# vim:ft=cmake
