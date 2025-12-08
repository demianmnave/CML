/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#ifndef CML_DISABLE_SIMD
#  define CML_DISABLE_SIMD
#endif

#include <cml/matrix.h>

using matrix44d = cml::matrix44d;

inline void
mxm_4x4(matrix44d& res, const matrix44d& A, const matrix44d& B)
{
  res = A * B;
}
