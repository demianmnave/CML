/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_binary_node_h
#define	cml_matrix_binary_node_h

#include <cml/common/scalar_traits.h>
#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {

template<class Sub1, class Sub2, class Op> class matrix_binary_node;

/** matrix_binary_node<> traits. */
template<class Sub1, class Sub2, class Op>
struct matrix_traits< matrix_binary_node<Sub1,Sub2,Op> >
{
  typedef Sub1						left_arg_type;
  typedef Sub2						right_arg_type;
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;
  typedef scalar_traits<typename Op::result_type>	element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef matrix_size_tag_promote_t<
    left_type, right_type>				size_tag;
  typedef matrix_basis_tag_promote_t<
    left_type,right_type>				basis_tag;
  typedef matrix_layout_tag_promote_t<
    left_type,right_type>				layout_tag;
  typedef matrix_temporary_promote_t<
    left_type, right_type, value_type>			temporary_type;
};

/** Represents a binary matrix operation in an expression tree. */
template<class Sub1, class Sub2, class Op>
class matrix_binary_node
: public readable_matrix< matrix_binary_node<Sub1,Sub2,Op> >
{
  public:

    typedef matrix_binary_node<Sub1,Sub2,Op>		node_type;
    typedef matrix_traits<node_type>			traits_type;
    typedef typename traits_type::left_arg_type		left_arg_type;
    typedef typename traits_type::right_arg_type	right_arg_type;
    typedef typename traits_type::left_type		left_type;
    typedef typename traits_type::right_type		right_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::basis_tag		basis_tag;
    typedef typename traits_type::layout_tag		layout_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /** Deduce the array row size constant from the larger of the
     * subexpression sizes.
     */
    static const int array_rows
      = left_type::array_rows > right_type::array_rows
      ? left_type::array_rows : right_type::array_rows;

    /** Deduce the array column size constant from the larger of the
     * subexpression sizes.
     */
    static const int array_cols
      = left_type::array_cols > right_type::array_cols
      ? left_type::array_cols : right_type::array_cols;


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


  public:

    /** Return the row size of the matrix expression. */
    int rows() const;

    /** Return the column size of the matrix expression. */
    int cols() const;

    /** Apply the operator to element @c (i,j) of the subexpressions and
     * return the result.
     */
    immutable_value get(int i, int j) const;


  protected:

    /** The type used to store the left subexpression.  The expression is
     * stored as a copy if Sub1 is an rvalue reference (temporary), or by
     * const reference if Sub1 is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub1>::value,
	    left_type, const left_type&>		left_wrap_type;

    /** The type used to store the right subexpression.  The expression is
     * stored as a copy if Sub2 is an rvalue reference (temporary), or by
     * const reference if Sub2 is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub2>::value,
	    right_type, const right_type&>		right_wrap_type;


  protected:

    /** The wrapped left subexpression. */
    left_wrap_type		m_left;

    /** The wrapped right subexpression. */
    right_wrap_type		m_right;


  private:

    // Not copy constructible.
    matrix_binary_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_MATRIX_BINARY_NODE_TPP
#include <cml/matrix/binary_node.tpp>
#undef __CML_MATRIX_BINARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
