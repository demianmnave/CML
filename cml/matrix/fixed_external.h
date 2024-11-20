/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/external_selector.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {

template<class Element, int Rows, int Cols, typename BasisOrient,
  typename Layout>
struct matrix_traits<matrix<Element, external<Rows, Cols>, BasisOrient, Layout>>
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
  using storage_type = rebind_t<external<Rows, Cols>, matrix_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, fixed_size_tag>::value,
    "invalid size tag");

  /* Array rows (should be positive): */
  static const int array_rows = storage_type::array_rows;
  static_assert(array_rows > 0, "invalid row size");

  /* Array columns (should be positive): */
  static const int array_cols = storage_type::array_cols;
  static_assert(array_cols > 0, "invalid column size");

  /* Basis orientation: */
  using basis_tag = BasisOrient;

  /* Layout: */
  using layout_tag = Layout;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = basis_tag::value;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = layout_tag::value;
};

/** Fixed-size matrix. */
template<class Element, int Rows, int Cols, typename BasisOrient,
  typename Layout>
class matrix<Element, external<Rows, Cols>, BasisOrient, Layout>
: public writable_matrix<
    matrix<Element, external<Rows, Cols>, BasisOrient, Layout>>
{
  public:
  using matrix_type = matrix<Element, external<Rows, Cols>, BasisOrient, Layout>;
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
  /** The matrix data type, depending upon the layout. */
  using matrix_data_type = if_t<layout_tag::value == row_major_c, value_type[Rows][Cols],
    value_type[Cols][Rows]>;


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
  /** Default construct with a null pointer.
   *
   * @warning The default constructor is enabled only if the compiler
   * supports rvalue references from *this.
   */
  matrix();

  /** Construct from the wrapped pointer.
   *
   * @note @c data will be referenced using the assigned matrix layout.
   */
  explicit matrix(pointer data);

  /** Construct from a wrapped pointer to a 2D array of values.
   *
   * @note The dimensions of @c array must match those of the matrix,
   * taking the matrix layout into account.  For example, the C-array
   * initializer for a 3x2 external matrix in row-major layout will have
   * dimensions [3][2], but the initializer for a column-major matrix
   * will have dimensions [2][3].
   */
  matrix(matrix_data_type& array);

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
  inline static auto s_access(Matrix& M, int i, int j, row_major)
    -> decltype((*M.m_data)[0][0])
  {
    return (*M.m_data)[i][j];
  }

  /** Column-major access to const or non-const @c M. */
  template<class Matrix>
  inline static auto s_access(Matrix& M, int i, int j, col_major)
    -> decltype((*M.m_data)[0][0])
  {
    return (*M.m_data)[j][i];
  }


  protected:
  /** Wrapped pointer. */
  matrix_data_type* m_data;
};

}  // namespace cml

#define __CML_MATRIX_FIXED_EXTERNAL_TPP
#include <cml/matrix/fixed_external.tpp>
#undef __CML_MATRIX_FIXED_EXTERNAL_TPP
