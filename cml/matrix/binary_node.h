/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {

template<class Sub1, class Sub2, class Op> class matrix_binary_node;

/** matrix_binary_node<> traits. */
template<class Sub1, class Sub2, class Op>
struct matrix_traits<matrix_binary_node<Sub1, Sub2, Op>>
{
  using matrix_type = matrix_binary_node<Sub1, Sub2, Op>;
  using left_arg_type = Sub1;
  using right_arg_type = Sub2;
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = matrix_traits<left_type>;
  using right_traits = matrix_traits<right_type>;
  using element_traits = scalar_traits<typename Op::result_type>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;

  /* Determine the common storage type for the node, based on the storage
   * types of its subexpressions:
   */
  using storage_type = matrix_binary_storage_promote_t<storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>;

  /* Traits and types for the storage: */
  using size_tag = typename storage_type::size_tag;

  /* Array rows: */
  static const int array_rows = storage_type::array_rows;

  /* Array cols: */
  static const int array_cols = storage_type::array_cols;

  /* Determine the common basis type: */
  using basis_tag = basis_tag_promote_t<basis_tag_of_t<left_traits>,
    basis_tag_of_t<right_traits>>;

  /* Determine the common layout type: */
  using layout_tag = layout_tag_promote_t<layout_tag_of_t<left_traits>,
    layout_tag_of_t<right_traits>>;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;
};

/** Represents a binary matrix operation in an expression tree. */
template<class Sub1, class Sub2, class Op>
class matrix_binary_node
: public readable_matrix<matrix_binary_node<Sub1, Sub2, Op>>
{
  public:
  using node_type = matrix_binary_node<Sub1, Sub2, Op>;
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
  /** Constant containing the number of rows. */
  static const int array_rows = traits_type::array_rows;

  /** Constant containing the number of columns. */
  static const int array_cols = traits_type::array_cols;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = traits_type::array_layout;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = traits_type::matrix_basis;


  public:
  /** Construct from the wrapped sub-expressions.  Sub1 and Sub2 must be
     * lvalue reference or rvalue reference types.
     *
     * @throws incompatible_matrix_sizes at run-time if either Sub1 or Sub2
     * is a dynamically-sized matrix, and sub1.size() != sub2.size().  If
     * both Sub1 and Sub2 are fixed-size expressions, then the sizes are
     * checked at compile time.
     */
  matrix_binary_node(Sub1 left, Sub2 right);

  /** Move constructor. */
  matrix_binary_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  matrix_binary_node(const node_type& other);
#endif


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
  matrix_binary_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_MATRIX_BINARY_NODE_TPP
#include <cml/matrix/binary_node.tpp>
#undef __CML_MATRIX_BINARY_NODE_TPP
