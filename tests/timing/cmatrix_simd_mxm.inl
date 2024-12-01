
/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#ifdef CML_DISABLE_SIMD
#  define CML_SIMD_SCALAR
#else

#  ifdef _MSC_VER
#    include <immintrin.h>

/* Assume SSE4.2 if SSE2 is supported (minimum requirement): */
#    if defined(_M_X64)
#      define __SSE4_2__ 1
#    elif defined(_M_IX86_FP)
#      if _M_IX86_FP >= 2
#        define __SSE4_2__ 1
#      endif
#    endif

#    if defined(__AVX2__)
#      define CML_SIMD_AVX2
#    elif defined(__SSE4_2__)
#      define CML_SIMD_SSE4_2
#    else
#      error "SSE4.2 or higher required"
#    endif

#  else
#    error "Unrecognized compiler"
#  endif

#endif

#include <ostream>
#include <cml/common/traits.h>

#include "cmatrix.h"

#if 0
struct matrix44d
{
  double& operator()(int i, int j) { return d[i][j]; }

  union
  {
    double d[4][4];
    __m256d m[4];
  };
};

/* Need some specializations for CML: */
namespace cml {

struct matrix44d_traits
{
  using value_type = double;
};

template<> struct traits_of<matrix44d>
{
  using type = matrix44d_traits;
};

namespace detail {

inline double&
get(::matrix44d& m, int i, int j)
{
  return m.d[i][j];
}

inline const double&
get(const ::matrix44d& m, int i, int j)
{
  return m.d[i][j];
}

}  // namespace detail
}  // namespace cml

inline std::ostream&
operator<<(std::ostream& os, const matrix44d& M)
{
  for(int i = 0; i < 4; ++i) {
    os << "[";
    for(int j = 0; j < 4; ++j) os << " " << M.d[i][j];
    os << " ]";
    if(i != 4 - 1) os << std::endl;
  }
  return os;
}
#endif

// References:
// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-10/intrinsics.html

/* Basic AVX2, double, row-major & col-basis: */
#if defined(CML_SIMD_AVX2)
inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
#  if 0
  const __m256d B0 = _mm256_loadu_pd(&B[0][0]);
  const __m256d B1 = _mm256_loadu_pd(&B[1][0]);
  const __m256d B2 = _mm256_loadu_pd(&B[2][0]);
  const __m256d B3 = _mm256_loadu_pd(&B[3][0]);

  __m256d C0 = _mm256_mul_pd(_mm256_broadcast_sd(&A[0][0]), B0);
  C0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[0][1]), B1, C0);
  C0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[0][2]), B2, C0);
  C0 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[0][3]), B3, C0);

  __m256d C1 = _mm256_mul_pd(_mm256_broadcast_sd(&A[1][0]), B0);
  C1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[1][1]), B1, C1);
  C1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[1][2]), B2, C1);
  C1 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[1][3]), B3, C1);

  __m256d C2 = _mm256_mul_pd(_mm256_broadcast_sd(&A[2][0]), B0);
  C2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[2][1]), B1, C2);
  C2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[2][2]), B2, C2);
  C2 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[2][3]), B3, C2);

  __m256d C3 = _mm256_mul_pd(_mm256_broadcast_sd(&A[3][0]), B0);
  C3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[3][1]), B1, C3);
  C3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[3][2]), B2, C3);
  C3 = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[3][3]), B3, C3);

  _mm256_storeu_pd(&C[0][0], C0);
  _mm256_storeu_pd(&C[1][0], C1);
  _mm256_storeu_pd(&C[2][0], C2);
  _mm256_storeu_pd(&C[3][0], C3);
#  endif

#  if 1
  const __m256d B0 = _mm256_loadu_pd(&B[0][0]);
  const __m256d B1 = _mm256_loadu_pd(&B[1][0]);
  const __m256d B2 = _mm256_loadu_pd(&B[2][0]);
  const __m256d B3 = _mm256_loadu_pd(&B[3][0]);

  __m256d C_row[4];
  for(int i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    C_row[i] = _mm256_mul_pd(_mm256_broadcast_sd(&A[i][0]), B0);

    /* row[0..3] += A[i][1] * B[1][0..3] */
    C_row[i] = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][1]), B1, C_row[i]);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    C_row[i] = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][2]), B2, C_row[i]);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    C_row[i] = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][3]), B3, C_row[i]);
  }

  for(int i = 0; i < 4; ++i) {
    /* C[i][0...3] = row[0..3] */
    _mm256_storeu_pd(&C[i][0], C_row[i]);
  }
#  endif

#  if 0
  /* Favor keeping B in registers, use AVX2 FMA: */
  __m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = _mm256_loadu_pd(&B[i][0]);
  }
  for(int i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    __m256d C_row = _mm256_mul_pd(B_row[0], _mm256_broadcast_sd(&A[i][0]));

    /* row[0..3] += A[i][1] * B[1][0..3] */
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][1]), B_row[1], C_row);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][2]), B_row[2], C_row);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A[i][3]), B_row[3], C_row);

    /* C[i][0...3] = row[0..3] */
    _mm256_storeu_pd(&C[i][0], C_row);
  }
