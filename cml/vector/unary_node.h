/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_unary_node_h
#define	cml_vector_unary_node_h

#include <cml/vector/readable_vector.h>

namespace cml {

template<class SubNode, class Op> class vector_unary_node;

/** vector_unary_node<> traits. */
template<class SubNode, class Op>
struct vector_traits< vector_unary_node<SubNode,Op> >
{
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
};

/** Represents a unary vector operation in an expression tree. */
template<class SubNode, class Op>
class vector_unary_node
: public readable_vector< vector_unary_node<SubNode,Op> >
{
  public:

    typedef vector_unary_node<SubNode,Op>		node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    /** Construct from the wrapped sub-expression, derived from
     * readable_vector<>.
     */
    explicit vector_unary_node(const readable_vector<SubNode>& sub);


  public:

    /** Return the size of the vector expression. */
    int size() const;

    /** Apply the operator to element @c i and return the result. */
    immutable_value get(int i) const;


  protected:

    /** The wrapped subexpression. */
    const SubNode&		m_sub;
};

} // namespace cml

#define __CML_VECTOR_UNARY_NODE_TPP
#include <cml/vector/unary_node.tpp>
#undef __CML_VECTOR_UNARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
