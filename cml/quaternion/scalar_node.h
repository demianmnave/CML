/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/size_tags.h>
#include <cml/quaternion/readable_quaternion.h>

namespace cml {

template<class Sub, class Scalar, class Op> class quaternion_scalar_node;

/** quaternion_scalar_node<> traits. */
template<class Sub, class Scalar, class Op>
struct quaternion_traits<quaternion_scalar_node<Sub, Scalar, Op>>
{
  /* Figure out the basic types of Sub and Scalar: */
  using quaternion_type = quaternion_scalar_node<Sub, Scalar, Op>;
  using left_arg_type = Sub;
  using right_arg_type = Scalar;
  using left_type = cml::unqualified_type_t<Sub>;
  using right_type = cml::unqualified_type_t<Scalar>;
  using left_traits = quaternion_traits<left_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;
  using storage_type = typename left_traits::storage_type;

  using size_tag = typename left_traits::size_tag;
  static_assert(cml::is_fixed_size<storage_type>::value, "invalid size tag");

  /* Array size: */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == 4, "invalid quaternion size");

  /* Order and cross taken from the sub-expression: */
  using order_type = typename left_traits::order_type;
  using cross_type = typename left_traits::cross_type;
};

/** Represents a binary quaternion operation, where one operand is a scalar
 * value, and the other is a quaternion.
 */
template<class Sub, class Scalar, class Op>
class quaternion_scalar_node
: public readable_quaternion<quaternion_scalar_node<Sub, Scalar, Op>>
{
  public:
  using node_type = quaternion_scalar_node<Sub, Scalar, Op>;
  using readable_type = readable_quaternion<node_type>;
  using traits_type = quaternion_traits<node_type>;
  using left_arg_type = typename traits_type::left_arg_type;
  using right_arg_type = typename traits_type::right_arg_type;
  using left_type = typename traits_type::left_type;
  using right_type = typename traits_type::right_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;
  using order_type = typename traits_type::order_type;
  using cross_type = typename traits_type::cross_type;


  public:
  /** The array size constant is the same as the subexpression. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expression and the scalar to apply.
   * @c left must be an lvalue reference or rvalue reference.
   */
  quaternion_scalar_node(Sub left, const right_type& right);

  /** Move constructor. */
  quaternion_scalar_node(node_type&& other);

  /** Copy constructor. */
  quaternion_scalar_node(const node_type& other);


  protected:
  /** @name readable_quaternion Interface */
  /*@{*/

  friend readable_type;

  /** Apply the scalar operator to element @c i of the subexpression and
   * return the result.
   */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the left subexpression.  The expression is
   * stored as a copy if Sub is an rvalue reference (temporary), or by
   * const reference if Sub is an lvalue reference.
   */
  using left_wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const left_type&,
    left_type>;


  protected:
  /** The quaternion operand. */
  left_wrap_type m_left;

  /** The scalar operand. */
  right_type m_right;


  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_QUATERNION_SCALAR_NODE_TPP
#include <cml/quaternion/scalar_node.tpp>
#undef __CML_QUATERNION_SCALAR_NODE_TPP
