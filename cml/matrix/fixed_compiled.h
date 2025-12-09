/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/compiled_selector.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {
template<class Element, int Rows, int Cols, typename BasisOrient,
  typename Layout>
struct matrix_traits<matrix<Element, fixed<Rows, Cols>, BasisOrient, Layout>>
{
  /* The basis must be col_basis or row_basis: */
  static_assert(std::is_same_v<BasisOrient, row_basis>
      || std::is_same_v<BasisOrient, col_basis>,
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
  using storage_type = rebind_t<compiled<Rows, Cols>, matrix_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same_v<size_tag, fixed_size_tag>,
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
class matrix<Element, fixed<Rows, Cols>, BasisOrient, Layout>
: public writable_matrix<
    matrix<Element, fixed<Rows, Cols>, BasisOrient, Layout>>
{
  public:
  using matrix_type = matrix<Element, fixed<Rows, Cols>, BasisOrient, Layout>;
  using readable_type = readable_matrix<matrix_type>;
  using writable_type = writable_matrix<matrix_type>;
  using traits_type = matrix_traits<matrix_type>;
  using storage_type = typename traits_type::storage_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using pointer = typename traits_type::pointer;
  using reference = typename traits_type::reference;
  using const_pointer = typename traits_type::const_pointer;
  using const_reference = typename traits_type::const_reference;
  using mutable_value = typename traits_type::mutable_value;
  using immutable_value = typename traits_type::immutable_value;
  using size_tag = typename traits_type::size_tag;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;

  /* Include methods from writable_matrix: */
  using writable_type::operator();
  using writable_type::operator=;

  /** Constant containing the number of rows. */
  static const int array_rows = traits_type::array_rows;

  /** Constant containing the number of columns. */
  static const int array_cols = traits_type::array_cols;

  /** Constant containing the matrix basis enumeration value. */
  static const basis_kind matrix_basis = traits_type::matrix_basis;

  /** Constant containing the array layout enumeration value. */
  static const layout_kind array_layout = traits_type::array_layout;

  /** Compiler-default constructor.
   *
   * @note The matrix elements are uninitialized.
   */
  matrix() = default;

  /** Compiler-default destructor. */
  ~matrix() = default;

  /** Compiler-default copy constructor. */
  matrix(const matrix_type& other) = default;

  /** Compiler-default move constructor. */
  matrix(matrix_type&& other) = default;

  /** Construct from a readable_matrix. */
  template<class Sub> matrix(const readable_matrix<Sub>& sub);

  /** Construct from at least 1 value.
   *
   * @note This overload is enabled only if all of the arguments are
   * convertible to value_type.
   */
  template<class E0, class... Elements,
    // XXX This could be enable_if_convertible_t, but VC++12 ICEs:
    typename enable_if_convertible<value_type, E0, Elements...>::type* =
      nullptr>
  matrix(const E0& e0, const Elements&... eN)
  // XXX Should be in matrix/fixed.tpp, but VC++12 has brain-dead
  // out-of-line template argument matching...
  {
    this->assign_elements(e0, eN...);
  }

  /** Construct from an array type. */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  matrix(const Array& array);

  /** Construct from a C-array type. */
  template<class Other, int Rows2, int Cols2>
  matrix(Other const (&array)[Rows2][Cols2]);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  matrix(const Pointer& array);

  /** Construct from std::initializer_list. */
  template<class Other> matrix(std::initializer_list<Other> l);

  /** Return access to the matrix data as a raw pointer. */
  pointer data();

  /** Return const access to the matrix data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer begin() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer end() const;

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
  template<class Other> matrix_type& i_put(int i, int j, const Other& v) &;

  /** Set element @c i on a temporary. */
  template<class Other> matrix_type&& i_put(int i, int j, const Other& v) &&;

  /*@}*/


  protected:
  /** Row-major access to const or non-const @c M. */
  template<class Matrix>
  static auto s_access(Matrix& M, int i, int j, row_major)
    -> decltype(M.m_data[0][0])
  {
    return M.m_data[i][j];
  }

  /** Column-major access to const or non-const @c M. */
  template<class Matrix>
  static auto s_access(Matrix& M, int i, int j, col_major)
    -> decltype(M.m_data[0][0])
  {
    return M.m_data[j][i];
  }

  protected:
  /** The matrix data type, depending upon the layout. */
  using matrix_data_type = if_t<array_layout == row_major_c,
    value_type[Rows][Cols], value_type[Cols][Rows]>;

  /** Fixed-size array, based on the layout. */
  matrix_data_type m_data;
};
}  // namespace cml

#include <cml/matrix/fixed_compiled.tpp>
