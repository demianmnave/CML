/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_UNARY_OPS_TPP
#error "matrix/unary_ops.tpp not included correctly"
#endif

namespace cml {

template<class Sub> inline auto
operator-(const readable_matrix<Sub>& sub)
-> matrix_unary_node<const Sub&, matrix_unary_minus<Sub>>
{
  return matrix_unary_node<const Sub&, matrix_unary_minus<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator-(readable_matrix<Sub>&& sub)
-> matrix_unary_node<Sub&&, matrix_unary_minus<Sub>>
{
  return matrix_unary_node<
    Sub&&, matrix_unary_minus<Sub>>((Sub&&) sub);
}

template<class Sub> inline auto
operator+(const readable_matrix<Sub>& sub)
-> matrix_unary_node<const Sub&, matrix_unary_plus<Sub>>
{
  return matrix_unary_node<const Sub&, matrix_unary_plus<Sub>>(sub.actual());
}

template<class Sub> inline auto
operator+(readable_matrix<Sub>&& sub)
-> matrix_unary_node<Sub&&, matrix_unary_plus<Sub>>
{
  return matrix_unary_node<
    Sub&&, matrix_unary_plus<Sub>>((Sub&&) sub);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
