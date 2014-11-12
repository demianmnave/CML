/* -*- C++ -*- ------------------------------------------------------------ @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_subvector_node_h
#define	cml_subvector_node_h

#include <cml/common/mpl/if_t.h>
#include <cml/vector/readable_vector.h>

namespace cml {

template<class Sub> class subvector_node;

/** subvector_node<> traits. */
template<class Sub>
struct vector_traits< subvector_node<Sub> >
{
  /* Figure out the basic type of Sub: */
  typedef Sub						sub_arg_type;
  typedef cml::unqualified_type_t<Sub>			sub_type;
  typedef vector_traits<sub_type>			sub_traits;
  typedef typename sub_traits::element_traits		element_traits;
  typedef typename sub_traits::value_type		value_type;
  typedef typename sub_traits::immutable_value 		immutable_value;
  typedef typename sub_traits::size_tag			size_tag;
  typedef typename sub_traits::temporary_type		temporary_type;
};

/** Represents an N-1 subvector operation in an expression tree, where N is
 * the length of the wrapped subexpression.
 */
template<class Sub>
class subvector_node
: public readable_vector< subvector_node<Sub> >
{
  public:

    typedef subvector_node<Sub>				node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::sub_arg_type		sub_arg_type;
    typedef typename traits_type::sub_type		sub_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /** The array size constant depends upon the subexpression size. */
    static const int array_size
      = (sub_type::array_size > 0) ? (sub_type::array_size - 1) : -1;


  public:

    /** Construct from the wrapped sub-expression and the element to drop.
     * @c sub must be an lvalue reference or rvalue reference.
     */
    explicit subvector_node(Sub sub, int skip);

    /** Move constructor. */
    subvector_node(node_type&& other);


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

    /** The element to skip. */
    int				m_skip;


  private:

    // Not copy constructible.
    subvector_node(const node_type&);

    // Not assignable.
    node_type& operator=(const node_type&);
};

} // namespace cml

#define __CML_VECTOR_SUBVECTOR_NODE_TPP
#include <cml/vector/subvector_node.tpp>
#undef __CML_VECTOR_SUBVECTOR_NODE_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
