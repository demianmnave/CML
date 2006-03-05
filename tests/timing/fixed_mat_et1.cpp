/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#define CML_ENABLE_MATRIX_BRACES // for operator[][] to load/print a matrix

#include <iostream>
#include <cml/fixed.h>
#include <cml/matrix.h>

using namespace cml::matrix_ops;

/* For convenience: */
using std::cerr;
using std::endl;

using cml::fixed;
typedef cml::matrix< double, fixed<4,4> > matrix_d44;
#define MATINIT(_m_) _m_

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

inline void mult(const matrix_d44& A, const matrix_d44& B, matrix_d44& res)
{
    int row, col, k;
#if 0
    for(row = 0; row < 4; ++row) {
	for(col = 0; col < 4; ++col) {
	    double sum = A[row][0]*B[0][col];
	    for(k = 1; k < 4; ++k) {
		sum += A[row][k]*B[k][col];
	    }
	    res[row][col] = sum;
	}
    }
#else
    for(row = 0; row < 4; ++row) {
	for(col = 0; col < 4; ++col) {
	    double sum = A(row,0)*B(0,col);
	    for(k = 1; k < 4; ++k) {
		sum += A(row,k)*B(k,col);
	    }
	    res(row,col) = sum;
	}
    }
#endif
}

inline matrix_d44 operator*(const matrix_d44& A, const matrix_d44& B) {
    matrix_d44 nrv; mult(A,B,nrv); return nrv;
}

#include "print_matrix.cpp"
#include "matrix_algebra1.cpp"
#include "matrix_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
