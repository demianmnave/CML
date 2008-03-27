# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

CMAKE_MINIMUM_REQUIRED(VERSION 2.4 FATAL_ERROR)
PROJECT(CML)

SET(CML_VERSION_MAJOR 1)
SET(CML_VERSION_MINOR 0)
SET(CML_VERSION_REV)
SET(CML_VERSION_STRING
  "${CML_VERSION_MAJOR}.${CML_VERSION_MINOR}${CML_VERSION_REV}")

# Systools version number:
MESSAGE(STATUS "Building CML ${CML_VERSION}")

# Installation configuration:
INCLUDE(CMakeExportBuildSettings)
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

CMAKE_EXPORT_BUILD_SETTINGS(
  ${CMAKE_BINARY_DIR}/CMLBuildSettings.cmake)
INSTALL(FILES
  ${CMAKE_BINARY_DIR}/CMLBuildSettings.cmake
  DESTINATION .
  )

INSTALL(FILES
  ${CMAKE_BINARY_DIR}/UseCML.cmake
  ${CMAKE_BINARY_DIR}/CMLConfig.cmake
  DESTINATION .
  )

# Setup CPack:
IF(WIN32 AND NOT UNIX)

  # Use NSIS on Windows:
  SET(CPACK_GENERATOR "NSIS;ZIP")
  #SET(CMAKE_INSTALL_PREFIX "")

  SET(CPACK_PACKAGE_NAME "CML")
  SET(CPACK_PACKAGE_FILE_NAME "CML-${CML_VERSION_STRING}")
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Configurable Math Libary")
  SET(CPACK_PACKAGE_VERSION ${CML_VERSION_STRING})
  SET(CPACK_PACKAGE_VENDOR "Jesse Krebs, Demian Nave")
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
