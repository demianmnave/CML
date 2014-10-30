# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Vector)
set(CML_CURRENT_TEST_GROUP "Vector")

ADD_CML_TEST(fixed_vector1)
ADD_CML_TEST(fixed_external_vector1)
ADD_CML_TEST(dynamic_external_vector1)
ADD_CML_TEST(dynamic_vector1)
ADD_CML_TEST(unary_node1)
ADD_CML_TEST(binary_node1)
ADD_CML_TEST(scalar_node1)

# --------------------------------------------------------------------------
# vim:ft=cmake
