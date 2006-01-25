/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  XXX The tests should use a testing rig, but this can wait for now.
 */

#ifdef C_TIMED
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

typedef double Mat[3][3];
inline void mult(const Mat& A, const Mat& B, Mat& res)
{
    int row, col, k;
    for(row = 0; row < 3; ++row) {
	for(col = 0; col < 3; ++col) {
	    double sum = A[row][0]*B[0][col];
	    for(k = 1; k < 3; ++k) {
		sum += A[row][k]*B[k][col];
	    }
	    res[row][col] = sum;
	}
    }
}

inline void c_timed()
{
    struct timeval t_start, t_end;
    gettimeofday(&t_start,0);

    double m3[3][3];
    {
        double m1[3][3], m2[3][3];
        int i;

        m1[0][0] = 1.; m1[0][1] = 0.; m1[0][2] = 0.;
        m1[1][0] = 0.; m1[1][1] = 1.; m1[1][2] = 0.;
        m1[2][0] = 0.; m1[2][1] = 0.; m1[2][2] = 1.;

        m2[0][0] = cos(M_PI/6.);  m2[0][1] = sin(M_PI/6.); m2[0][2] = 0.;
        m2[1][0] = -sin(M_PI/6.); m2[1][1] = cos(M_PI/6.); m2[1][2] = 0.;
        m2[2][0] = 0.;            m2[2][1] = 0.;           m2[2][2] = 1.;

        for(i = 0; i < 1000000; ++i) {
            mult(m1,m2,m3);
        }
    }
    gettimeofday(&t_end,0);
    double t = (t_end.tv_sec - t_start.tv_sec)*1e6;
    t += (double)(t_end.tv_usec - t_start.tv_usec);

    printf("%.4g ms\n", t/1e3);

    /* Force result to be used: */
    if(1){
        size_t i, j;
        printf("m3 = [\n");
        for(i = 0; i < 3; ++i) {
            printf("[");
            for(j = 0; j < 3; ++j) {
                printf(" %g", m3[i][j]);
            }
            printf("]\n");
        }
        printf("]\n");
    }
}
#else

#include <iostream>
#include <cmath>
#include <cml/core/fixed.h>
#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/gemm.h>	// For matrix multiplication.
#include <sys/time.h>

/* For convenience: */
using std::cerr;
using std::endl;

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename Element, class ArrayType, typename Orient> std::ostream&
operator<<(std::ostream& os, const cml::matrix<Element,ArrayType,Orient>& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "[";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m(i,j);
        }
        os << "]" << endl;
    }
    os << "]";
    return os;
}

template<class M1, class M2, class M3>
inline void mult(const M1& A, const M2& B, M3& res)
{
    int row, col, k;
    for(row = 0; row < 3; ++row) {
	for(col = 0; col < 3; ++col) {
	    double sum = A(row,0)*B(0,col);
	    for(k = 1; k < 3; ++k) {
		sum += A(row,k)*B(k,col);
	    }
	    res(row,col) = sum;
	}
    }
}

inline void timed()
{
    using cml::core::fixed;
    using cml::row_major;
    typedef cml::matrix<double, fixed<3,3>, row_major> matrix_d3_3r;

    struct timeval t_start, t_end;
    gettimeofday(&t_start,0);
    matrix_d3_3r m3;
    {
        matrix_d3_3r m1, m2;

        m1(0,0) = 1.; m1(0,1) = 0.; m1(0,2) = 0.;
        m1(1,0) = 0.; m1(1,1) = 1.; m1(1,2) = 0.;
        m1(2,0) = 0.; m1(2,1) = 0.; m1(2,2) = 1.;

        m2(0,0) = std::cos(M_PI/6.);  m2(0,1) = std::sin(M_PI/6.); m2(0,2) = 0.;
        m2(1,0) = -std::sin(M_PI/6.); m2(1,1) = std::cos(M_PI/6.); m2(1,2) = 0.;
        m2(2,0) = 0.;                 m2(2,1) = 0.;                m2(2,2) = 1.;

#if 0
        cerr << "here!" << endl;
        m3 = m1*m2;
#else
        for(int i = 0; i < 1000000; ++i) {
            matrix_d3_3r mz = m1*m2;
            //gemm(m3,m1,m2);
            //mult(m1,m2,m3);
        }
#endif
    }
    gettimeofday(&t_end,0);
    double t = (t_end.tv_sec - t_start.tv_sec)*1e6;
    t += (double)(t_end.tv_usec - t_start.tv_usec);

    printf("%.4g ms\n", t/1e3);

    /* Force matrix to be used: */
    cerr << "m3 = " << m3 << endl;
}
#endif


int main()
{
#ifdef C_TIMED
    c_timed();
#else
    timed();
#endif
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
