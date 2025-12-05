# CMake functions to reduce boilerplate when setting up targets.

include_guard()

# Get the TYPE target property of ${InTarget}.
#
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_get_target_type InTarget OutType)
  get_target_property(${OutType} ${InTarget} TYPE)
  set(${OutType} ${${OutType}} PARENT_SCOPE)
endfunction()

# Apply CML_TARGET_PROPERTIES to the named target if defined. ${InTarget} must
# already exist as a target.
#
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_target_properties_defaults InTarget)
  if(DEFINED CML_TARGET_PROPERTIES)
    set_target_properties(${InTarget} PROPERTIES ${CML_TARGET_PROPERTIES})
  endif()
endfunction()

# Apply:
#
#   CML_{PUBLIC,PRIVATE}_CXX_{OPTIONS,DEFINITIONS,FEATURES,OPTIONS_{DEBUG,RELEASE}}
#
# to the named target if defined. ${InTarget} must already exist as a target.
#
# Parameters:
#   InTarget: (required) string containing the target name :type
function(cml_target_compile_defaults InTarget)
  cml_get_target_type(${InTarget} _type)

  if("${_type}" STREQUAL "INTERFACE_LIBRARY")
    set(_scopes INTERFACE)
  else()
    set(_scopes PUBLIC PRIVATE)
  endif()

  foreach(_scope ${_scopes})
    if(DEFINED CML_${_scope}_CXX_OPTIONS)
      target_compile_options(${InTarget} ${_scope} ${CML_${_scope}_CXX_OPTIONS})
    endif()
    if(DEFINED CML_${_scope}_CXX_DEFINITIONS)
      target_compile_definitions(${InTarget} ${_scope} ${CML_${_scope}_CXX_DEFINITIONS})
    endif()
    if(DEFINED CML_${_scope}_CXX_FEATURES)
      target_compile_features(${InTarget} ${_scope} ${CML_${_scope}_CXX_FEATURES})
    endif()
    if(DEFINED CML_${_scope}_CXX_OPTIONS_DEBUG)
        target_compile_options(${InTarget} ${_scope} $<$<CONFIG:Debug>:${CML_${_scope}_CXX_OPTIONS_DEBUG}>)
    endif()
    if(DEFINED CML_${_scope}_CXX_OPTIONS_RELEASE)
        target_compile_options(${InTarget} ${_scope} $<$<CONFIG:Release>:${CML_${_scope}_CXX_OPTIONS_RELEASE}>)
    endif()
  endforeach()
endfunction()

function(cml_target_executable_properties_defaults InTarget)
  if(BUILD_SHARED_LIBS AND ${CML_ENABLE_RELATIVE_TEST_PATHS})
    # Use relative RPATHs in the build tree (will only take affect on platforms that
    # support it):
    set_target_properties(${InTarget} PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
  endif()
endfunction()

# Apply CML_{PUBLIC,PRIVATE}_EXE_LINK_OPTIONS to the named target if defined.
# ${InTarget} must already exist as a target and must not be an INTERFACE library.
#
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_target_executable_link_defaults InTarget)
  if(DEFINED CML_PUBLIC_EXE_LINK_OPTIONS)
      target_link_options(${InTarget} PUBLIC ${CML_PUBLIC_EXE_LINK_OPTIONS})
  endif()

  if(DEFINED CML_PRIVATE_EXE_LINK_OPTIONS)
      target_link_options(${InTarget} PRIVATE ${CML_PRIVATE_EXE_LINK_OPTIONS})
  endif()
endfunction()

