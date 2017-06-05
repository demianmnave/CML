# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Search for Boost.Test:
if(CML_BUILD_TESTING)

  if(NOT DEFINED BOOST_ROOT)
    set(BOOST_ROOT "" CACHE PATH "Path containing Boost")
  else()
    if("${BOOST_ROOT}" STREQUAL "")
      message(FATAL_ERROR "Please set BOOST_ROOT before configuring again")
    endif()
  endif()

  set(Boost_USE_STATIC_LIBS TRUE)
  set(Boost_USE_STATIC_RUNTIME TRUE)

  # Find Boost.UTF:
  find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()

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
  target_compile_definitions(${ExecName} PRIVATE -DBOOST_ALL_NO_LIB)
  target_link_libraries(${ExecName} Boost::unit_test_framework)

  # Setup the test:
  add_test(NAME ${TestName} COMMAND ${ExecName} --log_level=warning)
endmacro()

# --------------------------------------------------------------------------
# vim:ft=cmake
