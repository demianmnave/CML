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
-> vector_unary_node<const Sub&, vector_unary_minus<Sub>>
{
  return vector_unary_node<const Sub&, vector_unary_minus<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator-(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, vector_unary_minus<Sub>>
{
  return vector_unary_node<
    Sub&&, vector_unary_minus<Sub>>((Sub&&) sub);
}

template<class Sub> inline auto
operator+(const readable_vector<Sub>& sub)
-> vector_unary_node<const Sub&, vector_unary_plus<Sub>>
{
  return vector_unary_node<const Sub&, vector_unary_plus<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator+(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, vector_unary_plus<Sub>>
{
  return vector_unary_node<
    Sub&&, vector_unary_plus<Sub>>((Sub&&) sub);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
