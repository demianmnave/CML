
/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#ifdef CML_DISABLE_SIMD
#define CML_SIMD_SCALAR
#else
#include <simde/x86/fma.h>
#include "cmatrix.h"

// References:
// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-10/intrinsics.html

/* Basic AVX2, double, row-major & col-basis: */
inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  const simde__m256d B0 = simde_mm256_loadu_pd(&B[0][0]);
  const simde__m256d B1 = simde_mm256_loadu_pd(&B[1][0]);
  const simde__m256d B2 = simde_mm256_loadu_pd(&B[2][0]);
  const simde__m256d B3 = simde_mm256_loadu_pd(&B[3][0]);

  simde__m256d C0 = simde_mm256_mul_pd(simde_mm256_broadcast_sd(&A[0][0]), B0);
  C0 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[0][1]), B1, C0);
  C0 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[0][2]), B2, C0);
  C0 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[0][3]), B3, C0);

  simde__m256d C1 = simde_mm256_mul_pd(simde_mm256_broadcast_sd(&A[1][0]), B0);
  C1 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[1][1]), B1, C1);
  C1 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[1][2]), B2, C1);
  C1 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[1][3]), B3, C1);

  simde__m256d C2 = simde_mm256_mul_pd(simde_mm256_broadcast_sd(&A[2][0]), B0);
  C2 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[2][1]), B1, C2);
  C2 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[2][2]), B2, C2);
  C2 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[2][3]), B3, C2);

  simde__m256d C3 = simde_mm256_mul_pd(simde_mm256_broadcast_sd(&A[3][0]), B0);
  C3 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[3][1]), B1, C3);
  C3 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[3][2]), B2, C3);
  C3 = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[3][3]), B3, C3);

  simde_mm256_storeu_pd(&C[0][0], C0);
  simde_mm256_storeu_pd(&C[1][0], C1);
  simde_mm256_storeu_pd(&C[2][0], C2);
  simde_mm256_storeu_pd(&C[3][0], C3);
}
#endif
