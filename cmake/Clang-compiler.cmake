# Clang compiler defaults.

include_guard()

message(STATUS "${PROJECT_NAME}: configuring for ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")

if(MSVC)
  # Force include paths to be set in .vcxproj, not on the compiler command line
  # to avoid IntelliSense errors:
  #
  # See also:
  #  https://discourse.cmake.org/t/how-to-override-the-cmake-include-system-flag-lang/3615
  #  https://discourse.cmake.org/t/imported-projects-dont-resolve-include-paths-in-intellisense/9185
  unset(CMAKE_INCLUDE_SYSTEM_FLAG_CXX)

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
  )
  if(PROJECT_IS_TOP_LEVEL)
    list(APPEND _cml_private_cxx_options
      /W4          # Most warnings
      /MP
      /arch:AVX
    )
  endif()

  set(_cml_private_exe_link_options /NOIMPLIB)
else()
  if(BUILD_STATIC_RUNTIME)
    set(_cml_private_cxx_options -static)
    if(WIN32)
      # Must be defined, otherwise CMake passes -D_DLL to clang on Windows:
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
      set(_cml_target_properties
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        )
    elseif(NOT DARWIN)
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
  endif()

  list(APPEND _cml_private_cxx_options_release -O2)
endif()

set(CML_TARGET_PROPERTIES ${_cml_target_properties})
set(CML_PUBLIC_CXX_COMPILE_FEATURES ${CML_CXX_STD})
set(CML_PUBLIC_CXX_DEFINITIONS ${_cml_public_cxx_definitions})
set(CML_PRIVATE_CXX_DEFINITIONS ${_cml_private_cxx_definitions})
set(CML_PRIVATE_CXX_OPTIONS ${_cml_private_cxx_options})
set(CML_PRIVATE_CXX_OPTIONS_DEBUG ${_cml_private_cxx_options_debug})
set(CML_PRIVATE_CXX_OPTIONS_RELEASE ${_cml_private_cxx_options_release})
set(CML_PRIVATE_EXE_LINK_OPTIONS ${_cml_private_exe_link_options})