# Apply standard computed library properties to the named target. ${InTarget}
# must already exist as a target.
#
# This sets the OUTPUT_NAME and EXPORT_NAME properties for a library target.
#
# If ${InTarget} is hyphenated, the string preceding the hyphen will be used as
# the namespace of the export; e.g. ab-libname can be referenced as ab::libname
# by consumers of the library.
#
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_target_library_properties_defaults InTarget)
  get_target_property(_export ${InTarget} EXPORT_NAME)
  if(NOT _export)
    string(REPLACE "-" "::" _alias ${InTarget})
    set(_export "${_alias}")
  endif()
  get_target_property(_libname ${InTarget} LIBRARY_OUTPUT_NAME)
  if(NOT _libname)
    string(REPLACE "-" "_" _libname ${InTarget})
    set(_libname "$<$<BOOL:${BUILD_STATIC_RUNTIME}>:lib>${_libname}$<$<CONFIG:Debug>:-d>")
  endif()

  set_target_properties(${InTarget} PROPERTIES
    LIBRARY_OUTPUT_NAME "${_libname}"
    EXPORT_NAME "${_export}"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    )

  # Set the folder if not already defined:
  get_target_property(_folder ${InTarget} FOLDER)
  if(NOT _folder)
    set_target_properties(${InTarget} PROPERTIES FOLDER "libs")
  endif()

  if(BUILD_SHARED_LIBS AND ${CML_ENABLE_RELATIVE_TEST_PATHS})
    # Use relative RPATHs for shared libs if requested (will only take affect on
    # platforms that support it):
    get_target_property(_type ${InTarget} TYPE)
    if(TYPE STREQUAL "SHARED_LIBRARY" OR TYPE STREQUAL "MODULE_LIBRARY")
      set_target_properties(${InTarget} PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
    endif()
  endif()
endfunction()

# Create installation rules for the named project.
#
# The EXPORT name is set to Targets.
# 
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_install_target InTarget)
  # Export file sets:
  get_target_property(_header_sets ${InTarget} HEADER_SETS)
  set(_file_sets)
  foreach(_hs IN LISTS _header_sets)
    list(APPEND _file_sets FILE_SET ${_hs})
  endforeach()

  install(TARGETS ${InTarget}
    EXPORT Targets
    LIBRARY COMPONENT "Runtime" NAMELINK_COMPONENT "Development"
    RUNTIME COMPONENT "Runtime"
    ARCHIVE COMPONENT "Development"
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT "Development"
    ${_file_sets}
  )
endfunction()

# Apply standard configuration to a library. ${InTarget} must already exist as a
# target.
#
# This is equivalent to:
#
#   cml_target_properties_defaults(${InTarget})
#   cml_target_compile_defaults(${InTarget})
#   cml_target_library_properties_defaults(${InTarget})
#   cml_install_target(${InTarget})
#
# Parameters:
#   InTarget: (required) string containing the target name
#   SKIP_INSTALL: (optional) do not install the target
function(cml_configure_library InTarget)
  set(flags SKIP_INSTALL)
  set(single_args)
  set(list_args)
  cmake_parse_arguments(arg "${flags}" "${single_args}" "${list_args}" ${ARGN})

  cml_target_properties_defaults(${InTarget})
  cml_target_compile_defaults(${InTarget})
  cml_target_library_properties_defaults(${InTarget})

  if(NOT arg_SKIP_INSTALL)
    cml_install_target(${InTarget})
  endif()
endfunction()

