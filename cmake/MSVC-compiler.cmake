# Clang compiler defaults.

include_guard()
include(host-functions)

message(STATUS "${PROJECT_NAME}: configuring for ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")

if(MSVC)
  # Added to CML_TARGET_PROPERTIES:
  if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
    if(BUILD_STATIC_RUNTIME)
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif() 
  endif()

  # Enforce the default for all projects:
  if(NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
    set(CMAKE_MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY})
  endif()

  set(_cml_target_properties
    MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY}
  )

  set(_cml_public_cxx_definitions
    _UNICODE
    UNICODE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _WIN32_WINNT=0x0A00
  )

  set(_cml_private_cxx_options
    /permissive-   # Strict(er) standards conformance
    /GL            # Link-time code generation
  )

  if(PROJECT_IS_TOP_LEVEL)
    list(APPEND _cml_private_cxx_options
      /W4          # Most warnings
      /diagnostics:caret
      /MP
      /EHsc
      /bigobj
      /utf-8
    )

    cml_get_host_arch(_arch)
    if(${_arch} STREQUAL "x64")
      list(APPEND _cml_private_cxx_options /arch:AVX2)
    endif()
  endif()

  set(_cml_private_exe_link_options /NOIMPLIB /NOEXP /LTCG)
endif()

set(CML_TARGET_PROPERTIES ${_cml_target_properties})
set(CML_PUBLIC_CXX_COMPILE_FEATURES ${CML_CXX_STD})
set(CML_PUBLIC_CXX_DEFINITIONS ${_cml_public_cxx_definitions})
set(CML_PRIVATE_CXX_DEFINITIONS ${_cml_private_cxx_definitions})
set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
set(CML_PRIVATE_CXX_OPTIONS_DEBUG ${_cml_private_cxx_options_debug})
set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})