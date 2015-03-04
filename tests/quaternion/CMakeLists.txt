# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Quaternion)
set(CML_CURRENT_TEST_GROUP "Quaternion")

ADD_CML_TEST(fixed_compiled_quaternion1)
#ADD_CML_TEST(fixed_external_vector1)
#ADD_CML_TEST(dynamic_external_vector1)
#ADD_CML_TEST(dynamic_allocated_vector1)
#ADD_CML_TEST(vector_copy1)
ADD_CML_TEST(quaternion_unary_node1)
#ADD_CML_TEST(vector_binary_node1)
#ADD_CML_TEST(vector_scalar_node1)
#ADD_CML_TEST(vector_comparison1)
ADD_CML_TEST(quaternion_functions1)
#ADD_CML_TEST(dot1)
#ADD_CML_TEST(perp_dot1)
#ADD_CML_TEST(cross1)
#ADD_CML_TEST(triple_product1)
ADD_CML_TEST(imaginary1)
#ADD_CML_TEST(outer_product1)
#ADD_CML_TEST(vector_hadamard_product1)

# --------------------------------------------------------------------------
# vim:ft=cmake
