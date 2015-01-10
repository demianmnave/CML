# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Matrix)
set(CML_CURRENT_TEST_GROUP "Matrix")

ADD_CML_TEST(matrix_promotion1)
ADD_CML_TEST(fixed_compiled_matrix1)
ADD_CML_TEST(fixed_external_matrix1)
ADD_CML_TEST(dynamic_external_matrix1)
ADD_CML_TEST(dynamic_allocated_matrix1)
ADD_CML_TEST(matrix_scalar_node1)
ADD_CML_TEST(matrix_unary_node1)
ADD_CML_TEST(matrix_binary_node1)
ADD_CML_TEST(matrix_functions1)
ADD_CML_TEST(matrix_matrix_product1)
ADD_CML_TEST(matrix_vector_product1)
ADD_CML_TEST(matrix_transpose1)
ADD_CML_TEST(matrix_inverse1)
ADD_CML_TEST(lu1)
ADD_CML_TEST(determinant1)

# --------------------------------------------------------------------------
# vim:ft=cmake
