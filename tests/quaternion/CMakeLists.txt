# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Quaternion)
set(CML_CURRENT_TEST_GROUP "Quaternion")

ADD_CML_TEST(fixed_compiled_quaternion1)
#ADD_CML_TEST(quaternion_copy1)  ## Not implemented yet.
ADD_CML_TEST(quaternion_unary_node1)
ADD_CML_TEST(quaternion_binary_node1)
ADD_CML_TEST(quaternion_scalar_node1)
ADD_CML_TEST(quaternion_comparison1)
ADD_CML_TEST(quaternion_functions1)
ADD_CML_TEST(quaternion_product1)
ADD_CML_TEST(quaternion_dot1)
ADD_CML_TEST(imaginary1)
ADD_CML_TEST(conjugate1)
ADD_CML_TEST(inverse1)

# --------------------------------------------------------------------------
# vim:ft=cmake
