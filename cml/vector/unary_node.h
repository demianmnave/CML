/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub, class Op> class vector_unary_node;

/** vector_unary_node<> traits. */
template<class Sub, class Op> struct vector_traits<vector_unary_node<Sub, Op>>
{
  using vector_type = vector_unary_node<Sub, Op>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = vector_traits<sub_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;
  using storage_type = typename sub_traits::storage_type;
  using size_tag = typename sub_traits::size_tag;

  /* Propagate the array size from the subexpression: */
  static const int array_size = sub_traits::array_size;
};

/** Represents a unary vector operation in an expression tree. */
template<class Sub, class Op>
class vector_unary_node : public readable_vector<vector_unary_node<Sub, Op>>
{
  public:
  using node_type = vector_unary_node<Sub, Op>;
  using readable_type = readable_vector<node_type>;
  using traits_type = vector_traits<node_type>;
  using sub_arg_type = typename traits_type::sub_arg_type;
  using sub_type = typename traits_type::sub_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;


  public:
  /** The array size constant is the same as the subexpression. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expression.  @c sub must be an
   * lvalue reference or rvalue reference.
   */
  explicit vector_unary_node(Sub sub);

  /** Move constructor. */
  vector_unary_node(node_type&& other);

  /** Copy constructor. */
  vector_unary_node(const node_type& other);


  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the size of the vector expression. */
  int i_size() const;

  /** Apply the operator to element @c i and return the result. */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
   * as a copy if Sub is an rvalue reference (temporary), or by const
   * reference if Sub is an lvalue reference.
   */
  using sub_wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const sub_type&,
    sub_type>;

  /** The wrapped subexpression. */
  sub_wrap_type m_sub;


  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_VECTOR_UNARY_NODE_TPP
#include <cml/vector/unary_node.tpp>
#undef __CML_VECTOR_UNARY_NODE_TPP
