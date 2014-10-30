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
-> vector_unary_node<const Sub&, unary_minus_type<Sub>>
{
  return vector_unary_node<const Sub&, unary_minus_type<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator-(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, unary_minus_type<Sub>>
{
  return vector_unary_node<
    Sub&&, unary_minus_type<Sub>>((Sub&&) sub);
}

template<class Sub> inline auto
operator+(const readable_vector<Sub>& sub)
-> vector_unary_node<const Sub&, unary_plus_type<Sub>>
{
  return vector_unary_node<const Sub&, unary_plus_type<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator+(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, unary_plus_type<Sub>>
{
  return vector_unary_node<
    Sub&&, unary_plus_type<Sub>>((Sub&&) sub);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
