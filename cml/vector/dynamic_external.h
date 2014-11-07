/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_dynamic_external_h
#define	cml_vector_dynamic_external_h

#include <cml/common/scalar_traits.h>
#include <cml/common/external_selector.h>
#include <cml/vector/writable_vector.h>

namespace cml {

template<class Element>
struct vector_traits< vector<Element, external<>> >
{
  typedef scalar_traits<Element>			element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::pointer		pointer;
  typedef typename element_traits::reference		reference;
  typedef typename element_traits::const_pointer	const_pointer;
  typedef typename element_traits::const_reference	const_reference;
  typedef typename element_traits::mutable_value	mutable_value;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef dynamic_size_tag				size_tag;
};

/** Runtime-length wrapped array pointer as a vector. */
template<class Element>
class vector<Element, external<>>
: public writable_vector< vector<Element, external<>> >
{
  public:

    typedef vector<Element, external<>>			vector_type;
    typedef writable_vector<vector_type>		writable_type;
    typedef vector_traits<vector_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::pointer		pointer;
    typedef typename traits_type::reference		reference;
    typedef typename traits_type::const_pointer		const_pointer;
    typedef typename traits_type::const_reference	const_reference;
    typedef typename traits_type::mutable_value		mutable_value;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;


  public:

    /* Include methods from writable_type: */
    using writable_type::operator=;


  public:

    /** Constant containing the array size. */
    static const int array_size = -1;


  public:

    /** Construct from the wrapped pointer and size. */
    vector(pointer data, int size);

    /** Move constructor. */
    vector(vector_type&& other);


  public:

    /** Return the length of the vector. */
    int size() const;

    /** Return vector element @c i. */
    mutable_value get(int i);

    /** Return vector const element @c i. */
    immutable_value get(int i) const;

    /** Set vector element @c i. */
    template<class Other> vector_type& set(int i, const Other& v);

    /** Return access to the vector data as a raw pointer. */
    pointer data();

    /** Return const access to the vector data as a raw pointer. */
    const_pointer data() const;


  protected:

    /** Wrapped pointer. */
    pointer			m_data;

    /** Number of elements. */
    int				m_size;
};

} // namespace cml

#define __CML_VECTOR_DYNAMIC_EXTERNAL_TPP
#include <cml/vector/dynamic_external.tpp>
#undef __CML_VECTOR_DYNAMIC_EXTERNAL_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
