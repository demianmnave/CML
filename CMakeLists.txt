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

## Setup and install the config.h header:
#CONFIGURE_FILE(
#  ${CMAKE_SOURCE_DIR}/config.h.in
#  ${CMAKE_BINARY_DIR}/cml/config.h
#  @ONLY
#  )
#INSTALL(
#  FILES ${CMAKE_BINARY_DIR}/cml/config.h
#  DESTINATION "${CML_HEADER_PATH}cml"
#  )

# Setup CPack:
IF(WIN32 AND NOT UNIX)

  # Use NSIS on Windows:
  SET(CPACK_GENERATOR "NSIS")
  SET(CMAKE_INSTALL_PREFIX "")

  SET(CPACK_TEMPORARY_DIRECTORY
    "${CMAKE_BINARY_DIR}/_BuiltPackages/${_Package}")
  SET(CPACK_TEMPORARY_INSTALL_DIRECTORY ${CPACK_TEMPORARY_DIRECTORY})

  SET(CPACK_PACKAGE_NAME "CML")
  SET(CPACK_PACKAGE_FILE_NAME "CML-${CML_VERSION_STRING}")
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CML for Windows")
  SET(CPACK_PACKAGE_VENDOR "Jesse Krebs, Demian Nave")
  #SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/About.txt")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.rtf")
  #SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
  #SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/Welcome.txt")
  SET(CPACK_PACKAGE_VERSION ${CML_VERSION_STRING})
  #SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/<icon>")
  #SET(CPACK_PACKAGE_EXECUTABLES "" "")
  INCLUDE(CPack)
ENDIF(WIN32 AND NOT UNIX)

# --------------------------------------------------------------------------
# vim:ft=cmake
