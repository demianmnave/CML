# GCC compiler defaults.

include_guard()
include(host-functions)

message(STATUS "${PROJECT_NAME}: configuring for ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

if(BUILD_STATIC_RUNTIME)
  set(_cml_private_cxx_options -static)
  if(NOT DARWIN)
    # OS/X does not allow full static linking:
    set(_cml_private_exe_link_options -static)
  endif()
endif()

list(APPEND _cml_private_cxx_options
  -pedantic      # Stricter compliance
)
if(PROJECT_IS_TOP_LEVEL)
  list(APPEND _cml_private_cxx_options
    -Wall        # All warnings
    -Wextra
  )

  cml_get_host_arch(_arch)
  if(${_arch} STREQUAL "x64")
    list(APPEND _cml_private_cxx_options -march=native -mavx -fvectorize -fassociative-math)
  endif()
endif()

list(APPEND _cml_private_cxx_options_debug -g)
list(APPEND _cml_private_cxx_options_release -O2)
list(APPEND _cml_private_cxx_definitions -DNDEBUG)

set(CML_TARGET_PROPERTIES ${_cml_target_properties})
set(CML_PUBLIC_CXX_COMPILE_FEATURES ${CML_CXX_STD})
set(CML_PUBLIC_CXX_DEFINITIONS ${_cml_public_cxx_definitions})
set(CML_PRIVATE_CXX_DEFINITIONS ${_cml_private_cxx_definitions})
set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
set(CML_PRIVATE_CXX_OPTIONS_DEBUG ${_cml_private_cxx_options_debug})
set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})