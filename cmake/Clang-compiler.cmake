# Clang compiler defaults.

include_guard()
include(host-functions)

function(cml_configure_compiler)
  # The variables to export to the caller's scope:
  set(_defined)

  # Common configuration:
  list(APPEND _cml_private_cxx_features ${CML_CXX_STD})

  set(CML_PRIVATE_CXX_FEATURES ${_cml_private_cxx_features})
  list(APPEND _defined CML_PRIVATE_CXX_FEATURES)

  if(MSVC)
    # Force include paths to be set in .vcxproj, not on the compiler command line
    # to avoid IntelliSense errors:
    #
    # See also:
    #  https://discourse.cmake.org/t/how-to-override-the-cmake-include-system-flag-lang/3615
    #  https://discourse.cmake.org/t/imported-projects-dont-resolve-include-paths-in-intellisense/9185
    unset(CMAKE_INCLUDE_SYSTEM_FLAG_CXX PARENT_SCOPE)

    # Added to CML_TARGET_PROPERTIES:
    if(NOT DEFINED MSVC_RUNTIME_LIBRARY)
      if(BUILD_STATIC_RUNTIME)
        set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
      else()
        set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
      endif() 
    endif()

    list(APPEND _cml_target_properties MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY})
    list(APPEND _cml_private_cxx_options
      /permissive-   # Strict(er) standards conformance
      /W4            # Most warnings
      /FAs
    )
    list(APPEND _cml_private_exe_link_options /NOIMPLIB)

    if(NOT CML_DISABLE_SIMD)
      #>> Handle SIMD selection:
      #TODO move this to a separate function/macro?
      cml_get_host_arch(_arch)
      if(_arch STREQUAL "x64")
        if(DEFINED CML_SIMD)
          set(_cml_simd ${CML_SIMD})
        else()
          set(_cml_simd avx2)
        endif()

        set(_cml_simd_map)
        list(APPEND _cml_simd_map
          avx2 avx2
        )
      else()
        message(FATAL_ERROR "SIMD is only supported on x64 architecture for Clang-CL")
      endif()

      list(FIND _cml_simd_map ${_cml_simd} _idx)
      if(_idx EQUAL "-1")
        message(FATAL_ERROR "Unknown SIMD type ${_cml_simd}")
      else()
        math(EXPR _idx "${_idx} + 1")
        list(GET _cml_simd_map ${_idx} _cml_simd_opt)
      endif()
      list(APPEND _cml_private_cxx_options_release /clang:-m${_cml_simd_opt} /clang:-fvectorize /clang:-fassociative-math /clang:-mfma)
      #<< Handle SIMD selection:

      set(CML_SIMD ${_cml_simd})
      list(APPEND _defined CML_SIMD)
    endif()

    set(CML_TARGET_PROPERTIES ${_cml_target_properties})
    list(APPEND _defined CML_TARGET_PROPERTIES)

    set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
    list(APPEND _defined CML_PRIVATE_CXX_OPTIONS)

    set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
    list(APPEND _defined CML_PRIVATE_CXX_OPTIONS_RELEASE)

    set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})
    list(APPEND _defined CML_PRIVATE_EXE_LINK_OPTIONS)
  else()
    if(BUILD_STATIC_RUNTIME)
      list(APPEND _cml_private_cxx_options -static)
      if(WIN32)
        # Must be defined, otherwise CMake passes -D_DLL to clang on Windows:
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        list(APPEND _cml_target_properties
          MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
          )
      elseif(NOT DARWIN)
        # OS/X does not allow full static linking:
        list(APPEND _cml_private_exe_link_options -static)
      endif()
    endif()

    list(APPEND _cml_private_cxx_options
      -pedantic      # Stricter compliance
      -Wall          # All warnings
      -Wextra
    )
    list(APPEND _cml_private_cxx_options_release -O2)

    if(NOT CML_DISABLE_SIMD)
      #>> Handle SIMD selection:
      #TODO move this to a separate function/macro?

      #TODO Fix architecture detection for Clang on Darwin
      cml_get_host_arch(_arch)
      if(_arch STREQUAL "x86_64")
        if(NOT DEFINED CML_SIMD)
          set(_cml_simd avx2)
        endif()

        set(_cml_simd_map)
        list(APPEND _cml_simd_map
          avx2 avx2
        )
      else()
        message(FATAL_ERROR "SIMD is only supported on x86_64 architecture for Clang")
      endif()

      list(FIND _cml_simd_map ${_cml_simd} _idx)
      if(_idx EQUAL "-1")
        message(FATAL_ERROR "Unknown SIMD type ${_cml_simd}")
      else()
        math(EXPR _idx "${_idx} + 1")
        list(GET _cml_simd_map ${_idx} _cml_simd_opt)
      endif()
      list(APPEND _cml_private_cxx_options_release -m${_cml_simd_opt} -fvectorize -fassociative-math -mfma)
      #<< Handle SIMD selection:

      set(CML_SIMD ${_cml_simd})
      list(APPEND _defined CML_SIMD)
    endif()

    set(CML_TARGET_PROPERTIES ${_cml_target_properties})
    list(APPEND _defined CML_TARGET_PROPERTIES)

    set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
    list(APPEND _defined CML_PRIVATE_CXX_OPTIONS)

    set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
    list(APPEND _defined CML_PRIVATE_CXX_OPTIONS_RELEASE)

    set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})
    list(APPEND _defined CML_PRIVATE_EXE_LINK_OPTIONS)
  endif()

  foreach(_list IN LISTS _defined)
    set(${_list} ${${_list}} PARENT_SCOPE)
  endforeach()
endfunction()