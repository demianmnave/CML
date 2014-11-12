/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_PERP_DOT_TPP
#error "vector/perp_dot.tpp not included correctly"
#endif

#include <cml/vector/readable_vector.h>
#include <cml/vector/size_checking.h>

namespace cml {

template<class Sub1, class Sub2> auto perp_dot(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  ) -> value_type_promote_t<vector_traits<Sub1>, vector_traits<Sub2>>
{
  typedef value_type_promote_t<
    vector_traits<Sub1>, vector_traits<Sub2>> result_type;
  cml::check_size(left, cml::int_c<2>());
  cml::check_size(right, cml::int_c<2>());
  return result_type(left[0]*right[1] - left[1]*right[0]);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
