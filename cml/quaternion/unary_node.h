/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/size_tags.h>
#include <cml/quaternion/readable_quaternion.h>

namespace cml {
template<class Sub, class Op> class quaternion_unary_node;

/** quaternion_unary_node<> traits. */
template<class Sub, class Op>
struct quaternion_traits<quaternion_unary_node<Sub, Op>>
{
  /* Figure out the basic types of Sub: */
  using quaternion_type = quaternion_unary_node<Sub, Op>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = quaternion_traits<sub_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;
  using storage_type = typename sub_traits::storage_type;

  using size_tag = typename sub_traits::size_tag;
  static_assert(cml::is_fixed_size<storage_type>::value, "invalid size tag");

  /* Array size: */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == 4, "invalid quaternion size");

  /* Order and cross taken from the sub-expression: */
  using order_type = typename sub_traits::order_type;
  using cross_type = typename sub_traits::cross_type;
};

/** Represents a unary quaternion operation. */
template<class Sub, class Op>
class quaternion_unary_node
  : public readable_quaternion<quaternion_unary_node<Sub, Op>>
{
  public:
  using node_type = quaternion_unary_node<Sub, Op>;
  using readable_type = readable_quaternion<node_type>;
  using traits_type = quaternion_traits<node_type>;
  using sub_arg_type = typename traits_type::sub_arg_type;
  using sub_type = typename traits_type::sub_type;
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
  /** Construct from the wrapped sub-expression.  @c sub must be an
   * lvalue reference or rvalue reference.
   */
  quaternion_unary_node(Sub sub);

  /** Move constructor. */
  quaternion_unary_node(node_type&& other);

  /** Copy constructor. */
  quaternion_unary_node(const node_type& other);

  protected:
  /** @name readable_quaternion Interface */
  /*@{*/

  friend readable_type;

  /** Apply the unary operator to element @c i of the subexpression and
   * return the result.
   */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
   * as a copy if Sub is an rvalue reference (temporary), or by const
   * reference if Sub is an lvalue reference.
   */
  using sub_wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const
    sub_type&,
    sub_type>;

  protected:
  /** The subexpression. */
  sub_wrap_type m_sub;

  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};
} // namespace cml

#define __CML_QUATERNION_UNARY_NODE_TPP
#include <cml/quaternion/unary_node.tpp>
#undef __CML_QUATERNION_UNARY_NODE_TPP
