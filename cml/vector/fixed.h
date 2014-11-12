/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_fixed_h
#define	cml_vector_fixed_h

#include <cml/common/fixed_selector.h>
#include <cml/common/size_tags.h>
#include <cml/common/scalar_traits.h>
#include <cml/vector/writable_vector.h>
#include <cml/vector/vector.h>

namespace cml {

template<class Element, int Size>
struct vector_traits< vector<Element, fixed<Size>> >
{
  typedef scalar_traits<Element>			element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::pointer		pointer;
  typedef typename element_traits::reference		reference;
  typedef typename element_traits::const_pointer	const_pointer;
  typedef typename element_traits::const_reference	const_reference;
  typedef typename element_traits::mutable_value	mutable_value;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef fixed_size_tag				size_tag;
  typedef vector<Element, fixed<Size>>			temporary_type;
};

/** Fixed-length vector.
 *
 * @note Fixed-length vectors must have at least 2 elements.
 */
template<class Element, int Size>
class vector<Element, fixed<Size>>
: public writable_vector< vector<Element, fixed<Size>> >
{
  static_assert(Size >= 2, "fixed vectors must have at least 2 elements");
  public:

    typedef vector<Element, fixed<Size>>		vector_type;
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
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /* Include methods from writable_type: */
    using writable_type::operator=;


  public:

    /** Constant containing the array size. */
    static const int array_size = Size;


  public:

    /** Compiler-default constructor.
     *
     * @note The vector elements are uninitialized.
     */
    vector() = default;

    /** Compiler-default destructor. */
    ~vector() = default;

    /** Compiler-default copy constructor. */
    vector(const vector_type& other) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    /** Compiler-default move constructor. */
    vector(vector_type&& other) = default;
#endif

    /** Construct from a readable_vector. */
    template<class Sub> vector(const readable_vector<Sub>& sub);

    /** Construct from at least 2 constant values. If the vector is longer
     * than the variable argument list, the remaining elements are set to
     * value_type(0).
     *
     * @note There must be fewer arguments than the vector size.  This is
     * enforced at compile time.
     */
    template<class... Elements>
      vector(const_reference e0, const Elements&... eN);

    /** Construct from a single constant value.  The remaining vector
     * elements are set to value_type(0).
     */
    explicit vector(const_reference e0);

    /** Construct from an array type. */
    template<class Array> vector(
      const Array& array, cml::enable_if_array_t<Array>* = 0);

    /** Construct from std::initializer_list. */
    template<class Other> vector(std::initializer_list<Other> l);


  public:

    /** Return the length of the vector. */
    int size() const;

    /** Return vector element @c i. */
    mutable_value get(int i);

    /** Return vector const element @c i. */
    immutable_value get(int i) const;

    /** Set element @c i. */
    template<class Other> vector_type& set(int i, const Other& v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set element @c i on a temporary. */
    template<class Other> vector_type&& set(int i, const Other& v) &&;
#endif

    /** Return access to the vector data as a raw pointer. */
    pointer data();

    /** Return const access to the vector data as a raw pointer. */
    const_pointer data() const;

    /** Read-only iterator. */
    const_pointer begin() const;

    /** Read-only iterator. */
    const_pointer end() const;


  protected:

    /** Fixed-length array. */
    value_type			m_data[Size];
};

} // namespace cml

#define __CML_VECTOR_FIXED_TPP
#include <cml/vector/fixed.tpp>
#undef __CML_VECTOR_FIXED_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
