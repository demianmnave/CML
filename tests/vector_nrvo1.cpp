/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/core/fixed.h>
#include <cml/vector.h>
#include "timing.h"

/* For convenience: */
using std::cerr;
using std::endl;

using cml::core::fixed;
typedef cml::vector< double, fixed<4> > vector_d4;

/* Note: this has to have the same template params as cml::vector<>: */
template<typename Element, class ArrayType> std::ostream&
operator<<(std::ostream& os, const cml::vector<Element,ArrayType>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++ i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

/* Add two vectors: */
template<typename E, class AT>
inline cml::vector<E,AT>
operator+(
        const cml::vector<E,AT>& left,
        const cml::vector<E,AT>& right
        )
{
    cml::vector<E,AT> nrv(left);
    nrv += right;
    return nrv;
}

/* Scale a vector: */
template<typename E, class AT> inline cml::vector<E,AT>
operator*(
        const cml::vector<E,AT>& left,
        E v
        )
{
    cml::vector<E,AT> nrv(left);
    nrv *= v;
    return nrv;
}

/* Scale a vector: */
template<typename E, class AT> inline cml::vector<E,AT>
operator*(
        E v,
        const cml::vector<E,AT>& right
        )
{
    cml::vector<E,AT> nrv(right);
    nrv *= v;
    return nrv;
}

inline void timed1(
        vector_d4& v,
        const vector_d4& v1,
        const vector_d4& v2,
        const vector_d4& v3,
        const vector_d4& v4,
        size_t n_iter
        )
{
    for(int i = 0; i < n_iter; ++ i) {
        //v += v1+v2+v3;
        v = v+v1+v2+v3;
    }
}

#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
