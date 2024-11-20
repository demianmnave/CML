/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/detail/get.h>

namespace cml::detail {

/** Apply @c Op pairwise to @c left and @c right and assign the result to @c
 * left, where @c left is assumed to have a row-major layout.
 */
template<class Op, class Sub, class Other>
inline void
apply(writable_matrix<Sub>& left, const Other& right, row_major)
{
  for(int i = 0; i < left.rows(); ++i)
    for(int j = 0; j < left.cols(); ++j)
      left.put(i, j, Op().apply(left.get(i, j), get(right, i, j)));
}

/** Apply @c Op pairwise to @c left and @c right and assign the result to
 * @c left, where @c left is assumed to have a column-major layout.
 */
template<class Op, class Sub, class Other>
inline void
apply(writable_matrix<Sub>& left, const Other& right, col_major)
{
  for(int j = 0; j < left.cols(); ++j)
    for(int i = 0; i < left.rows(); ++i)
      left.put(i, j, Op().apply(left.get(i, j), get(right, i, j)));
}

}
