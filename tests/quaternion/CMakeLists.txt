# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Quaternion)
set(CML_CURRENT_TEST_GROUP "Quaternion")

cml_add_test(fixed_compiled_quaternion1)
#ADD_CML_TEST(quaternion_copy1)  ## Not implemented yet.
cml_add_test(quaternion_unary_node1)
cml_add_test(quaternion_binary_node1)
cml_add_test(quaternion_scalar_node1)
cml_add_test(quaternion_comparison1)
cml_add_test(quaternion_functions1)
cml_add_test(quaternion_product1)
cml_add_test(quaternion_dot1)
cml_add_test(imaginary1)
cml_add_test(conjugate1)
cml_add_test(inverse1)