/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/enable_if_t.h>
#include <cml/common/mpl/are_convertible.h>
#include <cml/common/mpl/rebind.h>
#include <cml/storage/allocated_selector.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {
template<class Element, class Allocator, typename BasisOrient, typename Layout>
struct matrix_traits<matrix<Element, dynamic<Allocator>, BasisOrient, Layout>>
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
  using storage_type = rebind_t<allocated<Allocator>, matrix_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, dynamic_size_tag>::value,
    "invalid size tag");

  /* Array rows (should be -1): */
  static const int array_rows = storage_type::array_rows;
  static_assert(array_rows == -1, "invalid row size");

  /* Array columns (should be -1): */
  static const int array_cols = storage_type::array_cols;
  static_assert(array_cols == -1, "invalid column size");

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
template<class Element, class Allocator, typename BasisOrient, typename Layout>
class matrix<Element, dynamic<Allocator>, BasisOrient, Layout>
  : public writable_matrix<
    matrix<Element, dynamic<Allocator>, BasisOrient, Layout>>
{
  protected:
  /** The real allocator type. */
  using allocator_type = cml::rebind_alloc_t<Allocator, Element>;

  /** Allocator traits. */
  using allocator_traits = std::allocator_traits<allocator_type>;

  /** Require a stateless allocator. */
  static_assert(std::is_empty<allocator_type>::value,
    "cannot use a stateful allocator for dynamic<> matrices");

  public:
  using matrix_type = matrix<Element, dynamic<Allocator>, BasisOrient, Layout>;
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
  /** Default constructor.
   *
   * @note The matrix has no elements.
   */
  matrix();

  /** Construct given a size.
   *
   * @throws std::invalid_argument if  @c rows < 0 or @c cols < 0.
   */
  matrix(int rows, int cols);

  /** Copy constructor. */
  matrix(const matrix_type& other);

  /** Move constructor. */
  matrix(matrix_type&& other);

  /** Construct from a readable_matrix. */
  template<class Sub> matrix(const readable_matrix<Sub>& sub);

  /** Construct from at least 1 value.
   *
   * @note This overload is enabled only if all of the arguments are
   * convertible to value_type.
   */
  template<typename RowsT, typename ColsT, class E0, class... Elements,
    enable_if_t<

      /* Avoid implicit conversions, for example, from double: */
      /**/ std::is_integral<RowsT>::value
      && std::is_integral<ColsT>::value

      /* Require compatible values: */
      && cml::are_convertible<value_type, E0, Elements...>::value>* = nullptr>

  matrix(RowsT rows, ColsT cols, const E0& e0, const Elements&... eN)
  // XXX Should be in matrix/dynamic_allocated.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
    : m_data(0)
      , m_rows(0)
      , m_cols(0)
  {
    this->resize_fast(rows, cols);
    this->assign_elements(e0, eN...);
  }

  /** Construct from an array type. */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  matrix(int rows, int cols, const Array& array);

  /** Construct from a C-array type. */
  template<class Other, int Rows, int Cols>
  matrix(Other const (&array)[Rows][Cols]);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  matrix(int rows, int cols, const Pointer& array);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  matrix(const Pointer& array, int rows, int cols);

  /** Destructor. */
  ~matrix();

  public:
  /** Return access to the matrix data as a raw pointer. */
  pointer data();

  /** Return const access to the matrix data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer begin() const;

  /** Read-only iterator over the elements as a 1D array. */
  const_pointer end() const;

  /** Resize the matrix to the specified size.
   *
   * @note This will reallocate the array and copy existing elements, if
   * any.
   *
   * @throws std::invalid_argument if @c rows or @c cols is negative.
   */
  void resize(int rows, int cols);

  /** Resize the matrix to the specified size without copying the old
   * elements.
   *
   * @throws std::invalid_argument if @c rows or @c cols is negative.
   */
  void resize_fast(int rows, int cols);

  public:
  /** Copy assignment. */
  matrix_type& operator=(const matrix_type& other);

  /** Move assignment. */
  matrix_type& operator=(matrix_type&& other);

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
  /** Dynamic storage. */
  pointer m_data;

  /** Matrix rows. */
  int m_rows;

  /** Matrix columns. */
  int m_cols;
};
} // namespace cml

#define __CML_MATRIX_DYNAMIC_ALLOCATED_TPP
#include <cml/matrix/dynamic_allocated.tpp>
#undef __CML_MATRIX_DYNAMIC_ALLOCATED_TPP
