
/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#pragma once

#include "cmatrix.h"

#ifdef CML_DISABLE_SIMD
# define CML_SIMD_SCALAR
#else

#ifdef _MSC_VER
#include <immintrin.h>

/* Assume SSE4.2 if SSE2 is supported (minimum requirement): */
#if defined(_M_X64)
# define __SSE4_2__ 1
#elif defined(_M_IX86_FP)
# if _M_IX86_FP >= 2
# define __SSE4_2__ 1
# endif
#endif

#if defined(__AVX__)
# define CML_SIMD_AVX
#elif defined(__SSE4_2__)
# define CML_SIMD_SSE4_2
#else
# error "SSE4.2 or higher required"
#endif

#else
#error "Unrecognized compiler"
#endif

#endif


/* Basic AVX, double, row-major & col-basis, unaligned access: */
#if defined(CML_SIMD_AVX)
inline void mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  /* Favor keeping B in registers: */
  __m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = _mm256_load_pd(reinterpret_cast<const double*>(&B[i][0]));
  }
  for(int i = 0; i < 4; ++i) {
     __m256d C_row = _mm256_mul_pd(B_row[0], _mm256_set1_pd(A[i][0]));
    C_row = _mm256_add_pd(C_row, _mm256_mul_pd(B_row[1], _mm256_set1_pd(A[i][1])));
    C_row = _mm256_add_pd(C_row, _mm256_mul_pd(B_row[2], _mm256_set1_pd(A[i][2])));
    C_row = _mm256_add_pd(C_row, _mm256_mul_pd(B_row[3], _mm256_set1_pd(A[i][3])));
    _mm256_store_pd(&C[i][0], C_row);
  }
}
#elif defined(CML_SIMD_SSE4_2)

#if 0

/* Row major: */
inline void mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{



#if 0
  C.zero();

  __m128d A0[2], A1[2];
  __m128d B0[2], B1[2];
  __m128d C[2];

  /* Load upper half of B into 4 registers (2 blocks of 2x2): */
  B0[0] = _mm_loadu_pd(&B[0][0]); B0[1] = _mm_loadu_pd(&B[0][2]);
  B1[0] = _mm_loadu_pd(&B[1][0]); B1[1] = _mm_loadu_pd(&B[1][2]);

  /* Load a00..a11: */
  A0[0] = _mm_set1_pd(A[0][0]); A0[1] = _mm_set1_pd(A[0][1]);
  A1[0] = _mm_set1_pd(A[1][0]); A0[1] = _mm_set1_pd(A[1][1]);

  /* Load and update c00..c11: */
  C[0] = _mm_loadu_pd(&C[0][0]);
  C[0] = _mm_add_pd(C[0], _mm_mul_pd(A0[0], B0[0]));
  C[0] = _mm_add_pd(C[0], _mm_mul_pd(A0[1], B1[0]));
  _mm_store_pd(&C[0][0], C[0]);

  C[1] = _mm_loadu_pd(&C[1][0]);
  C[1] = _mm_add_pd(C[0], _mm_mul_pd(A1[0], B0[0]));
  C[1] = _mm_add_pd(C[1], _mm_mul_pd(A1[1], B1[0]));
  _mm_store_pd(&C[1][0], C[1]);
#endif




  __m128d C0j, C1j, A0j, A1j, Bk;
  for(int ii = 0; ii < 4; ii += 2) {
    for(int jj = 0; jj < 4; jj += 2) {
      C0j = _mm_setzero_pd();
      C1j = _mm_setzero_pd();

      for(int kk = 0; kk < 4; kk += 2) {
        A0j = _mm_set1_pd(A[ii + 0][kk + 0]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 0]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk+0]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#if 0
        const auto A00 = A[ii + 0][kk + 0];
        const auto A10 = A[ii + 1][kk + 0];
        const auto B00 = B[kk + 0][jj + 0];
        const auto B01 = B[kk + 0][jj + 1];

        C00 += A00 * B00;
        C01 += A00 * B01;
        C10 += A10 * B00;
        C11 += A10 * B01;
#endif

        A0j = _mm_set1_pd(A[ii + 0][kk + 1]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 1]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk+1]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#if 0
        const auto A01 = A[ii + 0][kk + 1];
        const auto A11 = A[ii + 1][kk + 1];
        const auto B10 = B[kk + 1][jj + 0];
        const auto B11 = B[kk + 1][jj + 1];

        C00 += A01 * B10;
        C01 += A01 * B11;
        C10 += A11 * B10;
        C11 += A11 * B11;
#endif
      }

      _mm_store_pd(&C[ii][0], C0j);
      _mm_store_pd(&C[ii][1], C1j);
    }
  }
}

#elif 1

/* Basic blocked 2x2 using SSE2: */
inline void mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  __m128d C0j, C1j, A0j, A1j, Bk;
  for(int ii = 0; ii < 4; ii += 2) {
    for(int jj = 0; jj < 4; jj += 2) {
      C0j = _mm_setzero_pd();
      C1j = _mm_setzero_pd();

      for(int kk = 0; kk < 4; kk += 2) {
        A0j = _mm_set1_pd(A[ii + 0][kk + 0]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 0]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk+0]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#if 0
        const auto A00 = A[ii + 0][kk + 0];
        const auto A10 = A[ii + 1][kk + 0];
        const auto B00 = B[kk + 0][jj + 0];
        const auto B01 = B[kk + 0][jj + 1];

        C00 += A00 * B00;
        C01 += A00 * B01;
        C10 += A10 * B00;
        C11 += A10 * B01;
#endif

        A0j = _mm_set1_pd(A[ii + 0][kk + 1]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 1]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk+1]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#if 0
        const auto A01 = A[ii + 0][kk + 1];
        const auto A11 = A[ii + 1][kk + 1];
        const auto B10 = B[kk + 1][jj + 0];
        const auto B11 = B[kk + 1][jj + 1];

        C00 += A01 * B10;
        C01 += A01 * B11;
        C10 += A11 * B10;
        C11 += A11 * B11;
#endif
      }

      _mm_store_pd(&C[ii][0], C0j);
      _mm_store_pd(&C[ii][1], C1j);
    }
  }
}
#elif 0
/* Basic 2x2 blocked multiply: */
inline void mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  for(int ii = 0; ii < 4; ii += 2) {
    for(int jj = 0; jj < 4; jj += 2) {

      auto C00 = 0., C01 = 0., C10 = 0., C11 = 0.;
      for(int kk = 0; kk < 4; kk += 2) {
        const auto A00 = A[ii + 0][kk + 0];
        const auto A10 = A[ii + 1][kk + 0];
        const auto B00 = B[kk + 0][jj + 0];
        const auto B01 = B[kk + 0][jj + 1];

        C00 += A00 * B00;
        C01 += A00 * B01;
        C10 += A10 * B00;
        C11 += A10 * B01;


        const auto A01 = A[ii + 0][kk + 1];
        const auto A11 = A[ii + 1][kk + 1];
        const auto B10 = B[kk + 1][jj + 0];
        const auto B11 = B[kk + 1][jj + 1];

        C00 += A01 * B10;
        C01 += A01 * B11;
        C10 += A11 * B10;
        C11 += A11 * B11;
      }

      C[ii + 0][jj + 0] = C00;
      C[ii + 0][jj + 1] = C01;
      C[ii + 1][jj + 0] = C10;
      C[ii + 1][jj + 1] = C11;
    }
  }
}
#endif

#else
#error "No SIMD intrinsics defined?"
#endif
