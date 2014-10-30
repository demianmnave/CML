/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_binary_node_h
#define	cml_vector_binary_node_h

#include <cml/vector/readable_vector.h>
#include <cml/vector/promotion.h>

namespace cml {

template<class Sub1, class Sub2, class Op> class vector_binary_node;

/** vector_binary_node<> traits. */
template<class Sub1, class Sub2, class Op>
struct vector_traits< vector_binary_node<Sub1,Sub2,Op> >
{
  /* Figure out the basic types of Sub1 and Sub2: */
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;

  /* Figure out the scalar type: */
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;

  /* Figure out the size type of the resulting expression: */
  typedef typename left_type::size_tag			left_size_tag;
  typedef typename right_type::size_tag			right_size_tag;
  typedef typename vector_size_tag_promote<
    left_size_tag, right_size_tag>::size_tag		size_tag;
};

/** Represents a binary vector operation in an expression tree. */
template<class Sub1, class Sub2, class Op>
class vector_binary_node
: public readable_vector< vector_binary_node<Sub1,Sub2,Op> >
{
  public:

    typedef vector_binary_node<Sub1,Sub2,Op>		node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::left_type		left_type;
    typedef typename traits_type::right_type		right_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;


  public:

    /** Deduce the array size constant from the larger of the subexpression
     * sizes.
     */
    static const int array_size
      = left_type::array_size > right_type::array_size
      ? left_type::array_size : right_type::array_size;


  public:

    /** Construct from the wrapped sub-expressions.  Sub1 and Sub2 must be
     * lvalue reference or rvalue reference types.
     */
    vector_binary_node(Sub1 left, Sub2 right);

    /** Move constructor. */
    vector_binary_node(node_type&& other);


  public:

    /** Return the size of the vector expression. */
    int size() const;

    /** Apply the operator to element @c i of the subexpressions and return
     * the result.
     */
    immutable_value get(int i) const;


  protected:

    /** The type used to store the left subexpression.  The expression is
     * stored as a copy if Sub is an rvalue reference (temporary), or by
     * const reference if Sub is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub1>::value,
	    left_type, const left_type&>		left_wrap_type;

    /** The type used to store the right subexpression.  The expression is
     * stored as a copy if Sub is an rvalue reference (temporary), or by
     * const reference if Sub is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub2>::value,
	    right_type, const right_type&>		right_wrap_type;


  protected:

    /** The wrapped left subexpression. */
    left_wrap_type		m_left;

    /** The wrapped right subexpression. */
    right_wrap_type		m_right;


  private:

    // Not copyable constructible.
    vector_binary_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_VECTOR_BINARY_NODE_TPP
#include <cml/vector/binary_node.tpp>
#undef __CML_VECTOR_BINARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
