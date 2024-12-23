/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/binary_ops.h>
#include <cml/quaternion/binary_node.h>

namespace cml {

/** Helper function to generate a quaternion_binary_node from two
 * quaternion types (i.e. derived from readable_quaternion<>).
 */
template<class Op, class Sub1, class Sub2,
  enable_if_quaternion_t<Sub1>* = nullptr,
  enable_if_quaternion_t<Sub2>* = nullptr>
inline auto
make_quaternion_binary_node(Sub1&& sub1, Sub2&& sub2)
  -> quaternion_binary_node<actual_operand_type_of_t<decltype(sub1)>,
    actual_operand_type_of_t<decltype(sub2)>, Op>
{
  static_assert(
    std::is_same<decltype(sub1), decltype(std::forward<Sub1>(sub1))>::value,
    "internal error: unexpected expression type (sub1)");
  static_assert(
    std::is_same<decltype(sub2), decltype(std::forward<Sub2>(sub2))>::value,
    "internal error: unexpected expression type (sub2)");

  /* Deduce the operand types of the subexpressions (&, const&, &&): */
  using sub1_type = actual_operand_type_of_t<decltype(sub1)>;
  using sub2_type = actual_operand_type_of_t<decltype(sub2)>;
  return quaternion_binary_node<sub1_type, sub2_type, Op>((sub1_type) sub1,
    (sub2_type) sub2);
}

template<class Sub1, class Sub2, enable_if_quaternion_t<Sub1>* = nullptr,
  enable_if_quaternion_t<Sub2>* = nullptr>
inline auto
operator-(Sub1&& sub1, Sub2&& sub2)
  -> decltype(make_quaternion_binary_node<binary_minus_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2)))
{
  return make_quaternion_binary_node<binary_minus_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
}

template<class Sub1, class Sub2, enable_if_quaternion_t<Sub1>* = nullptr,
  enable_if_quaternion_t<Sub2>* = nullptr>
inline auto
operator+(Sub1&& sub1, Sub2&& sub2)
  -> decltype(make_quaternion_binary_node<binary_plus_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2)))
{
  return make_quaternion_binary_node<binary_plus_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
}

}  // namespace cml
