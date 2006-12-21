/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Check assignment to and from external vectors.
 */

#include <cml/cml.h>

void vector_test()
{
    using namespace cml;

    float a1[3], a2[3], a3[3];
    vector< float, external<3> > v1(a1);
    vector< float, external<> > v2(a2,3);
    vector< float, fixed<3> > v;

    // Assignment to element of external<N> vector ok
    v1[0] = 0.0f;

    // Assignment to external<N> vector ok.
    v1 = v;

    // Assignment from external<N> vector ok
    v = v1;

    // Assignment to element of external<> vector ok
    v2[0] = 0.0f;

    // Assignment to external<> vector not ok
    v2 = v;

    // Assignment from external<> vector not ok.
    v = v2;

    // Copy construct a dynamic vector from an external vector ok.
    vector< float, dynamic<> > v3(a3,3);
}

void matrix_test()
{
    using namespace cml;

    float a1[3][3], a2[3][3], a3[3][3];
    matrix< float, external<3,3> > m1(a1);
    matrix< float, external<> > m2(&a2[0][0],3,3);
    matrix< float, fixed<3,3> > m;

    // Assignment to element of external<N> matrix ok
    m1(0,0) = 0.0f;

    // Assignment to external<N> matrix ok - is this correct?
    m1 = m;

    // Assignment from external<N> matrix ok
    m = m1;

    // Assignment to element of external<> matrix ok
    m2(0,0) = 0.0f;

    // Assignment to external<> matrix not ok
    m2 = m;

    // Assignment from external<> matrix not ok - is this correct?
    m = m2;

    // Copy construct a dynamic matrix from an external matrix ok.
    matrix< float, dynamic<> > m3(&a3[0][0],3,3);
}

int main()
{
    vector_test();
}


// -------------------------------------------------------------------------
// vim:ft=cpp
