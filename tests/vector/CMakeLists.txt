# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Vector)
set(CML_CURRENT_TEST_GROUP "Vector")

ADD_CML_TEST(fixed_vector1)
ADD_CML_TEST(fixed_external_vector1)
ADD_CML_TEST(dynamic_external_vector1)
ADD_CML_TEST(dynamic_vector1)
ADD_CML_TEST(vector_copy1)
ADD_CML_TEST(vector_unary_node1)
ADD_CML_TEST(vector_binary_node1)
ADD_CML_TEST(vector_scalar_node1)
ADD_CML_TEST(vector_comparison1)
ADD_CML_TEST(vector_functions1)
ADD_CML_TEST(dot1)
ADD_CML_TEST(perp_dot1)
ADD_CML_TEST(cross1)
ADD_CML_TEST(triple_product1)
ADD_CML_TEST(subvector1)

# Mark tests that are expected to fail on MSVC:
if(MSVC)
  set_tests_properties(
    CML:Vector:vector_scalar_node1_test
    PROPERTIES WILL_FAIL TRUE
    )
endif()

# --------------------------------------------------------------------------
# vim:ft=cmake
