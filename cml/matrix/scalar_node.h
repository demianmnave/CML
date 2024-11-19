/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/traits.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

template<class Sub, class Scalar, class Op> class matrix_scalar_node;

/** matrix_scalar_node<> traits. */
template<class Sub, class Scalar, class Op>
struct matrix_traits<matrix_scalar_node<Sub, Scalar, Op>>
{
  using matrix_type = matrix_scalar_node<Sub, Scalar, Op>;
  using left_arg_type = Sub;
  using right_arg_type = Scalar;
  using left_type = cml::unqualified_type_t<Sub>;
  using right_type = cml::unqualified_type_t<Scalar>;
  using left_traits = matrix_traits<left_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;
  using storage_type = typename left_traits::storage_type;
  using size_tag = typename left_traits::size_tag;
  using basis_tag = typename left_traits::basis_tag;
  using layout_tag = typename left_traits::layout_tag;

  /* Propagate the rows from the subexpression: */
  static const int array_rows = left_traits::array_rows;

  /* Propagate the columns from the subexpression: */
  static const int array_cols = left_traits::array_cols;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;
};

/** Represents a binary matrix operation, where one operand is a scalar
 * value, and the other is a matrix.
 */
template<class Sub, class Scalar, class Op>
class matrix_scalar_node
: public readable_matrix<matrix_scalar_node<Sub, Scalar, Op>>
{
  public:
  using node_type = matrix_scalar_node<Sub, Scalar, Op>;
  using readable_type = readable_matrix<node_type>;
  using traits_type = matrix_traits<node_type>;
  using left_arg_type = typename traits_type::left_arg_type;
  using right_arg_type = typename traits_type::right_arg_type;
  using left_type = typename traits_type::left_type;
  using right_type = typename traits_type::right_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;


  public:
  /** Take the array row size from the subexpression. */
  static const int array_rows = left_type::array_rows;

  /** Take the array column size from the subexpression. */
  static const int array_cols = left_type::array_cols;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = traits_type::matrix_basis;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = traits_type::array_layout;


  public:
  /** Construct from the wrapped sub-expression and the scalar to apply.
   * @c left and @c right must be lvalue or rvalue references.
   */
  matrix_scalar_node(Sub left, Scalar right);

  /** Move constructor. */
  matrix_scalar_node(node_type&& other);

  /** Copy constructor. */
  matrix_scalar_node(const node_type& other);


  protected:
  /** @name readable_matrix Interface */
  /*@{*/

  friend readable_type;

  /** Return the row size of the matrix expression. */
  int i_rows() const;

  /** Return the column size of the matrix expression. */
  int i_cols() const;

  /** Apply the operator to element @c (i,j) of the subexpressions and
   * return the result.
   */
  immutable_value i_get(int i, int j) const;

  /*@}*/


  protected:
  /** The type used to store the left subexpression.  The expression is
   * stored as a copy if Sub is an rvalue reference (temporary), or by
   * const reference if Sub is an lvalue reference.
   */
  using left_wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const left_type&,
    left_type>;


  protected:
  /** The matrix operand. */
  left_wrap_type m_left;

  /** The scalar operand. */
  right_type m_right;


  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_MATRIX_SCALAR_NODE_TPP
#include <cml/matrix/scalar_node.tpp>
#undef __CML_MATRIX_SCALAR_NODE_TPP
