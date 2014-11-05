/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_DOT_TPP
#error "vector/dot.tpp not included correctly"
#endif

#include <cml/vector/size_checking.h>

namespace cml {

template<class Sub1, class Sub2> auto
dot(const readable_vector<Sub1>& left, const readable_vector<Sub2>& right)
-> typename value_type_promote<Sub1, Sub2>::scalar_type
{
  typedef typename value_type_promote<Sub1, Sub2>::scalar_type scalar_type;
  cml::check_minimum_size(left, cml::int_c<1>());
  cml::check_minimum_size(right, cml::int_c<1>());
  cml::check_same_size(left, right);
  scalar_type accum = left.get(0)*right.get(0);
  for(int i = 1; i < left.size(); ++ i) accum += left.get(i)*right.get(i);
  return accum;
  // TODO This could be reformulated as a reduction operator.
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
