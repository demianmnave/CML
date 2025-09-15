/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <iosfwd>

namespace cml {
/* Forward declarations: */
template<class DerivedT> class readable_quaternion;

/** Output a quaternion to a std::ostream. */
template<class DerivedT>
std::ostream& operator<<(std::ostream& os,
  const readable_quaternion<DerivedT>& v);
} // namespace cml

#define __CML_UTIL_QUATERNION_PRINT_TPP
#include <cml/util/quaternion_print.tpp>
#undef __CML_UTIL_QUATERNION_PRINT_TPP
