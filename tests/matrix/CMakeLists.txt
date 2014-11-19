# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Matrix)
set(CML_CURRENT_TEST_GROUP "Matrix")

ADD_CML_TEST(fixed_matrix1)
ADD_CML_TEST(fixed_external_matrix1)
ADD_CML_TEST(dynamic_external_matrix1)
ADD_CML_TEST(dynamic_matrix1)
ADD_CML_TEST(matrix_scalar_node1)
ADD_CML_TEST(matrix_unary_node1)
ADD_CML_TEST(matrix_binary_node1)
ADD_CML_TEST(matrix_functions1)

# Mark tests that are expected to fail on MSVC:
if(MSVC)
  set_tests_properties(
    CML:Matrix:matrix_scalar_node1_test
    PROPERTIES WILL_FAIL TRUE
    )
endif()

# --------------------------------------------------------------------------
# vim:ft=cmake