# Create a library and apply standard configuration.
#
# The target name is set to ${InTarget}. If a list of SOURCES is provided, it
# will be passed to target_sources(...).
#
# If ${InTarget} is hyphenated, the string preceding the hyphen will be used as
# the namespace of an alias target; e.g. ab-libname can be referenced as
# ab::libname by consumers of the library.
#
# Parameters:
#   InTarget: (required) string containing the target name
#
# Keywords:
#   INTERFACE, STATIC, SHARED, MODULE: (optional) the type of library to add
#   SOURCES: (optional) list of source files passed to target_sources(...)
#   USES: (optional) list of library dependencies passed to target_link_libraries(...)
#   FOLDER: (optional) path to the target in an IDE
#   SKIP_INSTALL: (optional) do not install the target
function(cml_add_library InTarget)
  set(flags INTERFACE STATIC SHARED MODULE)
  set(single_args FOLDER PREFIX)
  set(list_args SOURCES USES)
  cmake_parse_arguments(arg "${flags}" "${single_args}" "${list_args}" ${ARGN})

  set(conf_flags SKIP_INSTALL)
  set(conf_single_args)
  set(conf_list_args)
  cmake_parse_arguments(conf_arg "${conf_flags}" "${conf_single_args}" "${conf_list_args}" ${ARGN})

  if(${arg_INTERFACE})
    set(_type INTERFACE)
  elseif(${arg_STATIC})
    set(_type STATIC)
  elseif(${arg_SHARED})
    set(_type SHARED)
  elseif(${arg_MODULE})
    set(_type MODULE)
  else()
    set(_type)
  endif()

  string(REPLACE "-" "::" _alias ${InTarget})
  add_library(${InTarget} ${_type})
  if(NOT _alias STREQUAL InTarget)
    add_library(${_alias} ALIAS ${InTarget})
  endif()

  if(DEFINED arg_SOURCES)
    target_sources(${InTarget} PRIVATE ${arg_SOURCES})
  endif()

  if(DEFINED arg_USES)
    if(${arg_INTERFACE})
      set(_scope INTERFACE)
    else()
      set(_scope)
    endif()
    target_link_libraries(${InTarget} ${_scope} ${arg_USES})
  endif()

  if(DEFINED arg_FOLDER)
    set_target_properties(${InTarget} PROPERTIES
      FOLDER "${arg_FOLDER}")
  endif()

  get_target_property(_path ${InTarget} SOURCE_DIR)
  get_target_property(_sources ${InTarget} SOURCES)
  source_group(TREE "${_path}/${arg_PREFIX}" PREFIX "" FILES ${_sources})

  foreach(arg ${conf_flags})
    if(conf_arg_${arg})
      list(APPEND _conf_args ${arg})
    endif()
  endforeach()
  foreach(arg ${conf_single_args})
    if(DEFINED conf_arg_${arg})
      list(APPEND _conf_args ${arg} ${conf_arg_${arg}})
    endif()
  endforeach()
  foreach(arg ${conf_list_args})
    if(DEFINED conf_arg_${arg})
      list(APPEND _conf_args ${arg} ${conf_arg_${arg}})
    endif()
  endforeach()
  cml_configure_library(${InTarget} ${_conf_args})
endfunction()

# Apply standard configuration to an executable. ${InTarget} must already exist
# as a target.
#
# This is equivalent to:
#
#   cml_target_properties_defaults(${InTarget})
#   cml_target_compile_defaults(${InTarget})
#   cml_target_executable_link_defaults(${InTarget})
#
# Parameters:
#   InTarget: (required) string containing the target name
function(cml_configure_executable InTarget)
  cml_target_properties_defaults(${InTarget})
  cml_target_compile_defaults(${InTarget})
  cml_target_executable_properties_defaults(${InTarget})
  cml_target_executable_link_defaults(${InTarget})

  # Help ensure DLLs are found when debugging or when running unit tests:
  if(BUILD_SHARED_LIBS)
    if(CMAKE_GENERATOR MATCHES "Visual Studio.*")
      set_target_properties(${InTarget}
        PROPERTIES VS_DEBUGGER_ENVIRONMENT
            "PATH=$<JOIN:$<TARGET_RUNTIME_DLL_DIRS:${InTarget}>,;>"
      )
    endif()
  endif()
endfunction()

# Create an executable target and apply standard configuration.
#
# The target name is set to ${InTarget}. If a list of SOURCES is provided, it
# will be passed to target_sources(...).
#
# Parameters:
#   InTarget: (required) string containing the target name
#
# Keywords:
#   SOURCES: (optional) list of source files passed to target_sources(...)
#   USES: (optional) list of library dependencies passed to target_link_libraries(...)
#   FOLDER: (optional) path to the target in an IDE
function(cml_add_executable InTarget)
  set(flags)
  set(single_args FOLDER)
  set(list_args SOURCES USES)
  cmake_parse_arguments(arg "${flags}" "${single_args}" "${list_args}" ${ARGN})
  add_executable(${InTarget})

  if(DEFINED arg_SOURCES)
    target_sources(${InTarget} PRIVATE ${arg_SOURCES})
  endif()

  if(DEFINED arg_USES)
    target_link_libraries(${InTarget} ${arg_USES})
  endif()

  if(DEFINED arg_FOLDER)
    set_target_properties(${InTarget} PROPERTIES
      FOLDER "${arg_FOLDER}")
  endif()

  get_target_property(_path ${InTarget} SOURCE_DIR)
  get_target_property(_sources ${InTarget} SOURCES)
  source_group(TREE "${_path}" PREFIX "" FILES ${_sources})

  cml_configure_executable(${InTarget})
