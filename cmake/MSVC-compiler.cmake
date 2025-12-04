# MSVC compiler defaults.

include_guard()
include(host-functions)

function(cml_configure_compiler)
  # Added to CML_TARGET_PROPERTIES:
  if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
    if(BUILD_STATIC_RUNTIME)
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif() 
  endif()

  set(_cml_target_properties MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY})
  set(_cml_private_cxx_features ${CML_CXX_STD})
  set(_cml_private_cxx_options
    /permissive-   # Strict(er) standards conformance
    /GL            # Link-time code generation
    /W4            # Most warnings
    /diagnostics:caret
    /MP
    /EHsc
    /bigobj
    /FAs
  )
  set(_cml_private_exe_link_options /NOIMPLIB /NOEXP /LTCG)


  #>> Handle SIMD selection:
  #TODO move this to a separate function/macro?
  if(DEFINED CML_SIMD)
    set(_cml_simd ${CML_SIMD})
  else()
    cml_get_host_arch(_arch)
    if(${_arch} STREQUAL "x64")
      set(_cml_simd "sse4.2")
    endif()
  endif()

  # Note that the compiler default is "SSE2" for MSVC-x64, and it enables SSE4.2:
  set(_cml_simd_map)
  list(APPEND _cml_simd_map
    "sse4.2" "SSE2"
    "avx2" "AVX2"
  )

  list(FIND _cml_simd_map ${_cml_simd} _idx)
  if(_idx EQUAL "-1")
    message(FATAL_ERROR "Unknown SIMD type ${_cml_simd}")
  else()
    math(EXPR _idx "${_idx} + 1")
    list(GET _cml_simd_map ${_idx} _cml_simd_opt)
  endif()
  list(APPEND _cml_private_cxx_options_release "/arch:${_cml_simd_opt}")
  #<< Handle SIMD selection:


  # The variables to export to the caller's scope:
  set(_defined)

  set(CML_TARGET_PROPERTIES ${_cml_target_properties})
  list(APPEND _defined CML_TARGET_PROPERTIES)

  set(CML_PRIVATE_CXX_FEATURES ${_cml_private_cxx_features})
  list(APPEND _defined CML_PRIVATE_CXX_FEATURES)

  set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
  list(APPEND _defined CML_PRIVATE_CXX_OPTIONS)

  set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
  list(APPEND _defined CML_PRIVATE_CXX_OPTIONS_RELEASE)

  set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})
  list(APPEND _defined CML_PRIVATE_EXE_LINK_OPTIONS)

  set(CML_SIMD ${_cml_simd})
  list(APPEND _defined CML_SIMD)

  foreach(_list IN LISTS _defined)
    set(${_list} ${${_list}} PARENT_SCOPE)
  endforeach()
endfunction()