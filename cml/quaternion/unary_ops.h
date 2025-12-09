/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/unary_ops.h>
#include <cml/quaternion/unary_node.h>

namespace cml {
/** Helper function to generate a quaternion_unary_node from a quaternion
 * type (i.e. derived from readable_quaternion<>).
 */
template<class Op, class Sub, enable_if_quaternion_t<Sub>* = nullptr>
auto
make_quaternion_unary_node(Sub&& sub)
  -> quaternion_unary_node<actual_operand_type_of_t<decltype(sub)>, Op>
{
  static_assert(
    std::is_same_v<decltype(sub), decltype(std::forward<Sub>(sub))>,
    "internal error: unexpected expression type");

  /* Deduce the operand type of the subexpression (&, const&, &&): */
  using sub_type = actual_operand_type_of_t<decltype(sub)>;
  return quaternion_unary_node<sub_type, Op>((sub_type) sub);
}

template<class Sub, enable_if_quaternion_t<Sub>* = nullptr>
auto
operator-(Sub&& sub) -> decltype(make_quaternion_unary_node<unary_minus_t<Sub>>(
  std::forward<Sub>(sub)))
{
  return make_quaternion_unary_node<unary_minus_t<Sub>>(std::forward<Sub>(sub));
}

template<class Sub, enable_if_quaternion_t<Sub>* = nullptr>
auto
operator+(Sub&& sub) -> decltype(make_quaternion_unary_node<unary_plus_t<Sub>>(
  std::forward<Sub>(sub)))
{
  return make_quaternion_unary_node<unary_plus_t<Sub>>(std::forward<Sub>(sub));
}
} // namespace cml
