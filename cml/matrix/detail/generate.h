/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/detail/get.h>

namespace cml::detail {
/** Assign the value of @c f(i,j) to the element @c (i,j) of row-major
 * matrix @c left.
 */
template<class Sub, class F>
void
generate(writable_matrix<Sub>& left, F&& f, row_major)
{
  for(int i = 0; i < left.rows(); ++i)
    for(int j = 0; j < left.cols(); ++j)
      left.put(i, j, (std::forward<F>(f))(i, j));
}

/** Assign the value of @c f(i,j) to the element @c (i,j) of column-major
 * matrix @c left.
 */
template<class Sub, class F>
void
generate(writable_matrix<Sub>& left, F&& f, col_major)
{
  for(int j = 0; j < left.cols(); ++j)
    for(int i = 0; i < left.rows(); ++i)
      left.put(i, j, (std::forward<F>(f))(i, j));
}
}
