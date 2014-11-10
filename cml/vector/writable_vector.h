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
 *   for compilers without support for rvalue reference from *this; and
 *
 *   template<class T> DerivedT& set(int i, const T&) &
 *   template<class T> DerivedT&& set(int i, const T&) &&
 *
 *   for compilers with support for rvalue reference from this.
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

    /** Set element @c i. */
    template<class Other> DerivedT& set(int i, const Other& v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set element @c i on a temporary. */
    template<class Other> DerivedT&& set(int i, const Other& v) &&;
#endif

    /** Return mutable element @c i. */
    mutable_value get(int i);

    /** Return a mutable reference to element @c i. */
    mutable_value operator[](int i);


  public:

    /** Divide the vector elements by the length of the vector. */
    DerivedT& normalize() __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Divide the vector elements of a temporary by the length of the
     * vector.
     */
    DerivedT&& normalize() &&;
#endif

    /** Zero the vector elements. */
    DerivedT& zero() __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Zero the vector elements of a temporary. */
    DerivedT&& zero() &&;
#endif

    /** Set element @c i to value_type(1), and the other elements to 0. */
    DerivedT& cardinal(int i) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set element @c i of a temporary to value_type(1), and the other
     * elements to 0.
     */
    DerivedT&& cardinal(int i) &&;
#endif

    /** Set the vector to the pairwise minimum elements with @c other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&
      minimize(const readable_vector<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set the temporary vector to the pairwise minimum elements with @c
     * other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&&
      minimize(const readable_vector<OtherDerivedT>& other) &&;
#endif

    /** Set the vector to the pairwise minimum elements with @c other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&
      maximize(const readable_vector<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set the vector to the pairwise minimum elements with @c other.
     *
     * @throws incompatible_vector_sizes at run-time if either vector is
     * dynamically-sized, and @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&&
      maximize(const readable_vector<OtherDerivedT>& other) &&;
#endif


  public:

    /** Assign from a readable_vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&
      operator=(const readable_vector<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from a readable_vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator=(const readable_vector<OtherDerivedT>& other) &&;
#endif

    /** Assign from a fixed-length array type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c cml::array_size_of_c<value>::value !=
     * this->size().  If both are fixed-size, then the size is checked at
     * compile time.
     */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& operator=(const Array& array) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from a fixed-length array type.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is not
     * resizable, and if @c cml::array_size_of_c<value>::value !=
     * this->size().  If both are fixed-size, then the size is checked at
     * compile time.
     */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT&& operator=(const Array& array) &&;
#endif

    /** Assign from initializer list.
     *
     * @throws incompatible_vector_sizes if the vector is not resizable,
     * and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT& operator=(std::initializer_list<Other> l) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from initializer list.
     *
     * @throws incompatible_vector_sizes if the vector is not resizable,
     * and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT&& operator=(std::initializer_list<Other> l) &&;
#endif

    /** Modify the vector by addition of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&
      operator+=(const readable_vector<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Modify a temporary vector by addition of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator+=(const readable_vector<OtherDerivedT>& other) &&;
#endif

    /** Modify the vector by subtraction of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&
      operator-=(const readable_vector<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Modify a temporary vector by subtraction of another vector.
     *
     * @throws incompatible_vector_sizes at run-time if the vector is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator-=(const readable_vector<OtherDerivedT>& other) &&;
#endif

    /** Multiply the vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT& operator*=(const_reference v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Multiply a temporary vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT&& operator*=(const_reference v) &&;
#endif

    /** Divide the vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT& operator/=(const_reference v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Divide a temporary vector by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * vector value_type.
     */
    DerivedT&& operator/=(const_reference v) &&;
#endif


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

    // Use the compiler-generated default constructor:
    writable_vector() = default;

    // Use the compiler-generated copy constructor:
    writable_vector(const writable_vector&) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    // Use the compiler-generated move constructor:
    writable_vector(writable_vector&&) = default;
#endif

    // Force assignment through operator=(readable_vector<>):
    writable_vector& operator=(const writable_vector&) = delete;
};

} // namespace cml

#define __CML_VECTOR_WRITABLE_VECTOR_TPP
#include <cml/vector/writable_vector.tpp>
#undef __CML_VECTOR_WRITABLE_VECTOR_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
