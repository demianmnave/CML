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

/* Note: this has to have the same template params as cml::vector<>: */
template<typename Element, class ArrayType> std::ostream&
operator<<(std::ostream& os, const cml::vector<Element,ArrayType>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

/** Try some simple fixed<> vector operators.
 *
 * @return 0 if the test was successful.
 */
int fixed_operator_test()
{
    cerr << "]] fixed vector operator test" << endl;
    using cml::core::fixed;

    typedef cml::vector< double, fixed<4> > vector_d4;

    vector_d4 v1, v2, v3;
    v1[0] = 1.; v1[1] = 0.; v1[2] = 0.; v1[3] = 1.;
    v2[0] = 0.; v2[1] = 1.; v2[2] = 0.; v2[3] = 1.;
    v3[0] = 0.; v3[1] = 0.; v3[2] = 1.; v3[3] = 1.;

    vector_d4 v4 = v1+v2;
    cerr << "v4 = v1+v2 = " << v4 << endl;

    vector_d4 v5 = v1*2;
    cerr << "v5 = v1*2 = " << v5 << endl;

    vector_d4 v6 = 2*v5;
    cerr << "v6 = 2*v5 = " << v6 << endl;

    vector_d4 v7 = v6/4;
    cerr << "v7 = v6/4 = " << v7 << endl;

    vector_d4 v8 = v1+v2-v1*2-v7;
    cerr << "v8 = v1+v2-v1*2-v7 = " << v8 << endl;

    vector_d4 v9; v9 = v8;
    cerr << "v9 = v8 = " << v9 << endl;

    return 0;
}


/** Try some simple dynamic<> vector operators.
 *
 * @return 0 if the test was successful.
 */
int dynamic_operator_test()
{
    cerr << "]] dynamic vector operator test" << endl;
    using cml::core::dynamic;

    typedef cml::vector< double, dynamic<> > vector_d;

    vector_d v1(4), v2(4), v3(4);
    v1[0] = 1.; v1[1] = 0.; v1[2] = 0.; v1[3] = 1.;
    v2[0] = 0.; v2[1] = 1.; v2[2] = 0.; v2[3] = 1.;
    v3[0] = 0.; v3[1] = 0.; v3[2] = 1.; v3[3] = 1.;

    vector_d v4 = v1+v2;
    cerr << "v4 = v1+v2 = " << v4 << endl;

    vector_d v5 = v1*2;
    cerr << "v5 = v1*2 = " << v5 << endl;

    vector_d v6 = 2*v5;
    cerr << "v6 = 2*v5 = " << v6 << endl;

    vector_d v7 = v6/4;
    cerr << "v7 = v6/4 = " << v7 << endl;

    vector_d v8 = v1+v2-v1*2-v7;
    cerr << "v8 = v1+v2-v1*2-v7 = " << v8 << endl;

    {
        vector_d v9(4); v9 = v8;
        cerr << "v9 = v8 = " << v9 << endl;
        cerr << "v8[0] = " << &v8[0] << endl;
        cerr << "v9[0] = " << &v9[0] << endl;
    }

    return 0;
}

int main()
{
    int status;
    if((status = fixed_operator_test()) != 0) return status;
    if((status = dynamic_operator_test()) != 0) return status;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
