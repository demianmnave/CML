/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>

/* For convenience: */
using std::cerr;
using std::endl;

typedef double matrix_d44[4][4];
#define MATINIT(_m_) _m_

std::ostream&
operator<<(std::ostream& os, const matrix_d44& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < 4; ++i) {
        os << "  [";
        for(size_t j = 0; j < 4; ++j) {
            os << " " << m[i][j];
        }
        os << " ]" << endl;
    }
    os << "]";
    return os;
}

inline void add(const matrix_d44 A, const matrix_d44 B, matrix_d44 res)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
            res[row][col] = A[row][col]+B[row][col];
	}
    }
}

inline void mult(const matrix_d44 A, const matrix_d44 B, matrix_d44 res)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = A[row][0]*B[0][col];
	    for(int k = 1; k < 4; ++k) {
		sum += A[row][k]*B[k][col];
	    }
	    res[row][col] = sum;
	}
    }
}

/* The args should *not* be references: */
inline void timed1(
        matrix_d44 m,
        const matrix_d44 m1,
        const matrix_d44 m2,
        const matrix_d44 m3,
        size_t n_iter
        )
{
    matrix_d44 tmp, tmp2; 
    for(int i = 0; i < n_iter; ++i) {
        /* m = m1*m2*m3 -> tmp = m1*m2, m = tmp*m3 */
        //mult(m1,m2,tmp); mult(tmp,m3,m);

        /* m = m1*m2*m3*m3 -> tmp = m1*m2, tmp2 = m3*m3, m = tmp*tmp2 */
        //mult(m1,m2,tmp); mult(m3,m3,tmp2); mult(tmp,tmp2,m);

        //add(m,m1,m);
        //add(m,m2,m);

        for(int row = 0; row < 4; ++row) {
            for(int col = 0; col < 4; ++col) {
                m[row][col] = m[row][col] + m1[row][col] + m2[row][col]
                    + m3[row][col] + m2[row][col];
            }
        }
    }
}

#include "matrix_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
