# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

CMAKE_MINIMUM_REQUIRED(VERSION 2.4 FATAL_ERROR)
PROJECT(CML)

# Setup PSCCMakeTools:
SET(PSCCMakeTools_DIR ${CMAKE_SOURCE_DIR}/PSCCMakeTools)
SET(PSC_TOOL_NAME CML)
SET(PSC_TOOL_WIN32_NAME CML)
SET(PSC_TOOL_UNIX_NAME cml)

# Add the toplevel CMake and PSCCMakeTools directories for searching:
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${PSCCMakeTools_DIR})

# Pick up PSCCMakeToolsCommonMacros.cmake:
INCLUDE(PSCCMakeToolsCommonMacros)

# Disable exporting build settings, which aren't needed (CML is a header
# only libeary):
SET(PSC_TOOL_EXPORT_BUILD_SETTINGS FALSE)

# Generate the tool version:
SetToolVersion(1.0b1)

# Systools version number:
MESSAGE(STATUS "Building CML ${CML_VERSION}")

# Don't build tests by default:
OPTION(BUILD_TESTS "Build CML tests." OFF)
SET(CML_BUILD_TESTS ${BUILD_TESTS})

# Include the source CML headers before others:
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

# Setup install paths:
#SET(PSC_TOOL_PATH_VERSION)
#SET(PSC_TOOL_PATH_VARIANT ${CMAKE_BUILD_TYPE})
SET(PSC_TOOL_CONFIG_NAME "CML")
SetupToolInstallation()

# Add subdirectories to build:
ADD_SUBDIRECTORY(cml)
IF(CML_BUILD_TESTS)
  ADD_SUBDIRECTORY(tests)
ENDIF(CML_BUILD_TESTS)

# Generate install rules:
SetupToolInstallRules()

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
#INCLUDE(CMLCPackSetup)
IF(WIN32 AND NOT UNIX)

  # Use NSIS on Windows:
  SET(CPACK_GENERATOR "NSIS")
  SET(CMAKE_INSTALL_PREFIX "")

  SET(CPACK_TEMPORARY_DIRECTORY
    "${CMAKE_BINARY_DIR}/_BuiltPackages/${_Package}")
  SET(CPACK_TEMPORARY_INSTALL_DIRECTORY ${CPACK_TEMPORARY_DIRECTORY})

  SET(CPACK_PACKAGE_NAME "CML")
  SET(CPACK_PACKAGE_FILE_NAME "CML-1.0b1")
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CML for Windows")
  SET(CPACK_PACKAGE_VENDOR "Jesse Krebs, Demian Nave")
  #SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/About.txt")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.rtf")
  #SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
  #SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/Welcome.txt")
  SET(CPACK_PACKAGE_VERSION 1.0b1)
  #SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/<icon>")
  #SET(CPACK_PACKAGE_EXECUTABLES "" "")
  INCLUDE(CPack)
ENDIF(WIN32 AND NOT UNIX)

# --------------------------------------------------------------------------
# vim:ft=cmake
