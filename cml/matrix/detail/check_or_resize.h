/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/size_checking.h>

namespace cml::detail {
/** Ensure non-resizable matrix @c left is the same size as @c right. */
template<class Sub, class Other>
void
check_or_resize(const readable_matrix<Sub>& left, const Other& right)
{
  cml::check_same_size(left, right);
}

/** Ensure resizable matrix @c left is the same size as @c right. */
template<class Sub1, class Sub2>
auto
check_or_resize(writable_matrix<Sub1>& left, const readable_matrix<Sub2>& right)
  -> decltype(left.actual().resize(0, 0), void())
{
  left.actual().resize(right.rows(), right.cols());
}

/** Ensure resizable matrix @c left is the same size as array @c right. */
template<class Sub1, class Other, int Rows, int Cols>
auto
check_or_resize(writable_matrix<Sub1>& left, Other const (&)[Rows][Cols])
  -> decltype(left.actual().resize(0, 0), void())
{
  left.actual().resize(Rows, Cols);
}

/* check_or_resize for a read-only matrix and constant size RxC that
 * just forwards to check_size.
 */
template<class Sub, int R, int C>
void
check_or_resize(const readable_matrix<Sub>& sub, int_c<R>, int_c<C>)
{
  cml::check_size(sub, int_c<R>(), int_c<C>());
}

/* check_or_resize for a read-only matrix and run-time size RxC that
 * just forwards to check_size.
 */
template<class Sub>
void
check_or_resize(const readable_matrix<Sub>& sub, int R, int C)
{
  cml::check_size(sub, R, C);
}

/* check_or_resize for a resizable matrix and compile-time size that
 * resizes the matrix to RxC.
 */
template<class Sub, int R, int C>
auto
check_or_resize(writable_matrix<Sub>& sub, int_c<R>, int_c<C>)
  -> decltype(sub.actual().resize(0, 0), void())
{
  sub.actual().resize(R, C);
}

/* check_or_resize for a resizable matrix and run-time size that
 * resizes the matrix to RxC.
 */
template<class Sub>
auto
check_or_resize(writable_matrix<Sub>& sub, int R, int C)
  -> decltype(sub.actual().resize(0, 0), void())
{
  sub.actual().resize(R, C);
}
}  // namespace cml::detail
