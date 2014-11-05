/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_CROSS_TPP
#error "vector/cross.tpp not included correctly"
#endif

#include <cml/vector/size_checking.h>

namespace cml {

template<class Sub1, class Sub2> auto cross(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  ) -> cross_promote<Sub1,Sub2>
{
  typedef cross_promote<Sub1,Sub2> result_type;
  cml::check_size(left, cml::int_c<3>());
  cml::check_size(right, cml::int_c<3>());
  return result_type(
    left[1]*right[2] - left[2]*right[1],
    left[2]*right[0] - left[0]*right[2],
    left[0]*right[1] - left[1]*right[0]
    );
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
