/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/enable_if_arithmetic.h>
#include <cml/scalar/binary_ops.h>
#include <cml/quaternion/scalar_node.h>

namespace cml {
/** Helper function to generate a quaternion_scalar_node from a quaternion
 * type (i.e. derived from readable_quaternion<>) and a scalar type.
 */
template<class Op, class Sub, class Scalar,
  enable_if_quaternion_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
auto
make_quaternion_scalar_node(Sub&& sub,
  Scalar&& v) -> quaternion_scalar_node<actual_operand_type_of_t<decltype(sub)>,
  actual_operand_type_of_t<decltype(v)>, Op>
{
  static_assert(
    std::is_same_v<decltype(sub), decltype(std::forward<Sub>(sub))>,
    "internal error: unexpected expression type (sub)");
  static_assert(
    std::is_same_v<decltype(v), decltype(std::forward<Scalar>(v))>,
    "internal error: unexpected expression type (v)");

  /* Deduce the operand types of the scalar and the subexpression (&,
   * const&, &&):
   */
  using sub_type = actual_operand_type_of_t<decltype(sub)>;
  using scalar_type = actual_operand_type_of_t<decltype(v)>;
  return quaternion_scalar_node<sub_type, scalar_type, Op>((sub_type) sub,
    (scalar_type) v);
}

template<class Sub, class Scalar, enable_if_quaternion_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
auto
operator*(Sub&& sub, Scalar&& v)
  -> decltype(make_quaternion_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_quaternion_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Scalar, class Sub,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr,
  enable_if_quaternion_t<Sub>* = nullptr>
auto
operator*(Scalar&& v, Sub&& sub)
  -> decltype(make_quaternion_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_quaternion_scalar_node<binary_multiply_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}

template<class Sub, class Scalar, enable_if_quaternion_t<Sub>* = nullptr,
  enable_if_arithmetic_t<cml::unqualified_type_t<Scalar>>* = nullptr>
auto
operator/(Sub&& sub, Scalar&& v)
  -> decltype(make_quaternion_scalar_node<binary_divide_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v)))
{
  return make_quaternion_scalar_node<binary_divide_t<Sub, Scalar>>(
    std::forward<Sub>(sub), std::forward<Scalar>(v));
}
} // namespace cml
