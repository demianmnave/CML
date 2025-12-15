/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/traits.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {
template<class Sub> class matrix_transpose_node;

/** matrix_transpose_node<> traits. */
template<class Sub> struct matrix_traits<matrix_transpose_node<Sub>>
{
  using matrix_type = matrix_transpose_node<Sub>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = matrix_traits<sub_type>;
  using element_traits = typename sub_traits::element_traits;
  using value_type = typename sub_traits::value_type;
  using immutable_value = typename sub_traits::immutable_value;
  using storage_type = typename sub_traits::storage_type;
  using size_tag = typename sub_traits::size_tag;
  using basis_tag = typename sub_traits::basis_tag;
  using layout_tag = typename sub_traits::layout_tag;

#if 0
  /* Flip the layout: */
  typedef typename sub_traits::layout_tag sub_layout;
  typedef typename sub_layout::transposed_tag layout_tag;
#endif

  /* Propagate the rows from the subexpression: */
  static const int array_rows = sub_traits::array_cols;

  /* Propagate the columns from the subexpression: */
  static const int array_cols = sub_traits::array_rows;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;
};

/** Represents a transpose matrix operation in an expression tree. */
template<class Sub>
class matrix_transpose_node : public readable_matrix<matrix_transpose_node<Sub>>
{
  public:
  using node_type = matrix_transpose_node<Sub>;
  using readable_type = readable_matrix<node_type>;
  using traits_type = matrix_traits<node_type>;
  using sub_arg_type = typename traits_type::sub_arg_type;
  using sub_type = typename traits_type::sub_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;

  public:
  /** Constant containing the number of rows. */
  static const int array_rows = traits_type::array_rows;

  /** Constant containing the number of columns. */
  static const int array_cols = traits_type::array_cols;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = traits_type::matrix_basis;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = traits_type::array_layout;

  public:
  /** Construct from the wrapped sub-expression.  @c sub must be an
   * lvalue reference or rvalue reference type.
   */
  matrix_transpose_node(Sub sub);

  /** Move constructor. */
  matrix_transpose_node(node_type&& other);

  /** Copy constructor. */
  matrix_transpose_node(const node_type& other);

  protected:
  /** @name readable_matrix Interface */
  /*@{*/

  friend readable_type;

  /** Return the row size of the transposed matrix expression. */
  int i_rows() const;

  /** Return the column size of the transposed matrix expression. */
  int i_cols() const;

  /** Return element @c (j,i) of the subexpression. */
  immutable_value i_get(int i, int j) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
   * as a copy if Sub is an rvalue reference (temporary), or by const
   * reference if Sub is an lvalue reference.
   */
  using sub_wrap_type = cml::if_t<std::is_lvalue_reference_v<Sub>, const
    sub_type&,
    sub_type>;

  protected:
  /** The wrapped subexpression. */
  sub_wrap_type m_sub;

  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};
} // namespace cml

#define __CML_MATRIX_TRANSPOSE_NODE_TPP
#include <cml/matrix/transpose_node.tpp>
#undef __CML_MATRIX_TRANSPOSE_NODE_TPP
