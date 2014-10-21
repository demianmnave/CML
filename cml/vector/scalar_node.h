/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_scalar_node_h
#define	cml_vector_scalar_node_h

#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub, class Scalar, class Op> class vector_scalar_node;

/** vector_scalar_node<> traits. */
template<class Sub, class Scalar, class Op>
struct vector_traits< vector_scalar_node<Sub,Scalar,Op> >
{
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
};

/** Represents a binary vector operation, where one operand is a scalar
 * value, and the other is a vector.
 */
template<class Sub, class Scalar, class Op>
class vector_scalar_node
: public readable_vector< vector_scalar_node<Sub,Scalar,Op> >
{
  public:

    typedef vector_scalar_node<Sub,Scalar,Op>	node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    /** Construct from the wrapped sub-expression, derived from
     * readable_vector<>, and the scalar operand.
     */
    vector_scalar_node(const readable_vector<Sub>& sub, const Scalar& v);


  public:

    /** Return the size of the vector expression. */
    int size() const;

    /** Apply the scalar operator to element @c i of the subexpression and
     * return the result.
     */
    immutable_value get(int i) const;


  protected:

    /** The vector operand. */
    const Sub&			m_sub;

    /** The scalar operand. */
    const Scalar		m_v;
};

} // namespace cml

#define __CML_VECTOR_SCALAR_NODE_TPP
#include <cml/vector/scalar_node.tpp>
#undef __CML_VECTOR_SCALAR_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
