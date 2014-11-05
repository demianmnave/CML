/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_dynamic_h
#define	cml_vector_dynamic_h

#include <type_traits>
#include <cml/common/dynamic_selector.h>
#include <cml/vector/writable_vector.h>

namespace cml {

template<class Element, class Allocator>
struct vector_traits< vector<Element, dynamic<Allocator>> >
{
  typedef Element					value_type;
  typedef value_type*					pointer;
  typedef value_type&					reference;
  typedef value_type const*				const_pointer;
  typedef value_type const&				const_reference;
  typedef value_type&					mutable_value;
  typedef value_type const&				immutable_value;
  typedef dynamic_size_tag				size_tag;
};

/** Resizable vector. */
template<class Element, class Allocator>
class vector<Element, dynamic<Allocator>>
: public writable_vector< vector<Element, dynamic<Allocator>> >
{
  public:

    typedef vector<Element, dynamic<Allocator>>		vector_type;
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

    /** Default constructor.
     *
     * @note The vector has no elements.
     */
    vector();

    /** Construct given a size.
     *
     * @throws std::invalid_argument if size < 0.
     */
    explicit vector(int size);

    /** Copy constructor. */
    vector(const vector_type& other);

    /** Move constructor. */
    vector(vector_type&& other);

    /** Construct from a readable_vector. */
    template<class Sub> vector(const readable_vector<Sub>& sub);

    /** Construct from at least 2 constant values.  The vector is resized
     * to accomodate the number of elements passed.
     *
     * @note There must be fewer arguments than the vector size.  This is
     * enforced at compile time.
     */
    template<class... Elements>
      vector(immutable_value e0, const Elements&... eN);

    /** Construct a 2D vector from a single constant value @c e0 and
     * value_type(0).
     */
    explicit vector(immutable_value e0);

    /** Construct from an array type. */
    template<class Array> vector(
      const Array& array, cml::enable_if_array_t<Array>* = 0);

    /** Construct from std::initializer_list. */
    template<class Other> vector(std::initializer_list<Other> l);

    /** Destructor. */
    ~vector();


  public:

    /** Return the length of the vector. */
    int size() const;

    /** Return vector element @c i. */
    mutable_value get(int i);

    /** Return vector const element @c i. */
    immutable_value get(int i) const;

    /** Set vector element @c i. */
    vector_type& set(int i, immutable_value v);

    /** Return access to the vector data as a raw pointer. */
    pointer data();

    /** Return const access to the vector data as a raw pointer. */
    const_pointer data() const;

    /** Resize the vector to the specified size.
     *
     * @note This will reallocate the array and copy existing elements, if
     * any.
     *
     * @throws std::invalid_argument if @c n is negative.
     */
    void resize(int n);

    /** Resize the vector to the specified size without copying the old
     * elements.
     *
     * @note This will reallocate the array and copy existing elements, if
     * any.
     *
     * @throws std::invalid_argument if @c n is negative.
     */
    void resize_fast(int n);


  protected:

    /** The real allocator type. */
    typedef typename Allocator::template
      rebind<Element>::other				allocator_type;

    /** Require a stateless allocator. */
    static_assert(std::is_empty<allocator_type>::value,
      "cannot use a stateful allocator for dynamic<> vectors");


  protected:

    /** No-op for trivially destructible elements
     * (is_trivially_destructible).
     */
    void destruct(pointer, int, std::true_type);

    /** Invoke non-trivial destructors for @c n elements starting at @c
     * data.
     */
    void destruct(pointer data, int n, std::false_type);


  protected:

    /** Dynamic storage. */
    pointer			m_data;

    /** Size of the vector. */
    int				m_size;
};

} // namespace cml

#define __CML_VECTOR_DYNAMIC_TPP
#include <cml/vector/dynamic.tpp>
#undef __CML_VECTOR_DYNAMIC_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
