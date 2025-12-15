/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <simde/hedley.h>
#include <cml/vector.h>
#include <cml/matrix.h>

using vector4d = cml::vector4d;

#ifdef CML_TIMING_ROW_MAJOR
using matrix44d = cml::matrix44d_r;
#endif

#ifdef CML_TIMING_COL_MAJOR
using matrix44d = cml::matrix44d_c;
#endif

HEDLEY_ALWAYS_INLINE auto
mxv_4x1(vector4d& x, const matrix44d& M, const vector4d& v)
{
  x = M * v;
}

HEDLEY_ALWAYS_INLINE auto
mxv_1x4(vector4d& x, const vector4d& v, const matrix44d& M)
{
  x = v * M;
}