/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/quaternion/readable_quaternion.h>

namespace cml {

template<class Sub> class inverse_node;

/** inverse_node<> traits. */
template<class Sub> struct quaternion_traits<inverse_node<Sub>>
{
  /* Figure out the basic type of Sub: */
  using quaternion_type = inverse_node<Sub>;
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

/** Represents the inverse of a quaternion subexpression. */
template<class Sub>
class inverse_node : public readable_quaternion<inverse_node<Sub>>
{
  public:
  using node_type = inverse_node<Sub>;
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
  explicit inverse_node(Sub sub);

  /** Move constructor. */
  inverse_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  inverse_node(const node_type& other);
#endif


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

  /** The reciprocal of the subexpression norm. */
  value_type m_inv_norm;


  private:
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  // Not copy constructible.
  inverse_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_QUATERNION_INVERSE_NODE_TPP
#include <cml/quaternion/inverse_node.tpp>
#undef __CML_QUATERNION_INVERSE_NODE_TPP
