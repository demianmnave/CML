# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Mathlib)
set(CML_CURRENT_TEST_GROUP "Mathlib")

cml_add_test(vector_angle1)
cml_add_test(vector_transform1)
cml_add_test(vector_rotation1)
cml_add_test(vector_misc1)
    
cml_add_test(matrix_generators1)
cml_add_test(matrix_basis1)
cml_add_test(matrix_translation1)
cml_add_test(matrix_scale1)
cml_add_test(matrix_invert1)
cml_add_test(matrix_rotation1)
cml_add_test(matrix_projection1)
cml_add_test(matrix_transform1)
    
cml_add_test(quaternion_basis1)
cml_add_test(quaternion_rotation1)
    
cml_add_test(coordinate_conversion1)
cml_add_test(random_unit1)
cml_add_test(frustum1)