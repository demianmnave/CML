/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/enable_if_arithmetic.h>
#include <cml/scalar/binary_ops.h>
#include <cml/matrix/scalar_node.h>

namespace cml {

/** Helper function to generate a matrix_scalar_node from a matrix type
 * (i.e. derived from readable_matrix<>) and a scalar type.
 */
template<class Op, class Sub, class Scalar, enable_if_matrix_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
inline auto
make_matrix_scalar_node(Sub&& sub,
  Scalar&& v) -> matrix_scalar_node<actual_operand_type_of_t<decltype(sub)>,
  actual_operand_type_of_t<decltype(v)>, Op>
{
  static_assert(
    std::is_same<decltype(sub), decltype(std::forward<Sub>(sub))>::value,
    "internal error: unexpected expression type (sub)");
  static_assert(
    std::is_same<decltype(v), decltype(std::forward<Scalar>(v))>::value,
    "internal error: unexpected expression type (v)");

  /* Deduce the operand types of the scalar and the subexpression (&,
   * const&, &&):
   */
  using sub_type = actual_operand_type_of_t<decltype(sub)>;
  using scalar_type = actual_operand_type_of_t<decltype(v)>;
  return matrix_scalar_node<sub_type, scalar_type, Op>((sub_type) sub,
    (scalar_type) v);
}

template<class Sub, class Scalar, enable_if_matrix_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
inline auto
operator*(Sub&& sub, Scalar&& v)
  -> decltype(make_matrix_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Scalar, class Sub,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr,
  enable_if_matrix_t<Sub>* = nullptr>
inline auto
operator*(Scalar&& v, Sub&& sub)
  -> decltype(make_matrix_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Sub, class Scalar, enable_if_matrix_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
inline auto
operator/(Sub&& sub, Scalar&& v)
  -> decltype(make_matrix_scalar_node<binary_divide_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_matrix_scalar_node<binary_divide_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

}  // namespace cml
