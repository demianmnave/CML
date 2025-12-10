# MSVC compiler defaults.

include_guard()
include(host-functions)

function(cml_configure_compiler)

  # The variables to export to the caller's scope:
  set(_defined)

  # Added to CML_TARGET_PROPERTIES:
  if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
    if(BUILD_STATIC_RUNTIME)
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif() 
  endif()

  list(APPEND _cml_target_properties MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY})
  list(APPEND _cml_private_cxx_features ${CML_CXX_STD})
  list(APPEND _cml_private_cxx_options
    /permissive-   # Strict(er) standards conformance
    /GL            # Link-time code generation
    /W4            # Most warnings
    /diagnostics:caret
    /MP
    /EHsc
    /bigobj
  )
  set(_cml_private_exe_link_options /NOIMPLIB /NOEXP /LTCG)

  # Options to enable assembly output for inspection:
  list(APPEND CML_ASSEMBLY_OPTIONS /FAs)
  list(APPEND _defined CML_ASSEMBLY_OPTIONS)

  #TODO move this to a separate function/macro?
  if(NOT CML_DISABLE_SIMD)
    #>> Handle SIMD selection:
    cml_get_host_arch(_arch)
    if(_arch STREQUAL "x64")
      if(DEFINED CML_SIMD)
        set(_cml_simd ${CML_SIMD})
      else()
        set(_cml_simd avx2)
      endif()

      set(_cml_simd_map)
      list(APPEND _cml_simd_map
        avx2 AVX2
      )
    else()
      message(FATAL_ERROR "SIMD is only supported on x64 architecture for MSVC")
    endif()

    list(FIND _cml_simd_map ${_cml_simd} _idx)
    if(_idx EQUAL "-1")
      message(FATAL_ERROR "Unknown SIMD type ${_cml_simd}")
    else()
      math(EXPR _idx "${_idx} + 1")
      list(GET _cml_simd_map ${_idx} _cml_simd_opt)
    endif()
    list(APPEND _cml_private_cxx_options_release /arch:${_cml_simd_opt})
    #<< Handle SIMD selection:

    set(CML_SIMD ${_cml_simd})
    list(APPEND _defined CML_SIMD)
  endif()

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

  foreach(_list IN LISTS _defined)
    set(${_list} ${${_list}} PARENT_SCOPE)
  endforeach()
endfunction()