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

typedef double vector_d4[4];
#define VECINIT(_v_) _v_

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

#include "cvector_algebra2.cpp"
#include "vector_main2.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
