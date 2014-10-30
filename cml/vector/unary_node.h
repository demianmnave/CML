/* -*- C++ -*- ------------------------------------------------------------ @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_unary_node_h
#define	cml_vector_unary_node_h

#include <cml/common/mpl/if_t.h>
#include <cml/common/size_tags.h>
#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub, class Op> class vector_unary_node;

/** vector_unary_node<> traits. */
template<class Sub, class Op>
struct vector_traits< vector_unary_node<Sub,Op> >
{
  /* Figure out the basic type of Sub: */
  typedef cml::unqualified_type_t<Sub>			sub_type;
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
  typedef typename sub_type::size_tag			size_tag;
};

/** Represents a unary vector operation in an expression tree. */
template<class Sub, class Op>
class vector_unary_node
: public readable_vector< vector_unary_node<Sub,Op> >
{
  public:

    typedef vector_unary_node<Sub,Op>			node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::sub_type		sub_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;


  public:

    /** The array size constant is the same as the subexpression. */
    static const int array_size = sub_type::array_size;


  public:

    /** Construct from the wrapped sub-expression.  @c sub must be an
     * lvalue reference or rvalue reference.
     */
    explicit vector_unary_node(Sub sub);

    /** Move constructor. */
    vector_unary_node(node_type&& other);


  public:

    /** Return the size of the vector expression. */
    int size() const;

    /** Apply the operator to element @c i and return the result. */
    immutable_value get(int i) const;


  protected:

    /** The type used to store the subexpression.  The expression is stored
     * as a copy if Sub is an rvalue reference (temporary), or by const
     * reference if Sub is an lvalue reference.
     */
    typedef cml::if_t<std::is_rvalue_reference<Sub>::value,
	    sub_type, const sub_type&>			wrap_type;

    /** The wrapped subexpression. */
    wrap_type			m_sub;


  private:

    // Not copyable constructible.
    vector_unary_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_VECTOR_UNARY_NODE_TPP
#include <cml/vector/unary_node.tpp>
#undef __CML_VECTOR_UNARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
