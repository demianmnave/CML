/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_binary_node_h
#define	cml_vector_binary_node_h

#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub1, class Sub2, class Op> class vector_binary_node;

/** vector_binary_node<> traits. */
template<class Sub1, class Sub2, class Op>
struct vector_traits< vector_binary_node<Sub1,Sub2,Op> >
{
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
};

/** Represents a binary vector operation in an expression tree. */
template<class Sub1, class Sub2, class Op>
class vector_binary_node
: public readable_vector< vector_binary_node<Sub1,Sub2,Op> >
{
  public:

    typedef vector_binary_node<Sub1,Sub2,Op>	node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    /** Construct from the wrapped sub-expressions, derived from
     * readable_vector<>.
     */
     vector_binary_node(const readable_vector<Sub1>& sub1,
       const readable_vector<Sub2>& sub2);


  public:

    /** Return the size of the vector expression. */
    int size() const;

    /** Apply the operator to element @c i of the subexpressions and return
     * the result.
     */
    immutable_value get(int i) const;


  protected:

    /** The wrapped left subexpression. */
    const Sub1&			m_sub1;

    /** The wrapped right subexpression. */
    const Sub2&			m_sub2;
};

} // namespace cml

#define __CML_VECTOR_BINARY_NODE_TPP
#include <cml/vector/binary_node.tpp>
#undef __CML_VECTOR_BINARY_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
