/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/quaternion/readable_quaternion.h>
#include <cml/quaternion/promotion.h>

namespace cml {

template<class Sub1, class Sub2, class Op> class quaternion_binary_node;

/** quaternion_binary_node<> traits. */
template<class Sub1, class Sub2, class Op>
struct quaternion_traits<quaternion_binary_node<Sub1, Sub2, Op>>
{
  using quaternion_type = quaternion_binary_node<Sub1, Sub2, Op>;
  using left_arg_type = Sub1;
  using right_arg_type = Sub2;
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = quaternion_traits<left_type>;
  using right_traits = quaternion_traits<right_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;

  /* Determine the common storage type for the node, based on the storage
   * types of its subexpressions:
   */
  using storage_type = quaternion_binary_storage_promote_t<storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>;
  using size_tag = typename storage_type::size_tag;
  static_assert(cml::is_fixed_size<storage_type>::value, "invalid size tag");

  /* Array size: */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == 4, "invalid quaternion size");

  /* Determine the common order type: */
  using order_type = order_type_promote_t<order_type_of_t<left_traits>,
    order_type_of_t<right_traits>>;

  /* Determine the common cross type: */
  using cross_type = cross_type_promote_t<cross_type_of_t<left_traits>,
    cross_type_of_t<right_traits>>;
};

/** Represents a binary quaternion operation in an expression tree. */
template<class Sub1, class Sub2, class Op>
class quaternion_binary_node
: public readable_quaternion<quaternion_binary_node<Sub1, Sub2, Op>>
{
  public:
  using node_type = quaternion_binary_node<Sub1, Sub2, Op>;
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
  /** Constant containing the array size. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expressions.  Sub1 and Sub2 must be
     * lvalue reference or rvalue reference types.
     *
     * @throws incompatible_quaternion_size_error at run-time if either Sub1 or
     * Sub2 is a dynamically-sized quaternion, and sub1.size() != sub2.size().
     * If both Sub1 and Sub2 are fixed-size expressions, then the sizes are
     * checked at compile time.
     */
  quaternion_binary_node(Sub1 left, Sub2 right);

  /** Move constructor. */
  quaternion_binary_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  quaternion_binary_node(const node_type& other);
#endif


  protected:
  /** @name readable_quaternion Interface */
  /*@{*/

  friend readable_type;

  /** Apply the operator to element @c i of the subexpressions and return
     * the result.
     */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the left subexpression.  The expression is
     * stored as a copy if Sub1 is an rvalue reference (temporary), or by
     * const reference if Sub1 is an lvalue reference.
     */
  using left_wrap_type = cml::if_t<std::is_lvalue_reference<Sub1>::value, const left_type&,
    left_type>;

  /** The type used to store the right subexpression.  The expression is
     * stored as a copy if Sub2 is an rvalue reference (temporary), or by
     * const reference if Sub2 is an lvalue reference.
     */
  using right_wrap_type = cml::if_t<std::is_lvalue_reference<Sub2>::value, const right_type&,
    right_type>;


  protected:
  /** The wrapped left subexpression. */
  left_wrap_type m_left;

  /** The wrapped right subexpression. */
  right_wrap_type m_right;


  private:
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  // Not copy constructible.
  quaternion_binary_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_QUATERNION_BINARY_NODE_TPP
#include <cml/quaternion/binary_node.tpp>
#undef __CML_QUATERNION_BINARY_NODE_TPP
