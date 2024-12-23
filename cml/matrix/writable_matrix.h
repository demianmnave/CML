/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <initializer_list>
#include <cml/common/mpl/enable_if_pointer.h>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/common/mpl/enable_if_convertible.h>
#include <cml/vector/fwd.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

/** Base class for writable matrix types.  Writable matrices support
 * non-const read-write access to its elements, in addition to read-only
 * access via readable_matrix.
 *
 * In addition to the requirements of readable_matrix, DerivedT must
 * implement:
 *
 * - <X> i_get(int i, int j) returning element @c (i,j) as a mutable value,
 * where <X> is the mutable_value type defined by matrix_traits<DerivedT>
 *
 * - template<class T> DerivedT& i_put(int i, int j, const T&)
 *
 *   for compilers without support for rvalue reference from *this; and
 *
 *   template<class T> DerivedT& i_put(int i, int j, const T&) &
 *   template<class T> DerivedT&& i_put(int i, int j, const T&) &&
 *
 *   for compilers with support for rvalue reference from this.
 *
 * Note that mutable_value need not be a reference type.
 */
template<class DerivedT>
class writable_matrix : public readable_matrix<DerivedT>
{
  public:
  using matrix_type = DerivedT;
  using readable_type = readable_matrix<matrix_type>;
  using traits_type = matrix_traits<matrix_type>;
  using value_type = typename traits_type::value_type;
  using const_reference = typename traits_type::const_reference;
  using mutable_value = typename traits_type::mutable_value;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;


  public:
  /* Disambiguate readable_matrix<> methods: */
  using readable_type::actual;
  using readable_type::get;
  using readable_type::operator();


  public:
  /** Return a mutable reference to the matrix cast as DerivedT. */
  DerivedT& actual();

  /** Set element @c (i,j). */
  template<class Other> DerivedT& put(int i, int j, const Other& v) &;

  /** Set element @c (i,j) on a temporary. */
  template<class Other> DerivedT&& put(int i, int j, const Other& v) &&;

  /** Return mutable element @c (i,j). */
  mutable_value get(int i, int j);

  /** Return a mutable reference to element @c (i,j). */
  mutable_value operator()(int i, int j);


  public:
  /** Set element @c j of basis vector @c i. */
  template<class Other>
  DerivedT& set_basis_element(int i, int j, const Other& v) &;

  /** Set element @c j of basis vector @c i on a temporary. */
  template<class Other>
  DerivedT&& set_basis_element(int i, int j, const Other& v) &&;

  /** Copy @c v to row @c i of the matrix.
   *
   * @throws cml::incompatible_matrix_col_size_error if the matrix is
   * dynamic and the number of columns does not match the size of
   * @c v.  The sizes are checked at compile time otherwise.
   */
  template<class Sub> DerivedT& set_row(int i, const readable_vector<Sub>& v) &;

  /** Copy @c v to row @c i of a temporary matrix.
   *
   * @throws cml::incompatible_matrix_col_size_error if the matrix is
   * dynamic and the number of columns does not match the size of
   * @c v.  The sizes are checked at compile time otherwise.
   */
  template<class Sub>
  DerivedT&& set_row(int i, const readable_vector<Sub>& v) &&;

  /** Copy @c v to column @c j of the matrix.
   *
   * @throws cml::incompatible_matrix_row_size_error if the matrix is
   * dynamic and the number of rows does not match the size of @c v.  The
   * sizes are checked at compile time otherwise.
   */
  template<class Sub> DerivedT& set_col(int j, const readable_vector<Sub>& v) &;

  /** Copy @c v to column @c j of a temporary matrix.
   *
   * @throws cml::incompatible_matrix_row_size_error if the matrix is
   * dynamic and the number of rows does not match the size of @c v.  The
   * sizes are checked at compile time otherwise.
   */
  template<class Sub>
  DerivedT&& set_col(int j, const readable_vector<Sub>& v) &&;

  /** Zero the matrix elements. */
  DerivedT& zero() &;

  /** Zero the matrix elements of a temporary. */
  DerivedT&& zero() &&;

