# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

macro(MAKE_CML_TEST_GROUP _Group)
  set(test_group "CML-Projects/Tests")
  if(DEFINED CML_CURRENT_TEST_GROUP)
    set(test_group "${test_group}/${CML_CURRENT_TEST_GROUP}")

    # Make test_group a proper FOLDER name if it has ":" in it:
    string(REPLACE ":" "/" test_group ${test_group})
  endif()
  set(${_Group} ${test_group})
endmacro()

# Macro to add a multi-file test to the build.  The executable name and
# test title will be set to ${_Name}_test, while the source files are taken
# from the remaining passed-in arguments:
macro(ADD_CML_TEST
    _Name			# The test basename, e.g. my -> my_test
    )

  # Define the executable name:
  set(ExecName "${_Name}_test")

  # Define the test group:
  MAKE_CML_TEST_GROUP(test_group)

  # Define the test name:
  if(DEFINED CML_CURRENT_TEST_GROUP)
    set(TestName "CML:${CML_CURRENT_TEST_GROUP}:${_Name}_test")
  else()
    set(TestName "CML:${_Name}_test")
  endif()

  # Setup the build target:
  add_executable(${ExecName} ${_Name}.cpp)
  set_target_properties(${ExecName} PROPERTIES FOLDER "${test_group}")

  # Setup the test:
  add_test(NAME ${TestName} COMMAND ${ExecName})
endmacro()

# --------------------------------------------------------------------------
# vim:ft=cmake
