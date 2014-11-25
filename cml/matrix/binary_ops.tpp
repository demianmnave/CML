/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_BINARY_OPS_TPP
#error "matrix/binary_ops.tpp not included correctly"
#endif

#include <cml/matrix/is_matrix.h>

namespace cml {

/** Helper function to generate a matrix_binary_node from two matrix types
 * (i.e. derived from readable_matrix<>).
 */
template<class Op, class Sub1, class Sub2,
  typename std::enable_if<is_matrix<Sub1>::value>::type* = nullptr,
  typename std::enable_if<is_matrix<Sub2>::value>::type* = nullptr
> inline auto
make_matrix_binary_node(Sub1&& sub1, Sub2&& sub2)
->  matrix_binary_node<
typename actual_operand_type_of<decltype(std::forward<Sub1>(sub1))>::type,
typename actual_operand_type_of<decltype(std::forward<Sub2>(sub2))>::type,
Op
>
{
  typedef typename actual_operand_type_of<
    decltype(std::forward<Sub1>(sub1))>::type		sub1_type;
  typedef typename actual_operand_type_of<
    decltype(std::forward<Sub2>(sub2))>::type		sub2_type;
  return matrix_binary_node<sub1_type, sub2_type, Op>(
    (sub1_type) sub1, (sub2_type) sub2);
}

template<class Sub1, class Sub2>
inline auto operator-(Sub1&& sub1, Sub2&& sub2)
-> decltype(make_matrix_binary_node<op::binary_minus<double,double>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2)))
{
  return make_matrix_binary_node<op::binary_minus<double,double>>
    (std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
}

template<class Sub1, class Sub2>
inline auto operator+(Sub1&& sub1, Sub2&& sub2)
-> decltype(make_matrix_binary_node<op::binary_plus<double,double>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2)))
{
  return make_matrix_binary_node<op::binary_plus<double,double>>
    (std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
