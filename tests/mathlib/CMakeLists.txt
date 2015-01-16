# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Mathlib)
set(CML_CURRENT_TEST_GROUP "Mathlib")

ADD_CML_TEST(random_unit1)
ADD_CML_TEST(vector_angle1)
ADD_CML_TEST(vector_misc1)
ADD_CML_TEST(matrix_basis1)
ADD_CML_TEST(matrix_translation1)
ADD_CML_TEST(matrix_invert1)

# --------------------------------------------------------------------------
# vim:ft=cmake
