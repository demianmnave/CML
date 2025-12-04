
/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#ifdef CML_DISABLE_SIMD
#  define CML_SIMD_SCALAR
#else
#  include <simde/x86/fma.h>
#  include "cmatrix.h"

// References:
// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-10/intrinsics.html

/* Basic AVX2, double, row-major & col-basis: */
inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
#  if 1
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
#  endif

#  if 0
  // Unrolling seems to be slightly faster.
  const simde__m256d B0 = simde_mm256_loadu_pd(&B[0][0]);
  const simde__m256d B1 = simde_mm256_loadu_pd(&B[1][0]);
  const simde__m256d B2 = simde_mm256_loadu_pd(&B[2][0]);
  const simde__m256d B3 = simde_mm256_loadu_pd(&B[3][0]);

  simde__m256d C_row[4];
  for(int i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    C_row[i] = simde_mm256_mul_pd(simde_mm256_broadcast_sd(&A[i][0]), B0);

    /* row[0..3] += A[i][1] * B[1][0..3] */
    C_row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][1]), B1, C_row[i]);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    C_row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][2]), B2, C_row[i]);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    C_row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][3]), B3, C_row[i]);
  }

  for(int i = 0; i < 4; ++i) {
    /* C[i][0...3] = row[0..3] */
    simde_mm256_storeu_pd(&C[i][0], C_row[i]);
  }
#  endif

#  if 0
  /* Favor keeping B in registers, use AVX2 FMA: */
  // Note: Interleaving loads, computes, and stores is slower than load-all, compute-all, store-all.
  simde__m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = simde_mm256_loadu_pd(&B[i][0]);
  }
  for(int i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    simde__m256d C_row = simde_mm256_mul_pd(B_row[0], simde_mm256_broadcast_sd(&A[i][0]));

    /* row[0..3] += A[i][1] * B[1][0..3] */
    C_row = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][1]), B_row[1], C_row);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    C_row = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][2]), B_row[2], C_row);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    C_row = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(&A[i][3]), B_row[3], C_row);

    /* C[i][0...3] = row[0..3] */
    simde_mm256_storeu_pd(&C[i][0], C_row);
  }
#  endif

#  if 0
  /* Favor keeping B in registers: */
  simde__m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = simde_mm256_load_pd(reinterpret_cast<const double*>(&B[i][0]));
  }
  for(int i = 0; i < 4; ++i) {
    simde__m256d C_row = simde_mm256_mul_pd(B_row[0], simde_mm256_set1_pd(A[i][0]));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[1], simde_mm256_set1_pd(A[i][1])));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[2], simde_mm256_set1_pd(A[i][2])));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[3], simde_mm256_set1_pd(A[i][3])));
    simde_mm256_store_pd(&C[i][0], C_row);
  }
#  endif

#  if 0
  // Note: much slower than code above.
  // https://github.com/romz-pl/matrix-matrix-multiply/blob/main/src/dgemm_avx256.cpp
  for(uint32_t i = 0; i < 4; ++i) {
    for(uint32_t j = 0; j < 4; ++j) {
      __m256d c0 = _mm256_set_pd(0., 0., 0., 0.);
      for(uint32_t k = 0; k < 4; k++) {
        c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
          _mm256_mul_pd(_mm256_load_pd(&A[i][k]),
            _mm256_broadcast_sd(&B[k][j])));
      }
      _mm256_store_pd(&C[i][j], c0); /* C[i][j] = c0 */
    }
  }

#  endif

#  if 0
  // Note: broadcast_sd and set1_pd seem to have similar performance.
  /* Favor keeping B in registers (broadcast version): */
  simde__m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = simde_mm256_load_pd(&B[i][0]);
  }
  for(int i = 0; i < 4; ++i) {
    simde__m256d C_row = simde_mm256_mul_pd(B_row[0], simde_mm256_broadcast_sd(&A[i][0]));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[1], simde_mm256_broadcast_sd(&A[i][1])));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[2], simde_mm256_broadcast_sd(&A[i][2])));
    C_row =
      simde_mm256_add_pd(C_row, simde_mm256_mul_pd(B_row[3], simde_mm256_broadcast_sd(&A[i][3])));
    simde_mm256_store_pd(&C[i][0], C_row);
  }
#  endif

#  if 0
  // Much slower than caching B in registers.
  /* Load B, use AVX2 FMA: */
  for(int i = 0; i < 4; ++i) {
    __m256d C_row = _mm256_mul_pd(
      _mm256_set1_pd(A[i][0]),
     _mm256_load_pd(&B[0][0])
    );
    C_row = _mm256_fmadd_pd(
      _mm256_set1_pd(A[i][1]),
     _mm256_load_pd(&B[1][0]),
      C_row);
    C_row = _mm256_fmadd_pd(
      _mm256_set1_pd(A[i][2]),
     _mm256_load_pd(&B[2][0]),
      C_row);
    C_row = _mm256_fmadd_pd(
      _mm256_set1_pd(A[i][3]),
     _mm256_load_pd(&B[3][0]),
      C_row);
    _mm256_store_pd(&C[i][0], C_row);
  }
#  endif

#  if 0
    __m256d C_row0 = _mm256_mul_pd(_mm256_broadcast_sd(&A.d[0][0]), B.m[0]);
    C_row0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[0][1]), B.m[1], C_row0);
    C_row0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[0][2]), B.m[2], C_row0);
    C_row0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[0][3]), B.m[3], C_row0);

    __m256d C_row1 = _mm256_mul_pd(_mm256_broadcast_sd(&A.d[1][0]), B.m[0]);
    C_row1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[1][1]), B.m[1], C_row1);
    C_row1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[1][2]), B.m[2], C_row1);
    C_row1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[1][3]), B.m[3], C_row1);

    __m256d C_row2 = _mm256_mul_pd(_mm256_broadcast_sd(&A.d[2][0]), B.m[0]);
    C_row2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[2][1]), B.m[1], C_row2);
    C_row2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[2][2]), B.m[2], C_row2);
    C_row2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[2][3]), B.m[3], C_row2);

    __m256d C_row3 = _mm256_mul_pd(_mm256_broadcast_sd(&A.d[3][0]), B.m[0]);
    C_row3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[3][1]), B.m[1], C_row3);
    C_row3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[3][2]), B.m[2], C_row3);
    C_row3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[3][3]), B.m[3], C_row3);

    C.m[0] = C_row0;
    C.m[1] = C_row1;
    C.m[2] = C_row2;
    C.m[3] = C_row3;
#  endif
}
#endif