  /** Set the matrix to the identity. */
  DerivedT& identity() &;

  /** Set a temporary matrix to the identity. */
  DerivedT&& identity() &&;

  /** Set elements to random values in the range @c[low,high]. */
  DerivedT& random(const_reference low, const_reference high) &;

  /** Set elements of a temporary to random values in the range
   * @c[low,high].
   */
  DerivedT&& random(const_reference low, const_reference high) &&;

  /** Set all elements to a specific value. */
  DerivedT& fill(const_reference v) &;

  /** Set all elements of a temporary to a specific value. */
  DerivedT&& fill(const_reference v) &&;

  /** Set the matrix to its inverse.
   *
   * @throws non_square_matrix_error at run-time if the matrix is
   * dynamically sized and not square.
   */
  DerivedT& inverse() &;

  /** Set a temporary matrix to its inverse.
   *
   * @throws non_square_matrix_error at run-time if the matrix is
   * dynamically sized and not square.
   */
  DerivedT&& inverse() &&;

  /** Set the matrix to its transpose.
   *
   * @note This will raise a compile time error if the matrix is
   * fixed-size and non-square.  Dynamic-size matrices will be assigned
   * from a temporary.
   */
  DerivedT& transpose() &;

  /** Set a temporary matrix to its inverse.
   *
   * @note This will raise a compile time error if the matrix is
   * fixed-size and non-square.  Dynamic-size matrices will be assigned
   * from a temporary.
   */
  DerivedT&& transpose() &&;


  public:
  /** Assign from a readable_matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is not
   * resizable, and if @c other.size() != this->size().  If both are
   * fixed-size, then the size is checked at compile time.
   */
  template<class OtherDerivedT>
  DerivedT& operator=(const readable_matrix<OtherDerivedT>& other) &;

  /** Assign a temporary from a readable_matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is not
   * resizable, and if @c other.size() != this->size().  If both are
   * fixed-size, then the size is checked at compile time.
   */
  template<class OtherDerivedT>
  DerivedT&& operator=(const readable_matrix<OtherDerivedT>& other) &&;

  /** Assign from a fixed-length array type.
   *
   * @throws incompatible_matrix_size_error at run-time if @c
   * array_size_of_c<value>::value != this->rows()*this->cols().  If both
   * are fixed-size, then the size is checked at compile time.
   */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  DerivedT& operator=(const Array& array) &;

  /** Assign a temporary from a fixed-length array type.
   *
   * @throws incompatible_matrix_size_error at run-time if @c
   * array_size_of_c<value>::value != this->rows()*this->cols().  If both
   * are fixed-size, then the size is checked at compile time.
   */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  DerivedT&& operator=(const Array& array) &&;

  /** Assign from a 2D C-array.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * not resizable and does not have the same size as @c array.  If both
   * are fixed-size, then the size is checked at compile time.
   */
  template<class Other, int Rows, int Cols>
  DerivedT& operator=(Other const (&array)[Rows][Cols]) &;

  /** Assign a temporary from a fixed-length array type.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * not resizable and does not have the same size as @c array.  If both
   * are fixed-size, then the size is checked at compile time.
   */
  template<class Other, int Rows, int Cols>
  DerivedT& operator=(Other const (&array)[Rows][Cols]) &&;

  /** Assign from initializer list.
   *
   * @throws incompatible_matrix_size_error if the matrix is not
   * resizable, and if @c l.size() != this->size().
   */
  template<class Other> DerivedT& operator=(std::initializer_list<Other> l) &;

  /** Assign a temporary from initializer list.
   *
   * @throws incompatible_matrix_size_error if the matrix is not
   * resizable, and if @c l.size() != this->size().
   */
  template<class Other> DerivedT&& operator=(std::initializer_list<Other> l) &&;

  /** Modify the matrix by addition of another matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * dynamically-sized, and if @c other.size() != this->size().  If both
   * are fixed-size expressions, then the size is checked at compile
   * time.
   */
  template<class OtherDerivedT>
  DerivedT& operator+=(const readable_matrix<OtherDerivedT>& other) &;

