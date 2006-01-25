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

/** Try some complex fixed vector ops.
 *
 * @return 0 if the test was successful.
 */
int fixed_operator_test()
{
    cerr << "]] fixed vector operator test" << endl;
    using cml::core::fixed;
    using cml::dot;

    typedef cml::vector< double, fixed<4> > vector_d4;

    vector_d4 v1, v2, v3;
    v1[0] = 1.; v1[1] = 0.; v1[2] = 0.; v1[3] = 1.;
    v2[0] = 0.; v2[1] = 1.; v2[2] = 0.; v2[3] = 1.;
    v3[0] = 0.; v3[1] = 0.; v3[2] = 1.; v3[3] = 1.;

    cerr << "v1 = " << v1 << endl;
    cerr << "v2 = " << v2 << endl;
    cerr << "v3 = " << v3 << endl;
    cerr << "dot(v1,v2) = " << dot(v1,v2) << endl;
    cerr << "dot(v1,v3) = " << dot(v1,v3) << endl;
    cerr << "dot(v2,v3) = " << dot(v2,v3) << endl;

    vector_d4 v4 = v1+v2;
    cerr << "v4 = v1+v2 = " << v4 << endl;
    cerr << "dot(v4,v2) = " << dot(v4,v2) << endl;

    return 0;
}

/** Try some complex dynamic vector ops.
 *
 * @return 0 if the test was successful.
 */
int dynamic_operator_test()
{
    cerr << "]] dynamic vector operator test" << endl;
    using cml::core::dynamic;
    using cml::dot;

    typedef cml::vector< double, dynamic<> > vector_d;

    vector_d v1(4), v2(4), v3(4);
    v1[0] = 1.; v1[1] = 0.; v1[2] = 0.; v1[3] = 1.;
    v2[0] = 0.; v2[1] = 1.; v2[2] = 0.; v2[3] = 1.;
    v3[0] = 0.; v3[1] = 0.; v3[2] = 1.; v3[3] = 1.;

    cerr << "v1 = " << v1 << endl;
    cerr << "v2 = " << v2 << endl;
    cerr << "v3 = " << v3 << endl;
    cerr << "dot(v1,v2) = " << dot(v1,v2) << endl;
    cerr << "dot(v1,v3) = " << dot(v1,v3) << endl;
    cerr << "dot(v2,v3) = " << dot(v2,v3) << endl;

    vector_d v4 = v1+v2;
    cerr << "v4 = v1+v2 = " << v4 << endl;
    cerr << "dot(v4,v2) = " << dot(v4,v2) << endl;

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
