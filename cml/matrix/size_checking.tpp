/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_SIZE_CHECKING_TPP
#error "matrix/size_checking.tpp not included correctly"
#endif

#include <cml/common/mpl/array_size_of.h>
#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {
namespace detail {

/* No-op binary matrix expression linear size checking: */
template<class Sub1, class Sub2> inline void check_same_linear_size(
  const readable_matrix<Sub1>&, const Sub2&, any_size_tag) {}

/* Compile-time binary matrix expression linear size checking: */
template<class Sub1, class Sub2> inline void check_same_linear_size(
  const readable_matrix<Sub1>&, const Sub2&, fixed_size_tag
  )
{
  static_assert(
    Sub1::array_rows*Sub1::array_cols == cml::array_size_of_c<Sub2>::value,
    "incompatible matrix expression sizes");
}

/* Run-time binary matrix expression linear size checking: */
template<class Sub1, class Sub2> inline void check_same_linear_size(
  const readable_matrix<Sub1>& left, const Sub2& right, dynamic_size_tag
  )
{
#ifndef CML_NO_RUNTIME_MATRIX_SIZE_CHECKS
  cml_require(left.rows()*left.cols() == cml::array_size_of(right),
    incompatible_matrix_size_error, /**/);
#endif
}


/* No-op matrix linear size checking. */
template<class Sub> inline void check_linear_size(
  const readable_matrix<Sub>&, int, any_size_tag) {}

/* Compile-time matrix linear size checking. */
template<class Sub, int N> void check_linear_size(
  const readable_matrix<Sub>&, cml::int_c<N>, fixed_size_tag
  )
{
  static_assert(Sub::array_rows*Sub::array_cols == N,
    "incorrect matrix expression size");
}

/* Run-time matrix linear size checking. */
template<class Sub, class SizeTag> void check_linear_size(
  const readable_matrix<Sub>& sub, int N, SizeTag
  )
{
#ifndef CML_NO_RUNTIME_MATRIX_SIZE_CHECKS
  cml_require(sub.rows()*sub.cols() == N, matrix_size_error, /**/);
#endif
}


/* No-op binary matrix expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_matrix<Sub1>&, const Sub2&, any_size_tag) {}

/* Compile-time binary matrix expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_matrix<Sub1>&, const Sub2&, fixed_size_tag
  )
{
  static_assert(
    (Sub1::array_rows == Sub2::array_rows)
    && (Sub1::array_cols == Sub2::array_cols),
    "incompatible matrix expression sizes");
}

/* Run-time binary matrix expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_matrix<Sub1>& left, const Sub2& right, dynamic_size_tag
  )
{
#ifndef CML_NO_RUNTIME_MATRIX_SIZE_CHECKS
  cml_require(left.size() == right.size(),
    incompatible_matrix_size_error, /**/);
#endif
}

/* Compile-time binary matrix expression size checking against a C-array: */
template<class Sub, class Other, int R, int C> inline void check_same_size(
  const readable_matrix<Sub>&, Other const (&)[R][C], fixed_size_tag
  )
{
  static_assert((Sub::array_rows == R) && (Sub::array_cols == C),
    "incompatible matrix expression sizes");
}

/* Run-time binary matrix expression size checking against a C-array: */
template<class Sub, class Other, int R, int C> inline void check_same_size(
  const readable_matrix<Sub>& left, Other const (&)[R][C], dynamic_size_tag
  )
{
#ifndef CML_NO_RUNTIME_MATRIX_SIZE_CHECKS
  cml_require((left.rows() == R && left.cols() == C),
    incompatible_matrix_size_error, /**/);
#endif
}

} // namespace detail


/* check_same_linear_size: */

template<class Sub1, class Sub2> void
check_same_linear_size(
  const readable_matrix<Sub1>& left, const readable_matrix<Sub1>& right
  )
{
  typedef matrix_size_tag_of_t<Sub1> tag1;
  typedef matrix_size_tag_of_t<Sub2> tag2;
  detail::check_same_linear_size(
    left, right.actual(), size_check_promote_t<tag1,tag2>());
}

template<class Sub1, class Sub2> void
check_same_linear_size(
  const readable_matrix<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>*
  )
{
  typedef matrix_size_tag_of_t<Sub1> tag1;
  typedef tag1 tag2;			// dynamic/dynamic or fixed/fixed.
  detail::check_same_linear_size(
    left, right, size_check_promote_t<tag1,tag2>());
}

template<class Sub1, class Sub2> auto
check_same_linear_size(const readable_matrix<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void())
{
  typedef matrix_size_tag_of_t<Sub1> tag1;
  typedef dynamic_size_tag tag2;	// dynamic/dynamic or fixed/dynamic.
  detail::check_same_linear_size(
    left, right, size_check_promote_t<tag1,tag2>());
}


/* check_linear_size: */

template<class Sub> void
check_linear_size(const readable_matrix<Sub>& left, int n)
{
  typedef matrix_size_tag_of_t<Sub> tag;
  detail::check_linear_size(left, n, tag());
}

template<class Sub, int N> void
check_linear_size(const readable_matrix<Sub>& left, cml::int_c<N>)
{
  typedef matrix_size_tag_of_t<Sub> tag;
  detail::check_linear_size(left, cml::int_c<N>(), tag());
}


/* check_same_size: */

template<class Sub1, class Sub2> void
check_same_size(
  const readable_matrix<Sub1>& left, const readable_matrix<Sub2>& right
  )
{
  typedef matrix_size_tag_of_t<Sub1> tag1;
  typedef matrix_size_tag_of_t<Sub2> tag2;
  detail::check_same_size(
    left, right.actual(), size_check_promote_t<tag1,tag2>());
}

template<class Sub, class Other, int R, int C> void
check_same_size(
  const readable_matrix<Sub>& left, Other const (&array)[R][C]
  )
{
  typedef matrix_size_tag_of_t<Sub> tag1;
  typedef fixed_size_tag tag2;
  detail::check_same_size(left, array, size_check_promote_t<tag1,tag2>());
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
