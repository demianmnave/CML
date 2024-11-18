# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

# Function to add a single-file test to the build, using ${_name}.cpp as the
# test source.
function(cml_add_test _name)
  # Define the executable name:
  set(ExecName "${_name}")

  # Define the test name:
  if(DEFINED CML_TEST_GROUP)
    set(TestName "CML:${CML_TEST_GROUP}:${_name}")
  else()
    message(FATAL_ERROR "CML_TEST_GROUP must be defined")
  endif()

  # Setup the build target:
  add_executable(${ExecName} ${_name}.cpp)

  # MSVC-only C++ compiler options:
  if(MSVC)
    set(_msvc_common_options
      /permissive-
      /MP
      /EHsc
      /W4 # Enable strict warnings.
    )

    set(_cxx_is_msvc $<CXX_COMPILER_ID:MSVC>)
    set(_msvc_compile_options
      /Zc:inline
      /Zc:strictStrings
      /Zc:__cplusplus
      /Zc:lambda
      /Zc:rvalueCast
      /diagnostics:caret
      /WL
    )

    set(_msvc_link_options
      /NOIMPLIB
      /NOEXP
    )

    target_compile_options(${ExecName}
      PRIVATE
       ${_msvc_common_options}
       $<${_cxx_is_msvc}:${_msvc_compile_options}>
    )

    target_compile_features(${ExecName}
      PRIVATE
      cxx_std_17
    )

    target_link_options(${ExecName}
      PRIVATE $<${_cxx_is_msvc}:${_msvc_link_options}>
    )

    set_target_properties(${ExecName} PROPERTIES
      FOLDER "cml-tests/${CML_TEST_GROUP}"
      MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY}
    )

    get_target_property(_path ${_name} SOURCE_DIR)
    get_target_property(_sources ${_name} SOURCES)
    source_group(TREE "${_path}" FILES ${_sources})
  endif()

  target_link_libraries(${ExecName} cml cml_test_main)

  # Setup the test:
  add_test(NAME ${TestName} COMMAND ${ExecName})
endfunction()

add_subdirectory(main)
add_subdirectory(common)
add_subdirectory(storage)
add_subdirectory(vector)
add_subdirectory(matrix)
add_subdirectory(quaternion)
add_subdirectory(mathlib)
add_subdirectory(util)