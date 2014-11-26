/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_unary_node_h
#define	cml_matrix_unary_node_h

#include <cml/common/mpl/if_t.h>
#include <cml/common/type_util.h>
#include <cml/common/scalar_traits.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

template<class Sub, class Op> class matrix_unary_node;

/** matrix_unary_node<> traits. */
template<class Sub, class Op>
struct matrix_traits< matrix_unary_node<Sub,Op> >
{
  typedef matrix_unary_node<Sub,Op>			node_type;
  typedef matrix_traits<node_type>			traits_type;
  typedef Sub						sub_arg_type;
  typedef cml::unqualified_type_t<Sub>			sub_type;
  typedef matrix_traits<sub_type>			sub_traits;
  typedef scalar_traits<typename Op::result_type>	element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef typename sub_traits::size_tag			size_tag;
  typedef typename sub_traits::basis_tag		basis_tag;
  typedef typename sub_traits::layout_tag		layout_tag;
  typedef typename sub_traits::temporary_type		temporary_type;
};

/** Represents a unary matrix operation in an expression tree. */
template<class Sub, class Op>
class matrix_unary_node
: public readable_matrix< matrix_unary_node<Sub,Op> >
{
  public:

    typedef matrix_unary_node<Sub,Op>			node_type;
    typedef matrix_traits<node_type>			traits_type;
    typedef typename traits_type::sub_arg_type		sub_arg_type;
    typedef typename traits_type::sub_type		sub_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::basis_tag		basis_tag;
    typedef typename traits_type::layout_tag		layout_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /** Take the array row size from the subexpression. */
    static const int array_rows = sub_type::array_rows;

    /** Take the array column size from the subexpression. */
    static const int array_cols = sub_type::array_cols;


  public:

    /** Construct from the wrapped sub-expression.  @c sub must be an
     * lvalue reference or rvalue reference type.
     */
    matrix_unary_node(Sub sub);

    /** Move constructor. */
    matrix_unary_node(node_type&& other);


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

    /** The type used to store the subexpression.  The expression is stored
     * as a copy if Sub is an rvalue reference (temporary), or by const
     * reference if Sub is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub>::value,
	    sub_type, const sub_type&>			sub_wrap_type;


  protected:

    /** The wrapped subexpression. */
    sub_wrap_type		m_sub;


  private:

    // Not copy constructible.
    matrix_unary_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_MATRIX_UNARY_NODE_TPP
#include <cml/matrix/unary_node.tpp>
#undef __CML_MATRIX_UNARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
