# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Vector)
set(CML_CURRENT_TEST_GROUP "Vector")

cml_add_test(fixed_compiled_vector1)
cml_add_test(fixed_external_vector1)
cml_add_test(dynamic_external_vector1)
cml_add_test(dynamic_allocated_vector1)
cml_add_test(vector_temporary1)
cml_add_test(vector_copy1)
cml_add_test(vector_unary_node1)
cml_add_test(vector_binary_node1)
cml_add_test(vector_scalar_node1)
cml_add_test(vector_comparison1)
cml_add_test(vector_functions1)
cml_add_test(vector_dot1)
cml_add_test(perp_dot1)
cml_add_test(cross1)
cml_add_test(triple_product1)
cml_add_test(subvector1)
cml_add_test(outer_product1)
cml_add_test(vector_hadamard_product1)