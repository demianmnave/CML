/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/external_selector.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {
template<class Element, typename BasisOrient, typename Layout>
struct matrix_traits<matrix<Element, external<>, BasisOrient, Layout>>
{
  /* The basis must be col_basis or row_basis: */
  static_assert(std::is_same<BasisOrient, row_basis>::value
    || std::is_same<BasisOrient, col_basis>::value,
    "invalid basis");

  /* Traits and types for the matrix element: */
  using element_traits = scalar_traits<Element>;
  using value_type = typename element_traits::value_type;
  using pointer = typename element_traits::pointer;
  using reference = typename element_traits::reference;
  using const_pointer = typename element_traits::const_pointer;
  using const_reference = typename element_traits::const_reference;
  using mutable_value = typename element_traits::mutable_value;
  using immutable_value = typename element_traits::immutable_value;

  /* The matrix storage type: */
  using storage_type = rebind_t<external<>, matrix_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, dynamic_size_tag>::value,
    "invalid size tag");

  /* Array rows (should be -1): */
  static const int array_rows = storage_type::array_rows;
  static_assert(array_rows == -1, "invalid row size");

  /* Array rows (should be -1): */
  static const int array_cols = storage_type::array_cols;
  static_assert(array_cols == -1, "invalid column size");

  /* Basis orientation: */
  using basis_tag = BasisOrient;

  /* Layout: */
  using layout_tag = Layout;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;
};

/** Fixed-size matrix. */
template<class Element, typename BasisOrient, typename Layout>
class matrix<Element, external<>, BasisOrient, Layout>
  : public writable_matrix<matrix<Element, external<>, BasisOrient, Layout>>
{
  // The basis must be col_basis or row_basis (NOT is_basis_tag!):
  static_assert(std::is_same<BasisOrient, row_basis>::value
    || std::is_same<BasisOrient, col_basis>::value,
    "invalid basis");

  // The layout must be col_major or row_major (NOT is_layout_tag!):
  static_assert(std::is_same<Layout, row_major>::value
    || std::is_same<Layout, col_major>::value,
    "invalid layout");

  public:
  using matrix_type = matrix<Element, external<>, BasisOrient, Layout>;
  using readable_type = readable_matrix<matrix_type>;
  using writable_type = writable_matrix<matrix_type>;
  using traits_type = matrix_traits<matrix_type>;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using pointer = typename traits_type::pointer;
  using reference = typename traits_type::reference;
  using const_pointer = typename traits_type::const_pointer;
  using const_reference = typename traits_type::const_reference;
  using mutable_value = typename traits_type::mutable_value;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;

  public:
  /* Include methods from writable_type: */
  using writable_type::operator();
  using writable_type::operator=;

  public:
  /** Constant containing the number of rows. */
  static const int array_rows = traits_type::array_rows;

  /** Constant containing the number of columns. */
  static const int array_cols = traits_type::array_cols;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = traits_type::matrix_basis;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = traits_type::array_layout;

  public:
  /** Default construct with a null pointer and 0 size (rows, cols).
   *
   * @warning The default constructor is enabled only if the compiler
   * supports rvalue references from *this.
   */
  matrix();

  /** Construct from the wrapped pointer and the dimensions.
   *
   * @note @c data will be referenced using the assigned matrix layout.
   *
   * @note This is for compatibility with CML1.
   */
  matrix(pointer data, int rows, int cols);

  /** Construct from the wrapped pointer and the dimensions.
   *
   * @note @c data will be referenced using the assigned matrix layout.
   */
  matrix(int rows, int cols, pointer data);

  /** Construct from a wrapped pointer to a 2D array of values with
   * dimensions N1xN2.
   *
   * @note The dimensions of @c array must take the matrix layout into
   * account.  For example, the C-array initializer for a 3x2 external
   * matrix in row-major layout will have dimensions N1xN2 = [3][2], but
   * the initializer for a column-major matrix will have dimensions N1xN2
   * = [2][3].
   */
  template<class Other, int N1, int N2> matrix(Other (&array)[N1][N2]);

  /** Move constructor. */
  matrix(matrix_type&& other);

  public:
  /** Return access to the matrix data as a raw pointer. */
  pointer data();

  /** Return const access to the matrix data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer begin() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer end() const;

  /** Resize (reshape) the matrix to the specified size.
   *
   * @note The existing elements are not changed.
   *
   * @throws std::invalid_argument if @c rows or @c cols is negative.
   *
   * @throws matrix_size_error if the number of elements in the resized
   * matrix would be different from the original.
   */
  void resize(int rows, int cols);

  /** Reset the matrix to have no elements and no external pointer. */
  void reset();

  public:
  /** Copy assignment. */
  matrix_type& operator=(const matrix_type& other);

  /** Move assignment. */
  matrix_type& operator=(matrix_type&& other);

  protected:
  /** @name readable_matrix Interface */
  /*@{*/

  friend readable_type;

  /** Return the number of rows. */
  int i_rows() const;

  /** Return the number of columns. */
  int i_cols() const;

  /** Return matrix const element @c (i,j). */
  immutable_value i_get(int i, int j) const;

  /*@}*/


  protected:
  /** @name writeable_matrix Interface */
  /*@{*/

  friend writable_type;

  /** Return matrix element @c (i,j). */
  mutable_value i_get(int i, int j);

  /** Set element @c i. */
  template<class Other>
  matrix_type& i_put(int i, int j, const Other& v) &;

  /** Set element @c i on a temporary. */
  template<class Other> matrix_type&& i_put(int i, int j, const Other& v) &&;

  /*@}*/


  protected:
  /** Row-major access to const or non-const @c M. */
  template<class Matrix>
  static auto s_access(Matrix& M, int i, int j, row_major)
    -> decltype(M.m_data[0])
  {
    return M.m_data[i * M.m_cols + j];
  }

  /** Column-major access to const or non-const @c M. */
  template<class Matrix>
  static auto s_access(Matrix& M, int i, int j, col_major)
    -> decltype(M.m_data[0])
  {
    return M.m_data[j * M.m_rows + i];
  }

  protected:
  /** Wrapped pointer. */
  pointer m_data;

  /** Row count. */
  int m_rows;

  /** Column count. */
  int m_cols;
};
} // namespace cml

#define __CML_MATRIX_DYNAMIC_EXTERNAL_TPP
#include <cml/matrix/dynamic_external.tpp>
#undef __CML_MATRIX_DYNAMIC_EXTERNAL_TPP
