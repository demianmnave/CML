/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/resize.h>
#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {
template<class Sub1, class Sub2> class outer_product_node;

/** outer_product_node<> traits. */
template<class Sub1, class Sub2>
struct matrix_traits<outer_product_node<Sub1, Sub2>>
{
  using matrix_type = outer_product_node<Sub1, Sub2>;
  using left_arg_type = Sub1;
  using right_arg_type = Sub2;
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = vector_traits<left_type>;
  using right_traits = vector_traits<right_type>;

  /* Deduce the element type: */
  using element_traits = scalar_traits<value_type_promote_t<left_traits,
    right_traits>>;
  using value_type = typename element_traits::value_type;
  using immutable_value = value_type;

  /* Determine the common storage type for the node, based on the storage
   * types of its subexpressions:
   */
  using left_storage_type = storage_type_of_t<left_traits>;
  using right_storage_type = storage_type_of_t<right_traits>;
  using storage_type = matrix_outer_product_storage_promote_t<left_storage_type,
    right_storage_type>;

  /* Traits and types for the storage: */
  using size_tag = typename storage_type::size_tag;

  /* Array rows: */
  static const int array_rows = storage_type::array_rows;

  /* Array cols: */
  static const int array_cols = storage_type::array_cols;

  /* Unspecified basis: */
  using basis_tag = any_basis;

  /* Unspecified layout: */
  using layout_tag = any_major;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;
};

/** Represents a vector outer product in an expression tree. */
template<class Sub1, class Sub2>
class outer_product_node
  : public readable_matrix<outer_product_node<Sub1, Sub2>>
{
  public:
  using node_type = outer_product_node<Sub1, Sub2>;
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
  outer_product_node(Sub1 left, Sub2 right);

  /** Move constructor. */
  outer_product_node(node_type&& other);

  /** Copy constructor. */
  outer_product_node(const node_type& other);

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
  using left_wrap_type = cml::if_t<std::is_lvalue_reference<Sub1>::value, const
    left_type&,
    left_type>;

  /** The type used to store the right subexpression.  The expression is
   * stored as a copy if Sub2 is an rvalue reference (temporary), or by
   * const reference if Sub2 is an lvalue reference.
   */
  using right_wrap_type = cml::if_t<std::is_lvalue_reference<Sub2>::value, const
    right_type&,
    right_type>;

  protected:
  /** The wrapped left subexpression. */
  left_wrap_type m_left;

  /** The wrapped right subexpression. */
  right_wrap_type m_right;

  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};
} // namespace cml

#define __CML_VECTOR_OUTER_PRODUCT_NODE_TPP
#include <cml/vector/outer_product_node.tpp>
#undef __CML_VECTOR_OUTER_PRODUCT_NODE_TPP
