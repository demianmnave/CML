/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  XXX The tests should use a testing rig, but this can wait for now.
 */

#include <iostream>
#include <cmath>
#include <cml/core/fixed.h>
#include <cml/core/dynamic.h>
#include <cml/matrix.h>
#include <cml/gemm.h>	// For matrix multiplication.

/* For convenience: */
using std::cerr;
using std::endl;

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename Element, class ArrayType, typename Orient> std::ostream&
operator<<(std::ostream& os, const cml::matrix<Element,ArrayType,Orient>& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "  [";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m(i,j);
        }
        os << " ]" << endl;
    }
    os << "]" << endl;
    return os;
}

/** Try some complex fixed<>, row-major matrix operators.
 *
 * @return 0 if the test was successful.
 */
int fixed_r_operator_test()
{
    cerr << "]] fixed row-major matrix operator test" << endl;
    using cml::core::fixed;
    using cml::row_major;

    typedef cml::matrix<double, fixed<3,3>, row_major> matrix_d3_3r;

    matrix_d3_3r m1, m2, m3;

    m1(0,0) = 1.; m1(0,1) = 0.; m1(0,2) = 0.;
    m1(1,0) = 0.; m1(1,1) = 1.; m1(1,2) = 0.;
    m1(2,0) = 0.; m1(2,1) = 0.; m1(2,2) = 1.;

    m2(0,0) = 1.; m2(0,1) = 0.; m2(0,2) = 0.;
    m2(1,0) = 0.; m2(1,1) = 1.; m2(1,2) = 0.;
    m2(2,0) = 0.; m2(2,1) = 0.; m2(2,2) = 1.;

    m3(0,0) = std::cos(M_PI/6.);  m3(0,1) = std::sin(M_PI/6.); m3(0,2) = 0.;
    m3(1,0) = -std::sin(M_PI/6.); m3(1,1) = std::cos(M_PI/6.); m3(1,2) = 0.;
    m3(2,0) = 0.;                 m3(2,1) = 0.;                m3(2,2) = 1.;

    cerr << "m1 = " << m1 << endl;
    cerr << "m2 = " << m2 << endl;
    cerr << "m3 = " << m3 << endl;

    cerr << "m1*m2 = " << m1*m2 << endl;
    cerr << "m1*m2 = " << m1*m2 << endl;
    cerr << "m2*m3 = " << m2*m3 << endl;

    cerr << "m1+m2*m3 = " << m1+m2*m3 << endl;
    return 0;
}

/** Try some complex fixed<>, col-major matrix operators.
 *
 * @return 0 if the test was successful.
 */
int fixed_c_operator_test()
{
    cerr << "]] fixed col-major matrix operator test" << endl;
    using cml::core::fixed;
    using cml::col_major;

    typedef cml::matrix<double, fixed<3,3>, col_major> matrix_d3_3c;

    matrix_d3_3c m1, m2, m3;

    m1(0,0) = 1.; m1(0,1) = 0.; m1(0,2) = 0.;
    m1(1,0) = 0.; m1(1,1) = 1.; m1(1,2) = 0.;
    m1(2,0) = 0.; m1(2,1) = 0.; m1(2,2) = 1.;

    m2(0,0) = 1.; m2(0,1) = 0.; m2(0,2) = 0.;
    m2(1,0) = 0.; m2(1,1) = 1.; m2(1,2) = 0.;
    m2(2,0) = 0.; m2(2,1) = 0.; m2(2,2) = 1.;

    m3(0,0) = std::cos(M_PI/6.);  m3(0,1) = std::sin(M_PI/6.); m3(0,2) = 0.;
    m3(1,0) = -std::sin(M_PI/6.); m3(1,1) = std::cos(M_PI/6.); m3(1,2) = 0.;
    m3(2,0) = 0.;                 m3(2,1) = 0.;                m3(2,2) = 1.;

    cerr << "m1 = " << m1 << endl;
    cerr << "m2 = " << m2 << endl;
    cerr << "m3 = " << m3 << endl;

    cerr << "m1*m2 = " << m1*m2 << endl;
    cerr << "m1*m2 = " << m1*m2 << endl;
    cerr << "m2*m3 = " << m2*m3 << endl;

    cerr << "m1+m2*m3 = " << m1+m2*m3 << endl;
    return 0;
}

/** Try some complex dynamic<>, row-major matrix operators.
 *
 * @return 0 if the test was successful.
 */
int dynamic_r_operator_test()
{
    cerr << "]] dynamic row-major matrix operator test" << endl;
    using cml::core::dynamic;
    using cml::row_major;

    typedef cml::matrix<double, dynamic<>, row_major> matrix_d3_3d;

    matrix_d3_3d m1(3,3), m2(3,3), m3(3,3);

    m1(0,0) = 1.; m1(0,1) = 0.; m1(0,2) = 0.;
    m1(1,0) = 0.; m1(1,1) = 1.; m1(1,2) = 0.;
    m1(2,0) = 0.; m1(2,1) = 0.; m1(2,2) = 1.;

    m2(0,0) = 1.; m2(0,1) = 0.; m2(0,2) = 0.;
    m2(1,0) = 0.; m2(1,1) = 1.; m2(1,2) = 0.;
    m2(2,0) = 0.; m2(2,1) = 0.; m2(2,2) = 1.;

    m3(0,0) = std::cos(M_PI/6.);  m3(0,1) = std::sin(M_PI/6.); m3(0,2) = 0.;
    m3(1,0) = -std::sin(M_PI/6.); m3(1,1) = std::cos(M_PI/6.); m3(1,2) = 0.;
    m3(2,0) = 0.;                 m3(2,1) = 0.;                m3(2,2) = 1.;

    cerr << "m1 = " << m1 << endl;
    cerr << "m2 = " << m2 << endl;
    cerr << "m3 = " << m3 << endl;

    cerr << "m1*m2 = " << m1*m2 << endl;
    cerr << "m2*m3 = " << m2*m3 << endl;

    cerr << "m1+m2*m3 = " << m1+m2*m3 << endl;
    return 0;
}

int main()
{
    int status;
    if((status = fixed_r_operator_test()) != 0) return status;
    if((status = dynamic_r_operator_test()) != 0) return status;
    if((status = fixed_c_operator_test()) != 0) return status;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