endfunction()

# Apply standard configuration to a CTest test executable. ${InTarget} must
# already exist as a target.
#
# The test executables will be output according to the paths set in:
#
#   CML_TEST_RUNTIME_OUTPUT_DIRECTORY_DEBUG
#   CML_TEST_RUNTIME_OUTPUT_DIRECTORY_RELEASE
#   CML_ENABLE_RELATIVE_TEST_PATHS (if TRUE, paths will be relative to CMAKE_BINARY_DIR)
#
# Parameters:
#   InTarget: (required) string containing the target name
#
# Keywords:
#   GROUP: (optional) set the test group name, helpful with "ctest -R"
function(cml_configure_test_executable InTarget)
  set(flags)
  set(single_args GROUP)
  set(list_args)
  cmake_parse_arguments(arg "${flags}" "${single_args}" "${list_args}" ${ARGN})

  set_target_properties(${InTarget} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CML_TEST_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
     RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CML_TEST_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
  )

  if(DEFINED arg_GROUP)
    set(_test_name "${arg_GROUP}::${InTarget}")
  else()
    set(_test_name "${InTarget}")
  endif()

  if(${CML_ENABLE_RELATIVE_TEST_PATHS})
    # Make the path relative with generator expressions:
    add_test(NAME ${_test_name}
      COMMAND $<PATH:RELATIVE_PATH,$<TARGET_FILE:${InTarget}>,${CMAKE_BINARY_DIR}>
      WORKING_DIRECTORY "./"
      CONFIGURATIONS Debug Release
    )

    # Use relative RPATHs in the build tree (will only take affect on platforms that
    # support it):
    set_target_properties(${_test_name} PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
  else()
    add_test(NAME ${_test_name} COMMAND ${InTarget})
  endif()

  # Make sure CTest runs correctly when building DLLs:
  # See https://stackoverflow.com/a/78003965
  if(BUILD_SHARED_LIBS)
    set_tests_properties(${_test_name}
        PROPERTIES ENVIRONMENT_MODIFICATION
          "PATH=path_list_prepend:$<JOIN:$<TARGET_RUNTIME_DLL_DIRS:${InTarget}>,\;>"
    )
  endif()
endfunction()

# Create and configure an executable target as a CMake test.
#
# This is equivalent to:
#
#  cml_add_executable(${InTarget} ...)
#  cml_configure_test_executable(${InTarget} ...)
#
# Parameters:
#   InTarget: (required) string containing the target name
#
# Keywords:
#   SOURCES: (optional) list of source files passed to target_sources(...)
#   USES: (optional) list of library dependencies passed to target_link_libraries(...)
#   FOLDER: (optional) path to the target in an IDE
#   GROUP: (optional) set the test group name, helpful with "ctest -R"
function(cml_add_test_executable InTarget)
  set(flags)
  set(single_args FOLDER GROUP)
  set(list_args USES SOURCES)
  cmake_parse_arguments(arg "${flags}" "${single_args}" "${list_args}" ${ARGN})

  set(_argn)
  if(DEFINED arg_USES)
    list(APPEND _argn USES ${arg_USES})
  endif()
  if(DEFINED arg_SOURCES)
    list(APPEND _argn SOURCES ${arg_SOURCES})
  endif()
  if(DEFINED arg_FOLDER)
    list(APPEND _argn FOLDER ${arg_FOLDER})
  endif()

  cml_add_executable(${InTarget} ${_argn})

  if(DEFINED arg_GROUP)
    set(_argn GROUP ${arg_GROUP})
  endif()
  cml_configure_test_executable(${InTarget} ${_argn})
endfunction()