/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <simde/hedley.h>
#include <cml/matrix.h>

#ifdef CML_TIMING_ROW_MAJOR
using matrix44d = cml::matrix44d_r;
#endif

#ifdef CML_TIMING_COL_MAJOR
using matrix44d = cml::matrix44d_c;
#endif

HEDLEY_ALWAYS_INLINE auto
mxm_4x4(matrix44d& res, const matrix44d& A, const matrix44d& B)
{
  res = A * B;
}
