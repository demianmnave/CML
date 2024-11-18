/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub, class Scalar, class Op> class vector_scalar_node;

/** vector_scalar_node<> traits. */
template<class Sub, class Scalar, class Op>
struct vector_traits<vector_scalar_node<Sub, Scalar, Op>>
{
  /* Figure out the basic types of Sub and Scalar: */
  using vector_type = vector_scalar_node<Sub, Scalar, Op>;
  using left_arg_type = Sub;
  using right_arg_type = Scalar;
  using left_type = cml::unqualified_type_t<Sub>;
  using right_type = cml::unqualified_type_t<Scalar>;
  using left_traits = vector_traits<left_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;
  using storage_type = typename left_traits::storage_type;
  using size_tag = typename left_traits::size_tag;

  /* Propagate the array size from the subexpression: */
  static const int array_size = left_traits::array_size;
};

/** Represents a binary vector operation, where one operand is a scalar
 * value, and the other is a vector.
 */
template<class Sub, class Scalar, class Op>
class vector_scalar_node
: public readable_vector<vector_scalar_node<Sub, Scalar, Op>>
{
  public:
  using node_type = vector_scalar_node<Sub, Scalar, Op>;
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
  /** The array size constant is the same as the subexpression. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expression and the scalar to apply.
     * @c left must be an lvalue reference or rvalue reference.
     */
  vector_scalar_node(Sub left, const right_type& right);

  /** Move constructor. */
  vector_scalar_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  vector_scalar_node(const node_type& other);
#endif


  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the size of the vector expression. */
  int i_size() const;

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
  /** The vector operand. */
  left_wrap_type m_left;

  /** The scalar operand. */
  right_type m_right;


  private:
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  // Not copy constructible.
  vector_scalar_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_VECTOR_SCALAR_NODE_TPP
#include <cml/vector/scalar_node.tpp>
#undef __CML_VECTOR_SCALAR_NODE_TPP
