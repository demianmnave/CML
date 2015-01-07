/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_detail_check_or_resize_h
#define	cml_matrix_detail_check_or_resize_h

#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/size_checking.h>

namespace cml {
namespace detail {

/** Ensure non-resizable matrix @c left is the same size as @c right. */
template<class Sub, class Other> inline void
check_or_resize(const readable_matrix<Sub>& left, const Other& right)
{
  cml::check_same_size(left, right);
}

/** Ensure resizable matrix @c left is the same size as @c right. */
template<class Sub1, class Sub2> inline auto check_or_resize(
  writable_matrix<Sub1>& left, const readable_matrix<Sub2>& right
  )
-> decltype(left.actual().resize(0,0), void())
{
  left.actual().resize(right.rows(),right.cols());
}

/** Ensure resizable matrix @c left is the same size as array @c right. */
template<class Sub1, class Other, int Rows, int Cols>
inline auto check_or_resize(
  writable_matrix<Sub1>& left, Other const (&)[Rows][Cols]
  )
-> decltype(left.actual().resize(0,0), void())
{
  left.actual().resize(Rows, Cols);
}

} // namespace detail
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
