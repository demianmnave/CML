/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#define CML_ENABLE_MATRIX_BRACES // for operator[][] to load/print a matrix

#include <iostream>
#include <cml/cml.h>
using namespace cml;

/* For convenience: */
using std::cerr;
using std::endl;

typedef matrix< double, external<4,4>, row_major > matrix_d44;
#define MATINIT(_m_) _m_(&c_m[c_i++][0][0])

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

#include "print_matrix.cpp"
#include "matrix_algebra1.cpp"
#include "matrix_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