  /** Modify a temporary matrix by addition of another matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * dynamically-sized, and if @c other.size() != this->size().  If both
   * are fixed-size expressions, then the size is checked at compile
   * time.
   */
  template<class OtherDerivedT>
  DerivedT&& operator+=(const readable_matrix<OtherDerivedT>& other) &&;

  /** Modify the matrix by subtraction of another matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * dynamically-sized, and if @c other.size() != this->size().  If both
   * are fixed-size expressions, then the size is checked at compile
   * time.
   */
  template<class OtherDerivedT>
  DerivedT& operator-=(const readable_matrix<OtherDerivedT>& other) &;

  /** Modify a temporary matrix by subtraction of another matrix.
   *
   * @throws incompatible_matrix_size_error at run-time if the matrix is
   * dynamically-sized, and if @c other.size() != this->size().  If both
   * are fixed-size expressions, then the size is checked at compile
   * time.
   */
  template<class OtherDerivedT>
  DerivedT&& operator-=(const readable_matrix<OtherDerivedT>& other) &&;

  /** Multiply the matrix by a scalar convertible to its value_type. */
  template<class ScalarT,
    typename enable_if_convertible<value_type, ScalarT>::type* = nullptr>
  DerivedT& operator*=(const ScalarT& v) &;

  /** Multiply the matrix temporary by a scalar convertible to its
   * value_type.
   */
  template<class ScalarT,
    typename enable_if_convertible<value_type, ScalarT>::type* = nullptr>
  DerivedT&& operator*=(const ScalarT& v) &&;

  /** Divide the matrix by a scalar convertible to its value_type. */
  template<class ScalarT,
    typename enable_if_convertible<value_type, ScalarT>::type* = nullptr>
  DerivedT& operator/=(const ScalarT& v) &;

  /** Divide a temporary matrix by a scalar.
   *
   * @note This depends upon implicit conversion of @c v to the
   * matrix value_type.
   */
  template<class ScalarT,
    typename enable_if_convertible<value_type, ScalarT>::type* = nullptr>
  DerivedT&& operator/=(const ScalarT& v) &&;


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
   * not resizable, and if @c array_size_of_c<value>::value !=
   * this->rows()*this->cols().  If both are fixed-size, then the size is
   * checked at compile time.
   */
  template<class Array, enable_if_array_t<Array>* = nullptr>
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

  /** Assign from a pointer to an array.
   *
   * @note This depends upon implicit conversion of the array elements to
   * the matrix value_type.
   *
   * @note The number of elements read from @c array depends upon the
   * current size of the matrix.
   */
  template<class Pointer, cml::enable_if_pointer_t<Pointer>* = nullptr>
  DerivedT& assign(const Pointer& array);

  /** Assign from an initializer_list.
   *
   * @note This depends upon implicit conversion of @c Other to the
   * matrix value_type.
   *
   * @throws incompatible_matrix_size_error if the matrix is not resizable,
   * and if @c l.size() != this->rows()*this->cols().
   */
  template<class Other> DerivedT& assign(const std::initializer_list<Other>& l);

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
  template<class... Elements> DerivedT& assign_elements(const Elements&... eN);


  protected:
  /** Set basis element @c (i,j) for a row-basis matrix. */
  template<class Other>
  void set_basis_element(int i, int j, const Other& v, row_basis);

  /** Set basis element @c (i,j) for a column-basis matrix. */
  template<class Other>
  void set_basis_element(int i, int j, const Other& v, col_basis);


  protected:
  // Use the compiler-generated default constructor:
  writable_matrix() = default;

  // Use the compiler-generated copy constructor:
  writable_matrix(const writable_matrix&) = default;

  // Use the compiler-generated move constructor:
  writable_matrix(writable_matrix&&) = default;

  // Force assignment through operator=(readable_matrix<>):
  writable_matrix& operator=(const writable_matrix&) = delete;
};

}  // namespace cml

#define __CML_MATRIX_WRITABLE_MATRIX_TPP
#include <cml/matrix/writable_matrix.tpp>
#undef __CML_MATRIX_WRITABLE_MATRIX_TPP
