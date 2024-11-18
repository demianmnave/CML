/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef __CML_UTIL_QUATERNION_PRINT_TPP
#  error "util/quaternion_print.tpp not included correctly"
#endif

#include <iostream>
#include <cml/quaternion/order_tags.h>
#include <cml/quaternion/readable_quaternion.h>

namespace cml {

template<class DT>
inline std::ostream&
operator<<(std::ostream& os, const readable_quaternion<DT>& q)
{
  using order_type = order_type_trait_of_t<DT>;
  os << "[ "
     << " " << q[order_type::W] << " " << q[order_type::X] << " "
     << q[order_type::Y] << " " << q[order_type::Z] << " ]";
  return os;
}

}  // namespace cml