#  endif

#  if 0
  /* Favor keeping B in registers: */
  __m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = _mm256_load_pd(reinterpret_cast<const double*>(&B[i][0]));
  }
  for(int i = 0; i < 4; ++i) {
    __m256d C_row = _mm256_mul_pd(B_row[0], _mm256_set1_pd(A[i][0]));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[1], _mm256_set1_pd(A[i][1])));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[2], _mm256_set1_pd(A[i][2])));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[3], _mm256_set1_pd(A[i][3])));
    _mm256_store_pd(&C[i][0], C_row);
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
  __m256d B_row[4];
  for(int i = 0; i < 4; ++i) {
    B_row[i] = _mm256_load_pd(&B[i][0]);
  }
  for(int i = 0; i < 4; ++i) {
    __m256d C_row = _mm256_mul_pd(B_row[0], _mm256_broadcast_sd(&A[i][0]));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[1], _mm256_broadcast_sd(&A[i][1])));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[2], _mm256_broadcast_sd(&A[i][2])));
    C_row =
      _mm256_add_pd(C_row, _mm256_mul_pd(B_row[3], _mm256_broadcast_sd(&A[i][3])));
    _mm256_store_pd(&C[i][0], C_row);
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

#  if 0
  for(int i = 0; i < 4; ++i) {
    __m256d C_row = _mm256_mul_pd(_mm256_broadcast_sd(&A.d[i][0]), B.m[0]);
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[i][1]), B.m[1], C_row);
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[i][2]), B.m[2], C_row);
    C_row = _mm256_fmadd_pd(_mm256_broadcast_sd(&A.d[i][3]), B.m[3], C_row);
    C.m[i] = C_row;
  }
#  endif
}
#elif defined(CML_SIMD_SSE4_2)

#  if 0

/* Row major: */
inline void mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{


#    if 0
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
#    endif




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

#    if 0
        const auto A00 = A[ii + 0][kk + 0];
        const auto A10 = A[ii + 1][kk + 0];
        const auto B00 = B[kk + 0][jj + 0];
        const auto B01 = B[kk + 0][jj + 1];

        C00 += A00 * B00;
        C01 += A00 * B01;
        C10 += A10 * B00;
        C11 += A10 * B01;
#    endif

        A0j = _mm_set1_pd(A[ii + 0][kk + 1]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 1]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk+1]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#    if 0
        const auto A01 = A[ii + 0][kk + 1];
        const auto A11 = A[ii + 1][kk + 1];
        const auto B10 = B[kk + 1][jj + 0];
        const auto B11 = B[kk + 1][jj + 1];

        C00 += A01 * B10;
        C01 += A01 * B11;
        C10 += A11 * B10;
        C11 += A11 * B11;
#    endif
      }

      _mm_store_pd(&C[ii][0], C0j);
      _mm_store_pd(&C[ii][1], C1j);
    }
  }
}

#  elif 1

/* Basic blocked 2x2 using SSE2: */
inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
{
  __m128d C0j, C1j, A0j, A1j, Bk;
  for(int ii = 0; ii < 4; ii += 2) {
    for(int jj = 0; jj < 4; jj += 2) {
      C0j = _mm_setzero_pd();
      C1j = _mm_setzero_pd();

      for(int kk = 0; kk < 4; kk += 2) {
        A0j = _mm_set1_pd(A[ii + 0][kk + 0]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 0]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk + 0]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#    if 0
        const auto A00 = A[ii + 0][kk + 0];
        const auto A10 = A[ii + 1][kk + 0];
        const auto B00 = B[kk + 0][jj + 0];
        const auto B01 = B[kk + 0][jj + 1];

        C00 += A00 * B00;
        C01 += A00 * B01;
        C10 += A10 * B00;
        C11 += A10 * B01;
#    endif

        A0j = _mm_set1_pd(A[ii + 0][kk + 1]);
        A1j = _mm_set1_pd(A[ii + 1][kk + 1]);
        Bk = _mm_loadu_pd(reinterpret_cast<const double*>(&B[kk + 1]));
        C0j = _mm_add_pd(C0j, _mm_mul_pd(A0j, Bk));
        C1j = _mm_add_pd(C1j, _mm_mul_pd(A1j, Bk));

#    if 0
        const auto A01 = A[ii + 0][kk + 1];
        const auto A11 = A[ii + 1][kk + 1];
        const auto B10 = B[kk + 1][jj + 0];
        const auto B11 = B[kk + 1][jj + 1];

        C00 += A01 * B10;
        C01 += A01 * B11;
        C10 += A11 * B10;
        C11 += A11 * B11;
#    endif
      }

      _mm_store_pd(&C[ii][0], C0j);
      _mm_store_pd(&C[ii][1], C1j);
    }
  }
}
#  elif 0
/* Basic 2x2 blocked multiply: */
inline void
mxm_4x4(matrix44d& C, const matrix44d& A, const matrix44d& B)
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
#  endif

#else
#  error "No SIMD intrinsics defined?"
#endif
