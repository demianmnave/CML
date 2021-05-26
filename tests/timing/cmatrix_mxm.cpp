/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "cmatrix_mxm.h"

void mxm_4x4(matrix44d& res, const matrix44d& A, const matrix44d& B)
{
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            double sum = A[row][0]*B[0][col];
            for(int k = 1; k < 4; ++k) sum += A[row][k]*B[k][col];
            res[row][col] = sum;
        }
    }
}