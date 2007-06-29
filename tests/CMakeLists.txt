# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

PROJECT(CMLFunctionalityTests)

# Default definitions (should *really* be configured into a global
# "config.h" file to help satisfy the one definition rule [ODR]):
ADD_DEFINITIONS(
  #  -DCML_NO_DEFAULT_EXPR_TRAITS
  -DCML_VECTOR_UNROLL_LIMIT=25
  -DCML_VECTOR_DOT_UNROLL_LIMIT=25
  -DCML_ALWAYS_PROMOTE_TO_DEFAULT_LAYOUT
  -UCML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT
  -UCML_CHECK_VECTOR_EXPR_SIZES
  -UCML_AUTOMATIC_MATRIX_RESIZE_ON_ASSIGNMENT
  -UCML_CHECK_MATRIX_EXPR_SIZES
  )

# Setup the functionality tests:
SET(FunctionTests
  vector_et1
  matrix_et1
  external_assignment

  integer_vectors
  )
FOREACH(Test ${FunctionTests})
  ADD_EXECUTABLE(${Test} ${Test}.cpp)
ENDFOREACH(Test)

# Setup the timing tests:
ADD_SUBDIRECTORY(timing)

# --------------------------------------------------------------------------
# vim:ft=cmake
