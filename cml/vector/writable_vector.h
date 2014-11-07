/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_writable_vector_h
#define	cml_vector_writable_vector_h

#include <initializer_list>
#include <cml/common/scalar_traits.h>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Base class for writable vector types.  Writable vectors support
 * non-const read-write access to its elements, in addition to read-only
 * access via readable_vector.
 *
 * In addition to the requirements of readable_vector, DerivedT must
 * implement:
 *
 * - <X> get(int i), where <X> is the mutable_value type defined by
 * vector_traits<DerivedT>
 *
 * - template<class T> DerivedT& set(int i, const T&)
 *
 * Note that mutable_value need not be a reference type.
 */
template<class DerivedT>
class writable_vector
: public readable_vector<DerivedT>
{
  public:

    typedef DerivedT					vector_type;
    typedef readable_vector<vector_type>		readable_type;
    typedef vector_traits<vector_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::const_reference	const_reference;
    typedef typename traits_type::mutable_value		mutable_value;


  public:

    /* Disambiguate readable_vector<> methods: */
    using readable_type::actual;
    using readable_type::get;
    using readable_type::operator[];


  public:

    /** Return a mutable reference to the vector cast as DerivedT. */
    DerivedT& actual();

    /** Return mutable element @c i. */
    mutable_value get(int i);

    /** Set element @c i. */
    template<class Other> DerivedT& set(int i, const Other& v);

    /** Return a mutable reference to element @c i. */
    mutable_value operator[](int i);


  public:

    /** Divide the vector elements by the length of the vector. */
    DerivedT& normalize();

    /** Zero the vector elements. */
    DerivedT& zero();

    /** Set element @c i to value_type(1), and the other elements to 0. */
    DerivedT& cardinal(int i);

    /** Set the vector to the pairwise minimum elements with @c other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT>
      DerivedT& minimize(const readable_vector<OtherDerivedT>& other);

    /** Set the vector to the pairwise minimum elements with @c other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT>
      DerivedT& maximize(const readable_vector<OtherDerivedT>& other);


  public:

    /** Assign from a readable_vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size, then the size is checked at compile time.
     */
    template<class OtherDerivedT>
      DerivedT& operator=(const readable_vector<OtherDerivedT>& other);

    /** Assign from a fixed-length array type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c cml::array_size_of_c<value>::value !=
     * this->size().  If both are fixed-size, then the size is checked at
     * compile time.
     */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& operator=(const Array& array);

    /** Assign from initializer list.
     *
     * @throws incompatible_vector_sizes if the vector is not resizable,
     * and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT& operator=(std::initializer_list<Other> l);

    /** Modify the vector by addition of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT>
      DerivedT& operator+=(const readable_vector<OtherDerivedT>& other);

    /** Modify the vector by subtraction of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT>
      DerivedT& operator-=(const readable_vector<OtherDerivedT>& other);

    /** Multiply the vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT& operator*=(const_reference v);

    /** Divide the vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT& operator/=(const_reference v);


  protected:

    /** Assign from a readable_vector.
     *
     * @note This depends upon implicit conversion of the source vector
     * elements to the vector value_type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT>
      DerivedT& assign(const readable_vector<OtherDerivedT>& other);

    /** Assign from an array type.
     *
     * @note This depends upon implicit conversion of the array elements to
     * the vector value_type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c cml::array_size_of_c<value>::value !=
     * this->size().  If both are fixed-size, then the size is checked at
     * compile time.
     */
    template<class Array,
      typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& assign(const Array& array);

    /** Assign from an initializer_list.
     *
     * @note This depends upon implicit conversion of @c Other to the
     * vector value_type.
     *
     * @throws incompatible_vector_sizes if the vector is not resizable,
     * and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT& assign(const std::initializer_list<Other>& l);

    /** Construct from a variable list of at least 2 values. If the vector
     * is fixed-size and longer than the variable argument list, the
     * remaining elements are set to value_type(0).  Resizable vectors are
     * resized to accomodate the number of arguments.
     *
     * @note For fixed-size vectors, there must be fewer arguments than the
     * vector size.  This is enforced at compile time.
     *
     * @note This depends upon implicit conversions of the elements to the
     * vector value_type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * fixed-size, and if @c 1 + sizeof...(eN) >= this->size(). If the
     * vector is ixed-size, then the size is checked at compile time.
     */
    template<class... Elements>
      DerivedT& assign_elements(const Elements&... eN);


  protected:

    // Force assignment through operator=(readable_vector<>):
    writable_vector& operator=(writable_vector&) = delete;
};

} // namespace cml

#define __CML_VECTOR_WRITABLE_VECTOR_TPP
#include <cml/vector/writable_vector.tpp>
#undef __CML_VECTOR_WRITABLE_VECTOR_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
