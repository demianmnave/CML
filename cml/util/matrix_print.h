/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <iosfwd>

namespace cml {

/* Forward declarations: */
template<class DerivedT> class readable_matrix;

/** Output a matrix to a std::ostream. */
template<class DerivedT>
std::ostream& operator<<(std::ostream& os, const readable_matrix<DerivedT>& v);

}  // namespace cml

#define __CML_UTIL_MATRIX_PRINT_TPP
#include <cml/util/matrix_print.tpp>
#undef __CML_UTIL_MATRIX_PRINT_TPP
