/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef vector_print_h
#define vector_print_h

#include <iosfwd>

namespace cml {

/** Output a vector to a std::ostream. */
template<typename E, class AT > inline std::ostream&
operator<<(std::ostream& os, const vector<E,AT>& v)
{
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
