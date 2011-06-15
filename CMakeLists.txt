# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

CMAKE_MINIMUM_REQUIRED(VERSION 2.4 FATAL_ERROR)
PROJECT(CML)

# Build the current CML version number:
SET(CML_MAJOR 1)
SET(CML_MINOR 0)
SET(CML_PATCH 3)
SET(CML_RELEASE_VERSION "${CML_MAJOR}.${CML_MINOR}.${CML_PATCH}")
SET(CML_FILE_VERSION "${CML_MAJOR}_${CML_MINOR}_${CML_PATCH}")

# Handy message:
MESSAGE(STATUS "Building CML ${CML_RELEASE_VERSION}")

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# XXX Importing build settings for a header-only library leads to annoying
# "Setting CML_BUILD_TYPE to T" warnings:
# Installation configuration:
#INCLUDE(CMakeExportBuildSettings)
IF(WIN32)

  # The paths relative to the installation path into which libraries and
  # headers should be installed for Windows builds (there are currently no
  # libraries to install):
  SET(CML_LIBARARY_PATH)
  SET(CML_HEADER_PATH)
ELSE(WIN32)

  # The paths relative to the installation path into which libraries and
  # headers should be installed for UNIX-like builds (there are currently
  # no libraries to install):
  SET(CML_LIBARARY_PATH lib)
  SET(CML_HEADER_PATH include)
ENDIF(WIN32)

# Don't build tests by default:
OPTION(BUILD_TESTS "Build CML tests." OFF)
SET(CML_BUILD_TESTS ${BUILD_TESTS})

# Include the source CML headers before others:
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

# Add subdirectories to build:
ADD_SUBDIRECTORY(cml)
ADD_SUBDIRECTORY(examples)
IF(CML_BUILD_TESTS)
  ADD_SUBDIRECTORY(tests)
ENDIF(CML_BUILD_TESTS)

# Setup configuration files:
CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/UseCML.cmake.in
  ${CMAKE_BINARY_DIR}/UseCML.cmake
  @ONLY
  )

CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/CMLConfig.cmake.in
  ${CMAKE_BINARY_DIR}/CMLConfig.cmake
  @ONLY
  )

# XXX Importing build settings for a header-only library leads to annoying
# "Setting CML_BUILD_TYPE to T" warnings:
# CMAKE_EXPORT_BUILD_SETTINGS(
#   ${CMAKE_BINARY_DIR}/CMLBuildSettings.cmake)
# INSTALL(FILES
#   ${CMAKE_BINARY_DIR}/CMLBuildSettings.cmake
#   DESTINATION .
#   )

INSTALL(FILES
  ${CMAKE_BINARY_DIR}/UseCML.cmake
  ${CMAKE_BINARY_DIR}/CMLConfig.cmake
  DESTINATION .
  )

INSTALL(FILES
  ${CMAKE_SOURCE_DIR}/doc/parameters.txt
  DESTINATION doc
  )

INSTALL(FILES
  ${CMAKE_SOURCE_DIR}/examples/simple.cpp
  ${CMAKE_SOURCE_DIR}/examples/cml_config.h
  ${CMAKE_SOURCE_DIR}/examples/makefile
  ${CMAKE_SOURCE_DIR}/examples/CMakeLists.txt
  DESTINATION examples
  )

# Setup CPack:
IF(WIN32 AND NOT UNIX)

  # Build ZIP and NSIS packages:
  SET(CPACK_GENERATOR "NSIS;ZIP")

  # Set the name used by NSIS to refer to the project:
  SET(CPACK_NSIS_DISPLAY_NAME "CML ${CML_RELEASE_VERSION}")
  SET(CPACK_PACKAGE_VERSION_MAJOR ${CML_MAJOR})
  SET(CPACK_PACKAGE_VERSION_MINOR ${CML_MINOR})
  SET(CPACK_PACKAGE_VERSION_PATCH ${CML_PATCH})

  SET(CPACK_PACKAGE_FILE_NAME "cml-${CML_FILE_VERSION}")
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Configurable Math Libary")
  SET(CPACK_PACKAGE_VENDOR "Jesse Krebs, Demian Nave")
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY "cml-${CML_FILE_VERSION}")
  #SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/About.txt")
  #SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/<icon>")
  #SET(CPACK_PACKAGE_EXECUTABLES "" "")

  #SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/Welcome.txt")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.rtf")
  #SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")

  INCLUDE(CPack)
ENDIF(WIN32 AND NOT UNIX)

# --------------------------------------------------------------------------
# vim:ft=cmake
