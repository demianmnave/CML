/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>

/* For convenience: */
using std::cerr;
using std::endl;

typedef double* vector_d4/*[4]*/;
#define VECINIT(_v_) _v_ = &c_v[c_i++][0]

std::ostream&
operator<<(std::ostream& os, const vector_d4& v)
{
    os << "[";
    for(size_t i = 0; i < 4; ++i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}


#include "cvector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
