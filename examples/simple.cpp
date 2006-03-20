/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief A set of very simple examples of current CML functionality.
 */

#include "cml_config.h"         // Must be first (for now)!

#include <iostream>
#if defined(__ICC) && defined(__linux__) && (__ICC >= 900)
#include <math.h>
namespace std {
    using ::sqrt;
}
#else
#include <cmath>
#endif
#include <cml/cml.h>
using namespace cml;

using std::cout;
using std::endl;

/* Note: this has to have the same template params as cml::vector<>: */
template<typename E, class AT> std::ostream&
operator<<(std::ostream& os, const cml::vector<E,AT>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename E, class AT, class L> std::ostream&
operator<<(std::ostream& os, const cml::matrix<E,AT,L>& m)
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

void example1()
{
    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    cout << "Example1:" << endl;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;
    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

void example2()
{
    /* 3-space column vector, dynamic length, double coordinates: */
    typedef cml::vector< double, dynamic<> > vector_d;

    cout << "Example2:" << endl;

    vector_d u(3), v(3);
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

void example3()
{
    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    cout << "Example3:" << endl;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = T(A)+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
    cout << "  C(2,0) = " << C(2,0) << endl;
}

void example4()
{
    /* 3-space matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* 3-space matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<> > matrix_d;

    cout << "Example4:" << endl;

    matrix_d3 A, C;
    matrix_d B(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
}

void example5()
{
    /* 3-space matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* 3-space matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<> > matrix_d;

    cout << "Example4:" << endl;

    matrix_d3 A, B;
    matrix_d C(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
    cout << C << endl;

    C = A+T(B);
    cout << C << endl;
}

void example6()
{
    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* Column vector of the matrix: */
    typedef matrix_d3::col_vector_type cvector_d3;

    cout << "Example6:" << endl;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = T(A)+B;
    cout << "  T(A)+B = " << C << endl;

    cvector_d3 v = col(C,0);
    cout << "  C(0) = " << endl << v << endl;
    v = col(C,1);
    cout << "  C(1) = " << endl << v << endl;
    v = col(C,2);
    cout << "  C(2) = " << endl << v << endl;

    v = col(T(A)+B,2);
    cout << "  (T(A)+B)(2) = " << endl << v << endl;
}

void example7()
{
    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    cout << "Example7:" << endl;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A*B;
    cout << "  A = " << A << endl;
    cout << "  B = " << B << endl;
    cout << "  A*B = " << C << endl;
}

void example8()
{
    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, external<3> > vector_d3;

    cout << "Example8:" << endl;

    double c_u[3] = {0.,0.,1.};
    double c_v[3] = {1.,0.,0.};
    vector_d3 u(c_u), v(c_v);

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;
    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(v,v) = " << dot(v,v) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

#if defined(CML_ENABLE_DOT_OPERATOR)
void example9()
{
    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    cout << "Example9:" << endl;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;

    cout << "  dot(u,v) = " << u*v << endl;
    cout << "  dot(u,u) = " << u*u << endl;
    cout << "  dot(u+v,v) = " << (u+v)*v << endl;
    cout << "  cos(u,v) = " << (u*v)/sqrt((u*u)*(v*v)) << endl;
}
#endif

void example10()
{
    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<4> > vector_d4;

    cout << "Example10:" << endl;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    vector_d3 x;

    x[0] = 1.; x[1] = 0.; x[2] = 1.;

    cout << "A = " << A << endl;
    cout << "x = " << x << endl;

    vector_d4 y = A*x;
    cout << "y = A*x = " << y << endl;

    vector_d3 yp = y*A;
    cout << "yp = mul(y,A) = " << yp << endl;

    vector_d4 ypp = A*yp;
    cout << "ypp = mul(A,yp) = " << ypp << endl;

    matrix_d43::transposed_type B = T(A);
    cout << "T(A) = " << B << endl;

    vector_d4 z = yp*B;
    cout << "z = yp*T(A) = " << z << endl;
}

void example11()
{
    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<4> > vector_d4;

    cout << "Example11:" << endl;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    vector_d3 x;
    x[0] = 1.; x[1] = 0.; x[2] = 1.;

    cout << "A = " << A << endl;
    cout << "x = " << x << endl;

    vector_d4 y = A*x;
    cout << "y = A*x = " << y << endl;

    matrix_d43 B = outer(y,x);
    cout << "B = outer(y,x) = " << B << endl;
}

void example12()
{
    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space matrix, fixed length, float coordinates: */
    typedef cml::matrix< float, fixed<3,3>, cml::col_major > matrix_f33;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< float, fixed<4> > vector_d4;

    cout << "Example10:" << endl;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    matrix_f33 B = T(A)*A;

    cout << "A = " << A << endl;
    cout << "B[f33] = T(A)*A = " << B << endl;
}

int main()
{
    example1();
    example2();
    example3();
    example4();
    example5();
    example6();
    example7();
    example8();
#if defined(CML_ENABLE_DOT_OPERATOR)
    example9();
#endif
    example10();
    example11();
    example12();
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
