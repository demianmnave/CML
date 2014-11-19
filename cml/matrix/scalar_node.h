/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_scalar_node_h
#define	cml_matrix_scalar_node_h

#include <cml/common/mpl/type_util.h>
#include <cml/common/mpl/if_t.h>
#include <cml/common/scalar_traits.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

template<class Sub, class Scalar, class Op> class matrix_scalar_node;

/** matrix_scalar_node<> traits. */
template<class Sub, class Scalar, class Op>
struct matrix_traits< matrix_scalar_node<Sub,Scalar,Op> >
{
  /* Figure out the basic types of Sub and Scalar: */
  typedef Sub						left_arg_type;
  typedef Scalar 					right_arg_type;
  typedef cml::unqualified_type_t<Sub>			left_type;
  typedef matrix_traits<left_type>			left_traits;
  typedef cml::unqualified_type_t<Scalar>		right_type;
  typedef scalar_traits<typename Op::result_type>	element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef typename left_traits::size_tag		size_tag;
  typedef typename left_traits::temporary_type		temporary_type;
};

/** Represents a binary matrix operation, where one operand is a scalar
 * value, and the other is a matrix.
 */
template<class Sub, class Scalar, class Op>
class matrix_scalar_node
: public readable_matrix< matrix_scalar_node<Sub,Scalar,Op> >
{
  public:

    typedef matrix_scalar_node<Sub,Scalar,Op>		node_type;
    typedef matrix_traits<node_type>			traits_type;
    typedef typename traits_type::left_arg_type		left_arg_type;
    typedef typename traits_type::right_arg_type	right_arg_type;
    typedef typename traits_type::left_type		left_type;
    typedef typename traits_type::right_type		right_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /** Take the array row size from the subexpression. */
    static const int array_rows = left_type::array_rows;

    /** Take the array column size from the subexpression. */
    static const int array_cols = left_type::array_cols;


  public:

    /** Construct from the wrapped sub-expression and the scalar to apply.
     * @c sub must be an lvalue reference or rvalue reference.
     */
    matrix_scalar_node(Sub left, const right_type& right);

    /** Move constructor. */
    matrix_scalar_node(node_type&& other);


  public:

    /** Return the row size of the matrix expression. */
    int rows() const;

    /** Return the column size of the matrix expression. */
    int cols() const;

    /** Apply the scalar operator to element @c (i,j) of the subexpressions
     * and return the result.
     */
    immutable_value get(int i, int j) const;


  protected:

    /** The type used to store the left subexpression.  The expression is
     * stored as a copy if Sub is an rvalue reference (temporary), or by
     * const reference if Sub is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub>::value,
	    left_type, const left_type&>		left_wrap_type;


  protected:

    /** The matrix operand. */
    left_wrap_type		m_left;

    /** The read-only scalar operand. */
    const right_type		m_right;


  private:

    // Not copy constructible.
    matrix_scalar_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_MATRIX_SCALAR_NODE_TPP
#include <cml/matrix/scalar_node.tpp>
#undef __CML_MATRIX_SCALAR_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
