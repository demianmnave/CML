/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "cml_config.h"         // Must be first!

#include <iostream>
#include <cmath>
#include <cml/vector.h>

using std::cout;
using std::endl;
using cml::fixed;
using cml::dynamic;
using namespace cml::vector_ops;

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

void test1()
{
    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3>, vector_orient> vector_d3;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;
    cout << "dot(u,v) = " << dot(T(u),v) << endl;
    cout << "dot(u,u) = " << dot(T(u),u) << endl;
    cout << "dot(u+v,v) = " << dot(T(u+v),v) << endl;
    //cout << "cos(u,v) = " << dot(T(u),v)/sqrt(dot(T(u),u)*dot(T(v),v)) << endl;
}

void test2()
{
    /* 3-space column vector, dynamic length, double coordinates: */
    typedef cml::vector< double, dynamic<>, vector_orient> vector_d;

    vector_d u(3), v(3);
    cout << "dot(u,v) = " << dot(T(u),v) << endl;
    cout << "dot(u,u) = " << dot(T(u),u) << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
