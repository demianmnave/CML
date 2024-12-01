/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include "cmatrix.h"

inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  for(int row = 0; row < 4; ++row) {
    for(int col = 0; col < 4; ++col) {
      auto sum = 0.;
      for(int k = 0; k < 4; ++k) sum += A[row][k] * B[k][col];
      C[row][col] = sum;
    }
  }
}
