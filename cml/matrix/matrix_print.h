/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_print_h
#define matrix_print_h

#include <iosfwd>

namespace cml {

/** Output a matrix to a std::ostream. */
template<typename E, class AT, typename BO, class L> inline std::ostream&
operator<<(std::ostream& os, const matrix<E,AT,BO,L>& m)
{
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "[";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m(i,j);
        }
        os << " ]";
        if (i != m.rows()-1) {
            os << std::endl;
        }
    }
    return os;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
