/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  XXX The tests should use a testing rig, but this can wait for now.
 */

#include <iostream>
#include <cml/core/fixed.h>
#include <cml/core/dynamic.h>
#include <cml/vector.h>

/* For convenience: */
using std::cerr;
using std::endl;

/** Test const access into the vector. */
template<class V>
void const_test(const char* n, const V& v)
{
    cerr << "const " << n << "[1] = " << v[1] << endl;
}

/** Try to create static and dynamic vectors.
 *
 * @return 0 if the test was successful.
 */
int instance_test()
{
    using cml::core::fixed;
    using cml::core::dynamic;

    typedef cml::vector< double, fixed<3> > vector_d3;
    typedef cml::vector< double, dynamic<> > vector_d;

    vector_d3 v1;
    vector_d v2(3);
    vector_d v3(100);

    cerr << "v1 size = " << v1.size() << endl;
    cerr << "v3 size = " << v3.size() << endl;

    v1[1] = 1.;
    v2[1] = 1.;
    v3[99] = 101.3;
    cerr << "v1[1] = " << v1[1] << endl;
    cerr << "v2[1] = " << v2[1] << endl;
    cerr << "v3[99] = " << v3[99] << endl;

    const_test("v1", v1);
    const_test("v2", v2);

    return 0;
}

int main()
{
    return instance_test();
}

// -------------------------------------------------------------------------
// vim:ft=cpp
