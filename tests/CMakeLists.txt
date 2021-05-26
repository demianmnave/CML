# --------------------------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

include(target-functions)
function(cml_add_test _name)
  cml_add_test_executable(${_name}
   SOURCES ${_name}.cpp
   USES cml cml_test_main
   FOLDER "cml-tests/${CML_TEST_GROUP}")
endfunction()

add_subdirectory(main)
add_subdirectory(common)
add_subdirectory(storage)
add_subdirectory(scalar)
add_subdirectory(vector)
add_subdirectory(matrix)
add_subdirectory(quaternion)
add_subdirectory(expr)
add_subdirectory(mathlib)
add_subdirectory(util)

#if(CML_BUILD_TIMING)
  add_subdirectory(timing)
#endif()