/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>
#include <cml/vector/promotion.h>

namespace cml {

template<class Sub1, class Sub2> class vector_cross_node;

/** vector_cross_node<> traits. */
template<class Sub1, class Sub2>
struct vector_traits<vector_cross_node<Sub1, Sub2>>
{
  using vector_type = vector_cross_node<Sub1, Sub2>;
  using left_arg_type = Sub1;
  using right_arg_type = Sub2;
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = vector_traits<left_type>;
  using right_traits = vector_traits<right_type>;

  using element_type = value_type_promote_t<left_traits, right_traits>;
  using element_traits = scalar_traits<element_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;

  /* Determine the common storage type for the node, based on the storage
   * types of its subexpressions:
   */
  using storage_type = vector_binary_storage_promote_t<storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>;

  /* Traits and types for the storage: */
  using size_tag = typename storage_type::size_tag;

  /* Array size: */
  static const int array_size = storage_type::array_size;
};

/** Represents a cross product in an expression tree. */
template<class Sub1, class Sub2>
class vector_cross_node : public readable_vector<vector_cross_node<Sub1, Sub2>>
{
  public:
  using node_type = vector_cross_node<Sub1, Sub2>;
  using readable_type = readable_vector<node_type>;
  using traits_type = vector_traits<node_type>;
  using left_arg_type = typename traits_type::left_arg_type;
  using right_arg_type = typename traits_type::right_arg_type;
  using left_type = typename traits_type::left_type;
  using right_type = typename traits_type::right_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;


  public:
  /** Constant containing the array size. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expressions.  Sub1 and Sub2 must be
     * lvalue reference or rvalue reference types.
     *
     * @throws vector_size_error at run-time if either Sub1 or Sub2 is a
     * dynamically-sized vector, and sub1.size() != sub2.size() != 3.  If
     * both Sub1 and Sub2 are fixed-size expressions, then the sizes are
     * checked at compile time.
     */
  vector_cross_node(Sub1 left, Sub2 right);

  /** Move constructor. */
  vector_cross_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  vector_cross_node(const node_type& other);
#endif


  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the size of the vector expression. */
  int i_size() const;

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
  vector_cross_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_VECTOR_CROSS_NODE_TPP
#include <cml/vector/cross_node.tpp>
#undef __CML_VECTOR_CROSS_NODE_TPP
