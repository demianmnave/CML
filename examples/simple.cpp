/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * g++ -I.. -Wall -W -O3 -o simple simple.cpp
 */

#include "cml_config.h"         // Must be first!

#include <iostream>
#include <cmath>
#include <cml/vector.h>
#include <cml/matrix.h>

using std::cout;
using std::endl;
using cml::fixed;
using cml::dynamic;
using namespace cml::vector_ops;
using namespace cml::matrix_ops;

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

void example1()
{
    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3>, vector_orient> vector_d3;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "Example1:" << endl;
    transpose(u);
    cout << "  dot(u,v) = " << dot(T(u),v) << endl;
    cout << "  dot(u,u) = " << dot(T(u),u) << endl;
    cout << "  dot(u+v,v) = " << dot(T(u+v),v) << endl;
    cout << "  cos(u,v) = " << dot(T(u),v)/sqrt(dot(T(u),u)*dot(T(v),v))
        << endl;
}

void example2()
{
    /* 3-space column vector, dynamic length, double coordinates: */
    typedef cml::vector< double, dynamic<>, vector_orient> vector_d;

    vector_d u(3), v(3);
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "Example2:" << endl;
    cout << "  dot(u,v) = " << dot(T(u),v) << endl;
    cout << "  dot(u,u) = " << dot(T(u),u) << endl;
    cout << "  dot(u+v,v) = " << dot(T(u+v),v) << endl;
    cout << "  cos(u,v) = " << dot(T(u),v)/sqrt(dot(T(u),u)*dot(T(v),v))
        << endl;
}

void example3()
{
    /* 3-space column matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3>, vector_orient> matrix_d3;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    cout << "Example3:" << endl;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;

    typedef matrix_d3::transposed_type matrix_d3t;
    matrix_d3t Cp = T(A)+T(B);
    cout << "  Cp(0,2) = " << Cp(0,2) << endl;
}

void example4()
{
    /* 3-space column matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3>, vector_orient> matrix_d3;

    /* 3-space column matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<>, vector_orient> matrix_d;

    matrix_d3 A, C;
    matrix_d B(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    cout << "Example4:" << endl;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;

    typedef matrix_d3::transposed_type matrix_d3t;
    matrix_d3t Cp = T(A+B);
    cout << "  Cp(0,2) = " << Cp(0,2) << endl;
}

void example5()
{
    /* 3-space column matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3>, vector_orient> matrix_d3;

    /* 3-space column matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<>, vector_orient> matrix_d;

    matrix_d3 A, B;
    matrix_d C(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    cout << "Example4:" << endl;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;

    typedef matrix_d3::transposed_type matrix_d3t;
    matrix_d3t Cp = T(A)+T(B);
    cout << "  Cp(0,2) = " << Cp(0,2) << endl;
}

int main()
{
    example1();
    example2();
    example3();
    example4();
    example5();
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
