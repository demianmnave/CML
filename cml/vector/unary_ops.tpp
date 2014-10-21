/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_UNARY_OPS_TPP
#error "vector/unary_ops.tpp not included correctly"
#endif

namespace cml {

template<class Sub> inline auto
operator-(const readable_vector<Sub>& sub)
-> vector_unary_node<Sub, op::unary_minus<typename Sub::value_type>>
{
  return vector_unary_node<
    Sub, op::unary_minus<typename Sub::value_type>>(sub);
}

template<class Sub> inline auto
operator+(const readable_vector<Sub>& sub)
-> vector_unary_node<Sub, op::unary_plus<typename Sub::value_type>>
{
  return vector_unary_node<
    Sub, op::unary_plus<typename Sub::value_type>>(sub);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
