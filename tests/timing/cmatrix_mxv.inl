/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/detail/get.h>
#include <cml/matrix/detail/get.h>

#include "cmatrix.h"
#include "cvector.h"

inline void
mxv_4x1(vector4d& x, const matrix44d& M, const vector4d& v)
{
  for(int i = 0; i < 4; ++i) {
    auto m = cml::detail::get(M, i, 0) * cml::detail::get(v, 0);
    for(int k = 1; k < 4; ++k)
      m += cml::detail::get(M, i, k) * cml::detail::get(v, k);
    x[i] = m;
  }
}

inline void
mxv_1x4(vector4d& x, const vector4d& v, const matrix44d& M)
{
  for(int j = 0; j < 4; ++j) {
    auto m = cml::detail::get(v, 0) * cml::detail::get(M, 0, j);
    for(int k = 1; k < 4; ++k)
      m += cml::detail::get(v, k) * cml::detail::get(M, k, j);
    x[j] = m;
  }
}
