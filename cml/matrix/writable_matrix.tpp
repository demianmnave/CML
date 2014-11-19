/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_WRITABLE_MATRIX_TPP
#error "matrix/writable_matrix.tpp not included correctly"
#endif

#include <random>
#include <cml/matrix/size_checking.h>
#include <cml/matrix/scalar_ops.h>
#include <cml/matrix/unary_ops.h>
#include <cml/matrix/binary_ops.h>

namespace cml {

/* Local functions: */
namespace detail {

/** check_or_resize for a read-only matrix @c left that just forwards to
 * check_same_size.
 */
template<class Sub, class Other> inline void
check_or_resize(const readable_matrix<Sub>& left, const Other& right)
{
  cml::check_same_size(left, right);
}

/** check_or_resize for a read-write matrix @c left that resizes the matrix
 * to ensure it has the same size as @c right.
 */
template<class Sub1, class Sub2> inline auto check_or_resize(
  writable_matrix<Sub1>& left, const readable_matrix<Sub2>& right
  )
-> decltype(left.actual().resize(0,0), void())
{
  left.actual().resize(right.rows(),right.cols());
}

/** check_or_resize for a read-write matrix @c left that resizes the matrix
 * to ensure it has the same size as array @c right.
 */
template<class Sub1, class Other, int Rows, int Cols>
inline auto check_or_resize(
  writable_matrix<Sub1>& left, Other const (&)[Rows][Cols]
  )
-> decltype(left.actual().resize(0,0), void())
{
  left.actual().resize(Rows, Cols);
}


/** Terminate the assignment recursion at the final element. */
template<int I, class Sub, class E0> inline void
assign_elements(writable_matrix<Sub>& sub, const E0& e0)
{
  sub.set(I / sub.cols(), I % sub.cols(), e0);
}

/** Set element (I/cols(),I%cols()) of sub to e0, then assign the remainder
 * of the elements starting from I+1.
 */
template<int I, class Sub, class E0, class... Es>
inline void assign_elements(
  writable_matrix<Sub>& sub, const E0& e0, const Es&... eN
  )
{
  sub.set(I / sub.cols(), I % sub.cols(), e0);
  assign_elements<I+1>(sub, eN...);
}

/** Assign elements of @c sub from @c eN, assuming @c eN is given in
 * row-major order.
 */
template<class Sub, class... Es> inline void
assign_elements(writable_matrix<Sub>& sub, const Es&... eN)
{
  assign_elements<0>(sub, eN...);
}



/** Helper for copy() to return element @c (i,j) of @c array. */
template<class Other, int Rows, int Cols> inline const Other&
get(Other const (&array)[Rows][Cols], int i, int j)
{
  return array[i][j];
}

/** Helper for copy() to return element @c (i,j) of @c sub. */
template<class Sub> inline auto get(
  const readable_matrix<Sub>& sub, int i, int j
  ) -> typename matrix_traits<Sub>::immutable_value
{
  return sub.get(i,j);
}

/** Assign @c left from the elements of @c right, where @c left is assumed
 * to have a row-major layout.
 */
template<class Sub, class Other> inline void copy(
  writable_matrix<Sub>& left, const Other& right, row_major
  )
{
  for(int i = 0; i < left.rows(); ++ i)
    for(int j = 0; j < left.cols(); ++ j)
      left.set(i,j, get(right, i,j));
}

/** Assign @c left from the elements of @c right, where @c left is assumed
 * to have a column-major layout.
 */
template<class Sub, class Other> inline void copy(
  writable_matrix<Sub>& left, const Other& right, col_major
  )
{
  for(int j = 0; j < left.cols(); ++ j)
    for(int i = 0; i < left.rows(); ++ i)
      left.set(i,j, get(right, i,j));
}

template<class Sub, class F> inline void fill(
  writable_matrix<Sub>& left, F f, row_major
  )
{
  for(int i = 0; i < left.rows(); ++ i)
    for(int j = 0; j < left.cols(); ++ j) left.set(i,j, f());
}

template<class Sub, class F> inline void fill(
  writable_matrix<Sub>& left, F f, col_major
  )
{
  for(int j = 0; j < left.cols(); ++ j)
    for(int i = 0; i < left.rows(); ++ i) left.set(i,j, f());
}

} // namespace detail



/* Public methods: */

template<class DT> DT&
writable_matrix<DT>::actual()
{
  return (DT&) *this;
}

template<class DT> auto
writable_matrix<DT>::get(int i, int j) -> mutable_value
{
  return this->actual().get(i,j);
}

template<class DT> template<class Other> DT&
writable_matrix<DT>::set(int i, int j, const Other& v) __CML_REF
{
  return this->actual().set(i,j,v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_matrix<DT>::set(int i, int j, const Other& v) &&
{
  this->set(i,j,v);		// Forward to set(...) &
  return (DT&&) *this;
}
#endif

template<class DT> auto
writable_matrix<DT>::operator()(int i, int j) -> mutable_value
{
  return this->get(i,j);
}


template<class DT> DT&
writable_matrix<DT>::zero() __CML_REF
{
  auto zero_f = []() { return value_type(0); };
  detail::fill(*this, zero_f, layout_tag());
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_matrix<DT>::zero() &&
{
  this->zero();			// Forward to zero &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_matrix<DT>::random(
  const_reference low, const_reference high
  ) __CML_REF
{
  typedef if_t<std::is_integral<value_type>::value
    , std::uniform_int_distribution<value_type>
    , std::uniform_real_distribution<value_type>>	distribution_type;

  std::random_device rd;	// Non-deterministic seed, if supported.
  std::default_random_engine gen(rd());
  distribution_type d(low, high);
  auto random_f = [&d,&gen]() { return d(gen); };
  detail::fill(*this, random_f, layout_tag());
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_matrix<DT>::random(const_reference low, const_reference high) &&
{
  this->random(low, high);
  return (DT&&) *this;
}
#endif


template<class DT> template<class ODT> DT&
writable_matrix<DT>::operator=(const readable_matrix<ODT>& other) __CML_REF
{
  return this->assign(other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_matrix<DT>::operator=(const readable_matrix<ODT>& other) &&
{
  this->operator=(other);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class Array, typename cml::enable_if_array_t<Array>*> DT&
writable_matrix<DT>::operator=(const Array& array) __CML_REF
{
  return this->assign(array);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class Array, typename cml::enable_if_array_t<Array>*> DT&&
writable_matrix<DT>::operator=(const Array& array) &&
{
  this->operator=(array);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class Other, int Rows, int Cols> DT&
writable_matrix<DT>::operator=(Other const (&array)[Rows][Cols]) __CML_REF
{
  return this->assign(array);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class Other, int Rows, int Cols> DT&
writable_matrix<DT>::operator=(Other const (&array)[Rows][Cols]) &&
{
  this->operator=(array);
  return (DT&&) *this;
}
#endif

template<class DT> template<class Other> DT&
writable_matrix<DT>::operator=(std::initializer_list<Other> l) __CML_REF
{
  return this->assign(l);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_matrix<DT>::operator=(std::initializer_list<Other> l) &&
{
  return this->assign(l);
}
#endif

template<class DT> template<class ODT> DT&
writable_matrix<DT>::operator+=(const readable_matrix<ODT>& other) __CML_REF
{
  return this->assign(*this + other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_matrix<DT>::operator+=(const readable_matrix<ODT>& other) &&
{
  this->operator+=(other);
  return (DT&&) *this;
}
#endif

template<class DT> template<class ODT> DT&
writable_matrix<DT>::operator-=(const readable_matrix<ODT>& other) __CML_REF
{
  return this->assign(*this - other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_matrix<DT>::operator-=(const readable_matrix<ODT>& other) &&
{
  this->operator-=(other);
  return (DT&&) *this;
}
#endif


template<class DT> DT&
writable_matrix<DT>::operator*=(const_reference v) __CML_REF
{
  return this->assign((*this)*v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_matrix<DT>::operator*=(const_reference v) &&
{
  this->operator*=(v);
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_matrix<DT>::operator/=(const_reference v) __CML_REF
{
  return this->assign((*this)/v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_matrix<DT>::operator/=(const_reference v) &&
{
  this->operator/=(v);
  return (DT&&) *this;
}
#endif



/* Internal methods: */

template<class DT> template<class ODT> DT&
writable_matrix<DT>::assign(const readable_matrix<ODT>& other)
{
  detail::check_or_resize(*this, other);
  detail::copy(*this, other, layout_tag());
  return this->actual();
}

template<class DT>
template<class Array, typename cml::enable_if_array_t<Array>*> DT&
writable_matrix<DT>::assign(const Array& array)
{
  cml::check_same_linear_size(*this, array);
  int cols = this->cols();
  for(int i = 0; i < cml::array_size_of_c<Array>::value; ++ i) {
    this->set(i/cols, i%cols, array[i]);
  }
  return this->actual();
}

template<class DT> template<class Other, int R, int C> DT&
writable_matrix<DT>::assign(Other const (&array)[R][C])
{
  detail::check_or_resize(*this, array);
  detail::copy(*this, array, layout_tag());
  return this->actual();
}

template<class DT> template<class Other> DT&
writable_matrix<DT>::assign(const std::initializer_list<Other>& l)
{
  cml::check_same_linear_size(*this, l);
  int cols = this->cols(), i = 0;
  for(Other v : l) { this->set(i/cols, i%cols, v); ++ i; }
  return this->actual();
}

template<class DT> template<class... Es> DT&
writable_matrix<DT>::assign_elements(const Es&... eN)
{
  static const int N = int(sizeof...(eN));
  cml::check_linear_size(*this, cml::int_c<N>());

  /* Assign elements: */
  detail::assign_elements(*this, eN...);

  /* Done: */
  return this->actual();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
