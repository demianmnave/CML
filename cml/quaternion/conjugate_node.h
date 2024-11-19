/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/quaternion/readable_quaternion.h>

namespace cml {

template<class Sub> class conjugate_node;

/** conjugate_node<> traits. */
template<class Sub> struct quaternion_traits<conjugate_node<Sub>>
{
  /* Figure out the basic type of Sub: */
  using quaternion_type = conjugate_node<Sub>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = quaternion_traits<sub_type>;
  using element_traits = scalar_traits<value_type_of_t<sub_traits>>;
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

/** Represents the conjugate of a quaternion subexpression. */
template<class Sub>
class conjugate_node : public readable_quaternion<conjugate_node<Sub>>
{
  public:
  using node_type = conjugate_node<Sub>;
  using readable_type = readable_quaternion<node_type>;
  using traits_type = quaternion_traits<node_type>;
  using sub_arg_type = typename traits_type::sub_arg_type;
  using sub_type = typename traits_type::sub_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;


  public:
  /** The array size constant depends upon the subexpression size. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped quaternion expression.  @c sub must be
   * an lvalue reference or rvalue reference.
   */
  explicit conjugate_node(Sub sub);

  /** Move constructor. */
  conjugate_node(node_type&& other);

  /** Copy constructor. */
  conjugate_node(const node_type& other);


  protected:
  /** @name readable_quaternion Interface */
  /*@{*/

  friend readable_type;

  /** Apply the operator to element @c i and return the result. */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
   * as a copy if Sub is an rvalue reference (temporary), or by const
   * reference if Sub is an lvalue reference.
   */
  using wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const sub_type&,
    sub_type>;

  /** The wrapped subexpression. */
  wrap_type m_sub;


  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_QUATERNION_CONJUGATE_NODE_TPP
#include <cml/quaternion/conjugate_node.tpp>
#undef __CML_QUATERNION_CONJUGATE_NODE_TPP
