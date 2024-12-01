# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

function(cml_default_compile_options _name)
  # MSVC-only C++ compiler options:
  if(MSVC)
    set(_cxx_is_msvc $<CXX_COMPILER_ID:MSVC>)

    set(_msvc_common_options
      /permissive-
      /EHsc
      /W4 # Enable strict warnings.
    )

    set(_msvc_compile_options
      /Zc:inline
      /Zc:strictStrings
      /Zc:__cplusplus
      /Zc:lambda
      /Zc:rvalueCast
      /diagnostics:caret
      /WL
      /MP
      /arch:AVX2
    )

    target_compile_options(${_name}
      PRIVATE
      ${_msvc_common_options}
      $<${_cxx_is_msvc}:${_msvc_compile_options}>
    )

    target_compile_features(${_name}
      PRIVATE
      cxx_std_17
    )
  endif()
endfunction()

# Function to add a single-file executable to the build, using ${_name}.cpp as
# the test source.
function(cml_add_executable _name)
  add_executable(${_name} ${ARGN})
  cml_default_compile_options(${_name})

  if(MSVC)
    set(_cxx_is_msvc $<CXX_COMPILER_ID:MSVC>)

    set(_msvc_link_options
      /NOIMPLIB
      /NOEXP
    )

    target_link_options(${_name}
      PRIVATE $<${_cxx_is_msvc}:${_msvc_link_options}>
    )
  endif()

  get_target_property(_path ${_name} SOURCE_DIR)
  get_target_property(_sources ${_name} SOURCES)
  source_group(TREE "${_path}" FILES ${_sources})
endfunction()

# Function to add a single-file test to the build, using ${_name}.cpp as the
# test source.
function(cml_add_test _name)
  if(DEFINED CML_TEST_GROUP)
    set(TestName "CML:${CML_TEST_GROUP}:${_name}")
  else()
    message(FATAL_ERROR "CML_TEST_GROUP must be defined")
  endif()

  cml_add_executable(${_name} ${_name}.cpp ${ARGN})

  add_test(NAME ${TestName} COMMAND ${_name})
  set_target_properties(${_name} PROPERTIES
    FOLDER "cml-tests/${CML_TEST_GROUP}"
  )
  target_link_libraries(${_name} cml cml_test_main)
endfunction()

add_subdirectory(main)
add_subdirectory(common)
add_subdirectory(storage)
add_subdirectory(vector)
add_subdirectory(matrix)
add_subdirectory(quaternion)
add_subdirectory(mathlib)
add_subdirectory(util)

#if(BUILD_TIMING)
add_subdirectory(timing)
#endif()