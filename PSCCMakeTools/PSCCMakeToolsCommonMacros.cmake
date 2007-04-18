# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

SET(CMAKE_BUILD_TYPE_HELP "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")

IF(NOT PSC_TOOL_NAME)
  MESSAGE(FATAL_ERROR "PSC_TOOL_NAME is not defined.")
ENDIF(NOT PSC_TOOL_NAME)
IF(NOT PSC_TOOL_WIN32_NAME)
  MESSAGE(FATAL_ERROR "PSC_TOOL_WIN32_NAME is not defined.")
ENDIF(NOT PSC_TOOL_WIN32_NAME)
IF(NOT PSC_TOOL_UNIX_NAME)
  MESSAGE(FATAL_ERROR "PSC_TOOL_UNIX_NAME is not defined.")
ENDIF(NOT PSC_TOOL_UNIX_NAME)

# Make sure CMAKE_BUILD_TYPE is set before the user starts configuring:
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING ${CMAKE_BUILD_TYPE_HELP} FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Export build settings by default:
SET(PSC_TOOL_EXPORT_BUILD_SETTINGS TRUE)

# Generate the variables holding the project's VERSION string, and the
# variables holding the MAJOR, MINOR, and PATCH versions.  _VersionString
# is expected to be in <major>.<minor>.<patch> format, where each component
# can be any series of alphanumeric characters. These vars can be used to
# populate the CPACK_PACKAGE_VERSION[_{MAJOR,MINOR,PATCH}] variables:
MACRO(SetToolVersion _VersionString)
  SET(_name ${PSC_TOOL_NAME})
  STRING(REGEX REPLACE "([:alnum:]+).([:alnum:]+).([:alnum:]+)"
    "\\1" ${_name}_VERSION_MAJOR ${_VersionString})
  STRING(REGEX REPLACE "([:alnum:]+).([:alnum:]+).([:alnum:]+)"
    "\\2" ${_name}_VERSION_MINOR ${_VersionString})
  STRING(REGEX REPLACE "([:alnum:]+).([:alnum:]+).([:alnum:]+)"
    "\\3" ${_name}_VERSION_PATCH ${_VersionString})
  SET(${_name}_VERSION ${_VersionString})
ENDMACRO(SetToolVersion)

