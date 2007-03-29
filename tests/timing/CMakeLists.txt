# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

PROJECT(CMLTimingTests)

# Setup test groups:

# Hand-coded C vector tests:
SET(C_VEC_TESTS
  vector_c1
  extvec_c1
  vector_c2
  )

# Fixed-vector expression template tests:
SET(FIXED_VEC_TESTS
  fixed_vec_et1
  fixed_vec_et2
  #fixed_vec_exmat1
  #fixed_vec_ltl1
  )

# Dynamic-vector expression template tests:
SET(DYNAMIC_VEC_TESTS
  dynamic_vec_et1
  dynamic_vec_et2
  )

# External-vector expression template tests:
SET(EXTERNAL_VEC_TESTS
  external_vec_et1
  )

# Hand-coded C matrix tests:
SET(C_MAT_TESTS
  matrix_c1
  matrix_c2
  )

# Fixed-matrix expression template tests:
SET(FIXED_MAT_TESTS
  fixed_mat_et1
  fixed_mat_et2
  )

# Dynamic-matrix expression template tests:
SET(DYNAMIC_MAT_TESTS
  dynamic_mat_et1
  )

# External-matrix expression template tests:
SET(EXTERNAL_MAT_TESTS
  external_mat_et1
  )

# Hand-coded C matrix-vector tests:
SET(C_MATVEC_TESTS
  matvec_c1
  )

# Fixed-matrix/vector expression template tests:
SET(FIXED_MATVEC_TESTS
  fixed_matvec_et1
  )

# Dynamic-matrix/vector expression template tests:
SET(DYNAMIC_MATVEC_TESTS
  )

# External-matrix/vector expression template tests:
SET(EXTERNAL_MATVEC_TESTS
  )

# All of the tests:
SET(TimingTests
  ${C_VEC_TESTS}
  ${FIXED_VEC_TESTS}
  ${DYNAMIC_VEC_TESTS}
  ${EXTERNAL_VEC_TESTS}
  ${C_MAT_TESTS}
  ${FIXED_MAT_TESTS}
  ${DYNAMIC_MAT_TESTS}
  ${EXTERNAL_MAT_TESTS}
  ${C_MATVEC_TESTS}
  ${FIXED_MATVEC_TESTS}
  ${DYNAMIC_MATVEC_TESTS}
  ${EXTERNAL_MATVEC_TESTS}
  )

FOREACH(Test ${TimingTests})
  ADD_EXECUTABLE(${Test} ${Test}.cpp)
ENDFOREACH(Test)

# Copy test data into the output directory:
SET(TimingData vals.txt mvals.txt)
FOREACH(Data ${TimingData})
  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/${Data}
    ${CMAKE_CURRENT_BINARY_DIR}
    COPYONLY)
ENDFOREACH(Data)

# --------------------------------------------------------------------------
# vim:ft=cmake
