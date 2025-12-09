/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <simde/hedley.h>
#include <simde/x86/fma.h>

namespace cml::detail {

/* Multiply a 3-element vector (v) with a 3x4 matrix (M) using single-precision
 * floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_13(const float* const v, simde__m128 M0, simde__m128 M1, simde__m128 M2)
  -> simde__m128
{
  /* x[0..3] = v[0] * M[0][0..3] */
  auto x = simde_mm_mul_ps(simde_mm_broadcast_ss(v + 0), M0);
  /* x[0..3] += v[1] * M[1][0..3] */
  x = simde_mm_fmadd_ps(simde_mm_broadcast_ss(v + 1), M1, x);
  /* x[0..3] += v[2] * M[2][0..3] */
  x = simde_mm_fmadd_ps(simde_mm_broadcast_ss(v + 2), M2, x);
  return x;
}

/* Multiply a 3-element vector (v) with a 3x4 matrix (M) using double-precision
 * floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_13(const double* const v, simde__m256d M0, simde__m256d M1, simde__m256d M2)
  -> simde__m256d
{
  /* x[0..3] = v[0] * M[0][0..3] */
  auto x = simde_mm256_mul_pd(simde_mm256_broadcast_sd(v + 0), M0);
  /* x[0..3] += v[1] * M[1][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 1), M1, x);
  /* x[0..3] += v[2] * M[2][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 2), M2, x);
  return x;
}

/* Multiply a 4-element vector (v) with a 4x4 matrix (M) using single-precision
 * floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14(const float* const v, simde__m128 M0, simde__m128 M1, simde__m128 M2,
  simde__m128 M3) -> simde__m128
{
  /* x[0..3] = v[0] * M[0][0..3] */
  auto x = simde_mm_mul_ps(simde_mm_broadcast_ss(v + 0), M0);
  /* x[0..3] += v[1] * M[1][0..3] */
  x = simde_mm_fmadd_ps(simde_mm_broadcast_ss(v + 1), M1, x);
  /* x[0..3] += v[2] * M[2][0..3] */
  x = simde_mm_fmadd_ps(simde_mm_broadcast_ss(v + 2), M2, x);
  /* x[0..3] += v[3] * M[3][0..3] */
  x = simde_mm_fmadd_ps(simde_mm_broadcast_ss(v + 3), M3, x);
  return x;
}

/* Multiply a 4-element vector (v) with a 4x4 matrix (M) using double-precision
 * floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14(const double* const v, simde__m256d M0, simde__m256d M1, simde__m256d M2,
  simde__m256d M3) -> simde__m256d
{
  /* x[0..3] = v[0] * M[0][0..3] */
  auto x = simde_mm256_mul_pd(simde_mm256_broadcast_sd(v + 0), M0);
  /* x[0..3] += v[1] * M[1][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 1), M1, x);
  /* x[0..3] += v[2] * M[2][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 2), M2, x);
  /* x[0..3] += v[3] * M[3][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 3), M3, x);
  return x;
}

}  // namespace cml::detail