MACRO(SetupToolInstallation)
  SET(_name ${PSC_TOOL_NAME})
  SET(_win32_name ${PSC_TOOL_WIN32_NAME})
  SET(_unix_name ${PSC_TOOL_UNIX_NAME})
  IF(PSC_TOOL_CONFIG_NAME)
    SET(_config_name ${PSC_TOOL_CONFIG_NAME})
  ELSE(PSC_TOOL_CONFIG_NAME)
    MESSAGE(FATAL_ERROR "PSC_TOOL_CONFIG_NAME is not defined.")
  ENDIF(PSC_TOOL_CONFIG_NAME)
  IF(${_name}_VERSION)
    SET(_version ${${_name}_VERSION})
  ENDIF(${_name}_VERSION)

  # Local copies of the version and variant paths (may be undefined):
  SET(_version_path ${PSC_TOOL_PATH_VERSION})
  SET(_variant_path ${PSC_TOOL_PATH_VARIANT})

  # Generate the build path from the version and variant paths:
  SET(_build_path)
  IF(_version_path)
    SET(_build_path "${_build_path}${_version_path}/")
  ENDIF(_version_path)
  IF(_variant_path)
    SET(_build_path "${_build_path}${_variant_path}/")
  ENDIF(_variant_path)

  # Record the installation paths (these are also used in subdirectory
  # INSTALL rules, and must be here before any ADD_SUBDIRECTORY command):
  IF(WIN32 AND NOT UNIX)

    # On Windows, put everything under the same installation directory:
    IF(NOT CMAKE_INSTALL_PREFIX)
      SET(CMAKE_INSTALL_PREFIX "C:/Program Files/${_win32_name}"
	CACHE PATH "Install path prefix.")
      IF(_version)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX} ${_version"
	  CACHE PATH "Install path prefix.")
      ENDIF(_version)
    ENDIF(NOT CMAKE_INSTALL_PREFIX)

    # Where to find <tool>Config[Helper].cmake:
    SET(${_name}_INSTALL_ROOT "")
    # Note: this puts <tool>Config[Helper].cmake into CMAKE_INSTALL_PREFIX.

    # Where to find <tool>Config.cmake, Use<tool>.cmake, and
    # <tool>ConfigLibraries.cmake:
    SET(${_name}_CONFIG_PATH "${_build_path}")

    # Where to find the installed libraries:
    SET(${_name}_LIBRARY_PATH "${_build_path}")

    # Include directory, common to all installed builds (there is currently
    # no variant directory modifier for headers):
    SET(${_name}_HEADER_PATH "${_version_path}")
    # Note: this puts headers into a versioned directory under
    # CMAKE_INSTALL_PREFIX.

    # Set the build's library output path:
    SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${_build_path}")
  ELSE(WIN32 AND NOT UNIX)

    # By default, make all files relative to CMAKE_INSTALL_PREFIX, which
    # for UNIX will be e.g. /usr/local or /usr:
    IF(NOT CMAKE_INSTALL_PREFIX)
      SET(CMAKE_INSTALL_PREFIX "/usr/local")
    ENDIF(NOT CMAKE_INSTALL_PREFIX)

    # Where to find <tool>Config[Helper].cmake:
    SET(${_name}_INSTALL_ROOT "lib/${_unix_name}/")

    # Where to find <tool>Config.cmake, Use<tool>.cmake, and
    # <tool>ConfigLibraries.cmake:
    SET(${_name}_CONFIG_PATH "lib/${_unix_name}/${_build_path}")

    # Where to find the installed libraries:
    SET(${_name}_LIBRARY_PATH "lib/${_unix_name}/${_build_path}")

    # Include directory, common to all installed builds (there is currently
    # no variant directory modifier for headers):
    SET(${_name}_HEADER_PATH "include/")
    IF(_version_path)
      SET(${_name}_HEADER_PATH "include/${_unix_name}/${_version_path}/")
    ENDIF(_version_path)
    # Note: by default, headers go into CMAKE_INSTALL_PREFIX/include.  If
    # the headers are versioned, then they go into
    # CMAKE_INSTALL_PREFIX/${_unix_name}/${_version_path}.

    # Set the build's library output path:
    SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${_build_path}")
  ENDIF(WIN32 AND NOT UNIX)
ENDMACRO(SetupToolInstallation)


