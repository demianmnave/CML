/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_writable_matrix_h
#define	cml_matrix_writable_matrix_h

#include <initializer_list>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

/** Base class for writable matrix types.  Writable matrices support
 * non-const read-write access to its elements, in addition to read-only
 * access via readable_matrix.
 *
 * In addition to the requirements of readable_matrix, DerivedT must
 * implement:
 *
 * - <X> get(int i, int j) returning element @c (i,j) as a mutable value,
 * where <X> is the mutable_value type defined by matrix_traits<DerivedT>
 *
 * - template<class T> DerivedT& set(int i, int j, const T&)
 *
 *   for compilers without support for rvalue reference from *this; and
 *
 *   template<class T> DerivedT& set(int i, int j, const T&) &
 *   template<class T> DerivedT&& set(int i, int j, const T&) &&
 *
 *   for compilers with support for rvalue reference from this.
 *
 * Note that mutable_value need not be a reference type.
 */
template<class DerivedT>
class writable_matrix
: public readable_matrix<DerivedT>
{
  public:

    typedef DerivedT					matrix_type;
    typedef readable_matrix<matrix_type>		readable_type;
    typedef matrix_traits<matrix_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::const_reference	const_reference;
    typedef typename traits_type::mutable_value		mutable_value;
    typedef typename traits_type::basis_tag		basis_tag;
    typedef typename traits_type::layout_tag		layout_tag;


  public:

    /* Disambiguate readable_matrix<> methods: */
    using readable_type::actual;
    using readable_type::get;
    using readable_type::operator();


  public:

    /** Return a mutable reference to the matrix cast as DerivedT. */
    DerivedT& actual();

    /** Set element @c (i,j). */
    template<class Other> DerivedT&
      set(int i, int j, const Other& v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set element @c (i,j) on a temporary. */
    template<class Other> DerivedT&&
      set(int i, int j, const Other& v) &&;
#endif

    /** Return mutable element @c (i,j). */
    mutable_value get(int i, int j);

    /** Return a mutable reference to element @c (i,j). */
    mutable_value operator()(int i, int j);


  public:

    /** Zero the matrix elements. */
    DerivedT& zero() __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Zero the matrix elements of a temporary. */
    DerivedT&& zero() &&;
#endif

    /** Set elements to random values in the range @c[low,high]. */
    DerivedT& random(const_reference low, const_reference high) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set elements of a temporary to random values in the range
     * @c[low,high].
     */
    DerivedT&& random(const_reference low, const_reference high) &&;
#endif


  public:

    /** Assign from a readable_matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&
      operator=(const readable_matrix<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from a readable_matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size, then the size is checked at compile time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator=(const readable_matrix<OtherDerivedT>& other) &&;
#endif

    /** Assign from a fixed-length array type.
     *
     * @throws incompatible_matrix_size_error at run-time if @c
     * cml::array_size_of_c<value>::value != this->rows()*this->cols().  If
     * both are fixed-size, then the size is checked at compile time.
     */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& operator=(const Array& array) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from a fixed-length array type.
     *
     * @throws incompatible_matrix_size_error at run-time if @c
     * cml::array_size_of_c<value>::value != this->rows()*this->cols().  If
     * both are fixed-size, then the size is checked at compile time.
     */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT&& operator=(const Array& array) &&;
#endif

    /** Assign from a 2D C-array.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * not resizable and does not have the same size as @c array.  If both
     * are fixed-size, then the size is checked at compile time.
     */
    template<class Other, int Rows, int Cols>
      DerivedT& operator=(Other const (&array)[Rows][Cols]) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from a fixed-length array type.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * not resizable and does not have the same size as @c array.  If both
     * are fixed-size, then the size is checked at compile time.
     */
    template<class Other, int Rows, int Cols>
      DerivedT& operator=(Other const (&array)[Rows][Cols]) &&;
#endif

    /** Assign from initializer list.
     *
     * @throws incompatible_matrix_size_error if the matrix is not
     * resizable, and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT& operator=(std::initializer_list<Other> l) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Assign a temporary from initializer list.
     *
     * @throws incompatible_matrix_size_error if the matrix is not
     * resizable, and if @c l.size() != this->size().
     */
    template<class Other>
      DerivedT&& operator=(std::initializer_list<Other> l) &&;
#endif

    /** Modify the matrix by addition of another matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&
      operator+=(const readable_matrix<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Modify a temporary matrix by addition of another matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator+=(const readable_matrix<OtherDerivedT>& other) &&;
#endif

    /** Modify the matrix by subtraction of another matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&
      operator-=(const readable_matrix<OtherDerivedT>& other) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Modify a temporary matrix by subtraction of another matrix.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * dynamically-sized, and if @c other.size() != this->size().  If both
     * are fixed-size expressions, then the size is checked at compile
     * time.
     */
    template<class OtherDerivedT> DerivedT&&
      operator-=(const readable_matrix<OtherDerivedT>& other) &&;
#endif

    /** Multiply the matrix by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * matrix value_type.
     */
    DerivedT& operator*=(const_reference v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Multiply a temporary matrix by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * matrix value_type.
     */
    DerivedT&& operator*=(const_reference v) &&;
#endif

    /** Divide the matrix by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * matrix value_type.
     */
    DerivedT& operator/=(const_reference v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Divide a temporary matrix by a scalar.
     *
     * @note This depends upon implicit conversion of @c v to the
     * matrix value_type.
     */
    DerivedT&& operator/=(const_reference v) &&;
#endif


  protected:

    /** Assign from a readable_matrix.
     *
     * @note This depends upon implicit conversion of the source matrix
     * elements to the matrix value_type.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is not
     * resizable, and if @c other.size() != this->size().  If both are
     * fixed-size expressions, then the size is checked at compile time.
     */
    template<class OtherDerivedT>
      DerivedT& assign(const readable_matrix<OtherDerivedT>& other);

    /** Assign from an array type.
     *
     * @note This depends upon implicit conversion of the array elements to
     * the matrix value_type.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * not resizable, and if @c cml::array_size_of_c<value>::value !=
     * this->rows()*this->cols().  If both are fixed-size, then the size is
     * checked at compile time.
     */
    template<class Array,
      typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& assign(const Array& array);

    /** Assign from a 2D C-array type.
     *
     * @note This depends upon implicit conversion of the array elements to
     * the matrix value_type.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * not resizable and does not have the same size as @c array.  If both
     * are fixed-size, then the size is checked at compile time.
     */
    template<class Other, int Rows, int Cols>
      DerivedT& assign(Other const (&array)[Rows][Cols]);

    /** Assign from an initializer_list.
     *
     * @note This depends upon implicit conversion of @c Other to the
     * matrix value_type.
     *
     * @throws incompatible_matrix_size_error if the matrix is not resizable,
     * and if @c l.size() != this->rows()*this->cols().
     */
    template<class Other>
      DerivedT& assign(const std::initializer_list<Other>& l);

    /** Construct from a variable list of values. If the matrix has more
     * elements than the variable argument list, the remaining elements are
     * set to value_type(0).
     *
     * @note For fixed-size matrices, the number of arguments is checked
     * against the number of matrix elements at compile time.
     *
     * @note This depends upon implicit conversions of the elements to the
     * matrix value_type.
     *
     * @throws incompatible_matrix_size_error at run-time if the matrix is
     * not fixed-sized, and if @c sizeof...(eN) > @c (rows()*cols()).  If
     * the matrix is fixed-size, then the size is checked at compile time.
     */
    template<class... Elements> DerivedT&
      assign_elements(const Elements&... eN);


  protected:

    // Use the compiler-generated default constructor:
    writable_matrix() = default;

    // Use the compiler-generated copy constructor:
    writable_matrix(const writable_matrix&) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    // Use the compiler-generated move constructor:
    writable_matrix(writable_matrix&&) = default;
#endif

    // Force assignment through operator=(readable_matrix<>):
    writable_matrix& operator=(const writable_matrix&) = delete;
};

} // namespace cml

#define __CML_MATRIX_WRITABLE_MATRIX_TPP
#include <cml/matrix/writable_matrix.tpp>
#undef __CML_MATRIX_WRITABLE_MATRIX_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
