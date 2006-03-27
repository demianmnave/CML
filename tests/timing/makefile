# -*- Makefile -*- --------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

CML_ROOT=../..
CML_TEST_ROOT=../
include $(CML_TEST_ROOT)/makeconf

C_VEC_TEST_SRC		= vector_c1.cpp extvec_c1.cpp vector_c2.cpp
FIXED_VEC_TEST_SRC	= fixed_vec_et1.cpp fixed_vec_et2.cpp #fixed_vec_exmat1.cpp fixed_vec_ltl1.cpp
DYNAMIC_VEC_TEST_SRC	= dynamic_vec_et1.cpp dynamic_vec_et2.cpp
EXTERNAL_VEC_TEST_SRC	= external_vec_et1.cpp

C_MAT_TEST_SRC		= matrix_c1.cpp matrix_c2.cpp
FIXED_MAT_TEST_SRC	= fixed_mat_et1.cpp fixed_mat_et2.cpp
DYNAMIC_MAT_TEST_SRC	= dynamic_mat_et1.cpp
EXTERNAL_MAT_TEST_SRC	= external_mat_et1.cpp

C_MATVEC_TEST_SRC	= matvec_c1.cpp
FIXED_MATVEC_TEST_SRC	= fixed_matvec_et1.cpp
DYNAMIC_MATVEC_TEST_SRC	=
EXTERNAL_MATVEC_TEST_SRC=

ALL_SRC=$(C_VEC_TEST_SRC) \
	$(FIXED_VEC_TEST_SRC) \
	$(DYNAMIC_VEC_TEST_SRC) \
	$(EXTERNAL_VEC_TEST_SRC) \
	$(C_MAT_TEST_SRC) \
	$(FIXED_MAT_TEST_SRC) \
	$(DYNAMIC_MAT_TEST_SRC) \
	$(EXTERNAL_MAT_TEST_SRC) \
	$(C_MATVEC_TEST_SRC) \
	$(FIXED_MATVEC_TEST_SRC) \
	$(DYNAMIC_MATVEC_TEST_SRC) \
	$(EXTERNAL_MATVEC_TEST_SRC)

C_VEC_TESTS		= vector_c1$(exe) extvec_c1$(exe) vector_c2$(exe)
FIXED_VEC_TESTS		= fixed_vec_et1$(exe) fixed_vec_et2$(exe) #fixed_vec_exmat1$(exe) fixed_vec_ltl1$(exe)
DYNAMIC_VEC_TESTS	= dynamic_vec_et1$(exe) dynamic_vec_et2$(exe)
EXTERNAL_VEC_TESTS	= external_vec_et1$(exe)

C_MAT_TESTS		= matrix_c1$(exe) matrix_c2$(exe)
FIXED_MAT_TESTS		= fixed_mat_et1$(exe) fixed_mat_et2$(exe)
DYNAMIC_MAT_TESTS	= dynamic_mat_et1$(exe)
EXTERNAL_MAT_TESTS	= external_mat_et1$(exe)

C_MATVEC_TESTS		= matvec_c1$(exe)
FIXED_MATVEC_TESTS	= fixed_matvec_et1$(exe)
DYNAMIC_MATVEC_TESTS	=
EXTERNAL_MATVEC_TESTS	=

ALL=	$(C_VEC_TESTS) \
	$(FIXED_VEC_TESTS) \
	$(DYNAMIC_VEC_TESTS) \
	$(EXTERNAL_VEC_TESTS) \
	$(C_MAT_TESTS) \
	$(FIXED_MAT_TESTS) \
	$(DYNAMIC_MAT_TESTS) \
	$(EXTERNAL_MAT_TESTS) \
	$(C_MATVEC_TESTS) \
	$(FIXED_MATVEC_TESTS) \
	$(DYNAMIC_MATVEC_TESTS) \
	$(EXTERNAL_MATVEC_TESTS)
	
include $(CML_TEST_ROOT)/makepost

fixed_mat_et1.s: fixed_mat_et1.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -S $^

matrix_c1.s: matrix_c1.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -S $^

# --------------------------------------------------------------------------
# vim:ft=make
