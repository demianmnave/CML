/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_SCALAR_OPS_TPP
#error "matrix/scalar_ops.tpp not included correctly"
#endif

#include <cml/common/mpl/enable_if_arithmetic.h>

namespace cml {

/** Helper function to generate a matrix_scalar_node from a matrix type
 * (i.e. derived from readable_matrix<>) and a scalar type.
 */
template<class Op, class Sub, class Scalar,
  cml::enable_if_matrix_t<Sub>* = nullptr,
  cml::enable_if_arithmetic_t<Scalar>* = nullptr
> inline auto
make_matrix_scalar_node(Sub&& sub, Scalar&& v)
-> matrix_scalar_node<
actual_operand_type_of_t<decltype(sub)>,
actual_operand_type_of_t<decltype(v)>,
Op
>
{
  static_assert(std::is_same<
    decltype(sub), decltype(std::forward<Sub>(sub))>::value,
    "internal error: unexpected expression type (sub)");
  static_assert(std::is_same<
    decltype(v), decltype(std::forward<Scalar>(v))>::value,
    "internal error: unexpected expression type (v)");

  /* Deduce the operand types of the scalar and the subexpression (&,
   * const&, &&):
   */
  typedef actual_operand_type_of_t<decltype(sub)> sub_type;
  typedef actual_operand_type_of_t<decltype(v)> scalar_type;
  return matrix_scalar_node<sub_type, scalar_type, Op>(
    (sub_type) sub, (scalar_type) v);
}

template<class Sub, class Scalar,
  cml::enable_if_matrix_t<Sub>* = nullptr,
  cml::enable_if_arithmetic_t<Scalar>* = nullptr
>
inline auto operator*(Sub&& sub, Scalar&& v)
-> decltype(make_matrix_scalar_node<matrix_scalar_multiply<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<matrix_scalar_multiply<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Scalar, class Sub,
  cml::enable_if_arithmetic_t<Scalar>* = nullptr,
  cml::enable_if_matrix_t<Sub>* = nullptr
>
inline auto operator*(Scalar&& v, Sub&& sub)
-> decltype(make_matrix_scalar_node<matrix_scalar_multiply<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<matrix_scalar_multiply<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Sub, class Scalar,
  cml::enable_if_matrix_t<Sub>* = nullptr,
  cml::enable_if_arithmetic_t<Scalar>* = nullptr
>
inline auto operator/(Sub&& sub, Scalar&& v)
-> decltype(make_matrix_scalar_node<matrix_scalar_divide<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<matrix_scalar_divide<Sub,Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