MACRO(SetupToolInstallRules)
  SET(_name ${PSC_TOOL_NAME})
  IF(PSC_TOOL_CONFIG_NAME)
    SET(_config_name ${PSC_TOOL_CONFIG_NAME})
  ELSE(PSC_TOOL_CONFIG_NAME)
    MESSAGE(FATAL_ERROR "PSC_TOOL_CONFIG_NAME is not defined.")
  ENDIF(PSC_TOOL_CONFIG_NAME)

  # These variables have to be set by calling SetupToolInstallation:
  SET(_check_var_list
    #${_name}_INSTALL_ROOT
    #${_name}_CONFIG_PATH
    LIBRARY_OUTPUT_PATH
    )
  FOREACH(_check_var ${_check_var_list})
    IF(NOT ${_check_var})
      MESSAGE(FATAL_ERROR "${_check_var} is not defined.")
    ENDIF(NOT ${_check_var})
  ENDFOREACH(_check_var)

  # Local copies of the version and variant paths (may be undefined):
  SET(_version_path ${PSC_TOOL_PATH_VERSION})
  SET(_variant_path ${PSC_TOOL_PATH_VARIANT})

  # Generate the build path from the version and variant paths:
  SET(_build_path)
  IF(_version_path)
    SET(_build_path "${_build_path}${_version_path}/")
  ENDIF(_version_path)
  IF(_variant_path)
    SET(_build_path "${_build_path}${_variant_path}/")
  ENDIF(_variant_path)


  # Local copy of ${_name}_INSTALL_ROOT:
  SET(_rootdir ${${_name}_INSTALL_ROOT})

  # Local copy of ${_name}_HEADER_PATH:
  SET(_incdir ${${_name}_HEADER_PATH})

  # Local copy of ${_name}_LIBRARY_PATH:
  SET(_libdir ${${_name}_LIBRARY_PATH})

  # Local copy of ${_name}_CONFIG_PATH:
  SET(_confdir ${${_name}_CONFIG_PATH})


  # Setup variables used by the config file templates:

  # This is the file that the FIND_PACKAGE(<tool>) command
  # finds. It sets up variables required by Use<tool>.cmake:
  SET(_TemplateConfigFile ${_config_name}Config.cmake)

  # This is the file that is included from the project CMakeLists.txt after
  # ${_config_name}Config.cmake has been found:
  SET(_TemplateUseFile Use${_config_name}.cmake)

  # The settings used to build the current installation:
  IF(PSC_TOOL_EXPORT_BUILD_SETTINGS)
    SET(_TemplateBuildSettingsFile ${_config_name}BuildSettings.cmake)
  ENDIF(PSC_TOOL_EXPORT_BUILD_SETTINGS)

  # The library dependencies file:
  SET(_TemplateLibDependenciesFile ${_config_name}LibraryDependencies.cmake)

  # Extra configuration commands, INCLUDE'd from <tool>Config.cmake:
  SET(_TemplateConfigExtraFile ${_config_name}ConfigExtra.cmake)

  # Extra configuration commands, INCLUDE'd from Use<tool>.cmake:
  SET(_TemplateUseExtraFile Use${_config_name}Extra.cmake)

  # Required CXX flags (not required to be defined):
  SET(_TemplateRequiredCxxFlags ${${_name}_REQUIRED_CXX_FLAGS})

  # This is the build path, relative to CMAKE_INSTALL_PREFIX:
  SET(_TemplateBuildVersion ${_version_path})
  SET(_TemplateBuildVariant ${_variant_path})

  # This is the installation path-relative path to installed libraries and
  # configuration files:
  SET(_TemplateLibDir ${_libdir})

  # This is the path to installed headers:
  SET(_TemplateIncDir ${_incdir})

  # Adjust the relative installation path based upon system:
  IF(WIN32 AND NOT UNIX)
    SET(_TemplateRelativeInstallDir)
    # Note: On Windows, everything is installed under the same path, so
    # only the version and variant directories will induce a relative path.
  ELSE(WIN32 AND NOT UNIX)
    SET(_TemplateRelativeInstallDir "/../..")
    # Note: the two extra ".." on UNIX account for lib/<unix name> after
    # CMAKE_INSTALL_PREFIX.
  ENDIF(WIN32 AND NOT UNIX)
  # Note: This path manipulation is used to find the base installation path
  # (e.g. C:/Program Files/<tool> on Windows or /usr/local/ on UNIX), to
  # support arbitrary installation paths.

  # Account for the version and variant paths:
  IF(PSC_TOOL_PATH_VERSION)
    SET(_TemplateRelativeInstallDir "${_TemplateRelativeInstallDir}/..")
  ENDIF(PSC_TOOL_PATH_VERSION)
  IF(PSC_TOOL_PATH_VARIANT)
    SET(_TemplateRelativeInstallDir "${_TemplateRelativeInstallDir}/..")
  ENDIF(PSC_TOOL_PATH_VARIANT)


  # Setup and install the configuration files:

  # <tool>Config[Helper] goes into the installation root to help find the
  # most recent version and/or variant of a build.  It is only configured
  # if there is a separate version and/or variant defined, since otherwise
  # the most recent installation lives entirely in <tool>_INSTALL_ROOT:
  IF(PSC_TOOL_PATH_VERSION OR PSC_TOOL_PATH_VARIANT)
    CONFIGURE_FILE(
      ${PSCCMakeTools_DIR}/Templates/ToolConfigHelperTemplate.cmake.in
      ${CMAKE_BINARY_DIR}/${_TemplateConfigFile}
      @ONLY)
    INSTALL(
      FILES ${CMAKE_BINARY_DIR}/${_TemplateConfigFile}
      DESTINATION "${${_name}_INSTALL_ROOT}")
  ENDIF(PSC_TOOL_PATH_VERSION OR PSC_TOOL_PATH_VARIANT)

  # This is the file that the FIND_PACKAGE(<tool>) command finds either
  # directly or via <tool>ConfigHelper. It sets up variables required by
  # Use<tool>.cmake:
  CONFIGURE_FILE(
    ${PSCCMakeTools_DIR}/Templates/ToolConfigTemplate.cmake.in
    ${LIBRARY_OUTPUT_PATH}/${_config_name}Config.cmake
    @ONLY)
  INSTALL(
    FILES ${LIBRARY_OUTPUT_PATH}/${_config_name}Config.cmake
    DESTINATION "${_confdir}")

  # This is the file that is included from the project CMakeLists.txt after
  # ${_config_name}Config.cmake has been found:
  CONFIGURE_FILE(
    ${PSCCMakeTools_DIR}/Templates/UseToolTemplate.cmake.in
    ${LIBRARY_OUTPUT_PATH}/${_TemplateUseFile}
    @ONLY)
  INSTALL(
    FILES ${LIBRARY_OUTPUT_PATH}/${_TemplateUseFile}
    DESTINATION "${_confdir}")

  # Export and install the build settings:
  IF(PSC_TOOL_EXPORT_BUILD_SETTINGS)
    INCLUDE(CMakeExportBuildSettings)
    CMAKE_EXPORT_BUILD_SETTINGS(
      ${LIBRARY_OUTPUT_PATH}/${_TemplateBuildSettingsFile})
    INSTALL(
      FILES ${LIBRARY_OUTPUT_PATH}/${_TemplateBuildSettingsFile}
      DESTINATION "${_confdir}")
  ENDIF(PSC_TOOL_EXPORT_BUILD_SETTINGS)

  # Export and install the library dependencies file:
  EXPORT_LIBRARY_DEPENDENCIES(
    ${LIBRARY_OUTPUT_PATH}/${_TemplateLibDependenciesFile})
  INSTALL(
    FILES ${LIBRARY_OUTPUT_PATH}/${_TemplateLibDependenciesFile}
    DESTINATION "${_confdir}")

  # If <tool>ConfigExtra.cmake.in exists, configure and install it:
  IF(EXISTS ${CMAKE_SOURCE_DIR}/${_TemplateConfigExtraFile}.in)
    CONFIGURE_FILE(
      ${CMAKE_SOURCE_DIR}/${_TemplateConfigExtraFile}.in
      ${LIBRARY_OUTPUT_PATH}/${_TemplateConfigExtraFile}
      @ONLY)
    INSTALL(
      FILES ${LIBRARY_OUTPUT_PATH}/${_TemplateConfigExtraFile}
      DESTINATION "${_confdir}")
  ENDIF(EXISTS ${CMAKE_SOURCE_DIR}/${_TemplateConfigExtraFile}.in)

  # If Use<tool>Extra.cmake.in exists, configure and install it:
  IF(EXISTS ${CMAKE_SOURCE_DIR}/${_TemplateUseExtraFile}.in)
    CONFIGURE_FILE(
      ${CMAKE_SOURCE_DIR}/${_TemplateUseExtraFile}.in
      ${LIBRARY_OUTPUT_PATH}/${_TemplateUseExtraFile}
      @ONLY)
    INSTALL(
      FILES ${LIBRARY_OUTPUT_PATH}/${_TemplateUseExtraFile}
      DESTINATION "${_confdir}")
  ENDIF(EXISTS ${CMAKE_SOURCE_DIR}/${_TemplateUseExtraFile}.in)
ENDMACRO(SetupToolInstallRules)

# --------------------------------------------------------------------------
# vim:ft=cmake
