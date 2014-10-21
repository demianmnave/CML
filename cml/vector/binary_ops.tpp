/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_BINARY_OPS_TPP
#error "vector/binary_ops.tpp not included correctly"
#endif

namespace cml {

template<class Sub1, class Sub2> inline auto
operator-(
  const readable_vector<Sub1>& sub1,
  const readable_vector<Sub2>& sub2
  )
-> vector_binary_node<Sub1, Sub2, op::binary_minus<
  typename Sub1::value_type, typename Sub2::value_type>>
{
  return vector_binary_node<Sub1, Sub2, op::binary_minus<
    typename Sub1::value_type, typename Sub2::value_type>>(sub1,sub2);
}

template<class Sub1, class Sub2> inline auto
operator+(
  const readable_vector<Sub1>& sub1,
  const readable_vector<Sub2>& sub2
  )
-> vector_binary_node<Sub1, Sub2, op::binary_plus<
  typename Sub1::value_type, typename Sub2::value_type>>
{
  return vector_binary_node<Sub1, Sub2, op::binary_plus<
    typename Sub1::value_type, typename Sub2::value_type>>(sub1,sub2);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
