/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <simde/hedley.h>
#include <simde/x86/fma.h>

namespace cml::detail {

/* Multiply a 3-element "row" vector (v) with a 3x3 row-major matrix (M) using
 * single-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_13_rr(const float* const v, simde__m128 M0, simde__m128 M1, simde__m128 M2)
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

/* Multiply a 3-element vector (v) with a 3x3 row-major matrix (M) using
 * double-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_13_rr(const double* const v, simde__m256d M0, simde__m256d M1,
  simde__m256d M2) -> simde__m256d
{
  /* x[0..3] = v[0] * M[0][0..3] */
  auto x = simde_mm256_mul_pd(simde_mm256_broadcast_sd(v + 0), M0);
  /* x[0..3] += v[1] * M[1][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 1), M1, x);
  /* x[0..3] += v[2] * M[2][0..3] */
  x = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(v + 2), M2, x);
  return x;
}

/* Multiply a 4-element vector (v) with a row-major 4x4 matrix (M) using
 * single-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14_rr(const float* const v, simde__m128 M0, simde__m128 M1, simde__m128 M2,
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

/* Multiply a 4-element vector (v) with a 4x4 col-major matrix (M) using
 * float-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14_rc(const float* const v, simde__m128 M0, simde__m128 M1, simde__m128 M2,
  simde__m128 M3) -> simde__m128
{
  const auto y = simde_mm_loadu_ps(v);

  /* m[0..3] = v[0..3] * M[0..3] */
  const auto m0 = simde_mm_mul_ps(y, M0);

  /* p0[0,1,2,3] = m[2,3,0,1] */
  const auto p00 = simde_mm_shuffle_ps(m0, m0, 0b0100'1110);

  /* s0[0,1,2,3] = m[0,1,2,3] + p0[0,1,2,3]
   *             = m[0,1,2,3] + m[2,3,0,1]
   *             = {m[0]+m[2], m[1]+m[3], m[0]+m[2], m[1]+m[3]}
   *             = {m02, m13, m02, m13}
   */
  const auto s00 = simde_mm_add_ps(m0, p00);

  /* p0[0,1,2,3] = s0[1,0,3,2]
   *             = {m13, m02, m13, m02}
   */
  const auto p01 = simde_mm_shuffle_ps(s00, s00, 0b1011'0001);

  /* x[0,1,2,3] = s0[0,1,2,3] + p0[0,1,2,3]
   *            = {m02+m13, m13+m02, m02+m13, m13+m02}
   *            = {m0123, ... }
   */
  const auto x0 = simde_mm_add_ps(s00, p01);

  /* Compute x1, x2, and x3: */
  const auto m1 = simde_mm_mul_ps(y, M1);
  const auto p10 = simde_mm_shuffle_ps(m1, m1, 0b0100'1110);
  const auto s10 = simde_mm_add_ps(m1, p10);
  const auto p11 = simde_mm_shuffle_ps(s10, s10, 0b1011'0001);
  const auto x1 = simde_mm_add_ps(s10, p11);

  const auto m2 = simde_mm_mul_ps(y, M2);
  const auto p20 = simde_mm_shuffle_ps(m2, m2, 0b0100'1110);
  const auto s20 = simde_mm_add_ps(m2, p20);
  const auto p21 = simde_mm_shuffle_ps(s20, s20, 0b1011'0001);
  const auto x2 = simde_mm_add_ps(s20, p21);

  const auto m3 = simde_mm_mul_ps(y, M3);
  const auto p30 = simde_mm_shuffle_ps(m3, m3, 0b0100'1110);
  const auto s30 = simde_mm_add_ps(m3, p30);
  const auto p31 = simde_mm_shuffle_ps(s30, s30, 0b1011'0001);
  const auto x3 = simde_mm_add_ps(s30, p31);

  /* Combine sums into the final result vector: */

  /* r01 = { x0[0], x1[1], x0[2], x1[3] }
   *     = { m0:0123, m1:0123, m0:0123, m1:0123 }
   */
  const auto r01 = simde_mm_blend_ps(x0, x1, 0b1010);

  /* r23 = { x2[0], x3[1], x2[2], x3[3] }
   *     = { m2:0123, m3:0123, m2:0123, m3:0123 }
   */
  const auto r23 = simde_mm_blend_ps(x2, x3, 0b1010);

  /* r0123 = { r01[0], r01[1], r23[0], r23[1] } */
  return simde_mm_blend_ps(r01, r23, 0b1100);
}

/* Multiply a 4-element vector (v) with a 4x4 row-major matrix (M) using
 * double-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14_rr(const double* const v, simde__m256d M0, simde__m256d M1,
  simde__m256d M2, simde__m256d M3) -> simde__m256d
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

/* Multiply a 4-element vector (v) with a 4x4 col-major matrix (M) using
 * double-precision floats.
 */
static HEDLEY_ALWAYS_INLINE auto
vxm_14_rc(const double* const v, simde__m256d M0, simde__m256d M1,
  simde__m256d M2, simde__m256d M3) -> simde__m256d
{
  const auto y = simde_mm256_loadu_pd(v);

#if 1
  /* This version saves an add_pd for each pair of rows: */

  /* m[0..3] = v[0..3] * M[0..3] */
  const auto m0 = simde_mm256_mul_pd(y, M0);
  const auto m1 = simde_mm256_mul_pd(y, M1);

  /* p0[0,1,2,3] = m[1,0,3,2] */
  const auto p0 = simde_mm256_shuffle_pd(m0, m0, 0b0101);
  const auto p1 = simde_mm256_shuffle_pd(m1, m1, 0b0101);

  /* s0[0,1,2,3] = m[0,1,2,3] + p0[0,1,2,3]
   *             = m[0,1,2,3] + m[1,0,3,2]
   *             = {m[0]+m[1], m[0]+m[1], m[2]+m[3], m[2]+m[3]}
   *             = {m01, m01, m23, m23}
   */
  const auto s0 = simde_mm256_add_pd(m0, p0);
  const auto s1 = simde_mm256_add_pd(m1, p1);

  /* Combine the pairwise sums of s0 and s1 into a single register: */

  /* l01 = {m0:01, m1:01, m0:23, m1:23} */
  const auto l01 = simde_mm256_unpacklo_pd(s0, s1);

  /* p01 = {m0:23, m1:23, m0:01, m0:23} */
  const auto p01 = simde_mm256_permute2f128_pd(l01, l01, 0x1);

  /* s01 = {m0:0123, m1:0123, m0:0123, m1:0123 } */
  const auto s01 = simde_mm256_add_pd(l01, p01);

  /* Same for rows 2 and 3: */
  const auto m2 = simde_mm256_mul_pd(y, M2);
  const auto m3 = simde_mm256_mul_pd(y, M3);
  const auto p2 = simde_mm256_shuffle_pd(m2, m2, 0b0101);
  const auto p3 = simde_mm256_shuffle_pd(m3, m3, 0b0101);
  const auto s2 = simde_mm256_add_pd(m2, p2);
  const auto s3 = simde_mm256_add_pd(m3, p3);
  const auto l23 = simde_mm256_unpacklo_pd(s2, s3);
  const auto p23 = simde_mm256_permute2f128_pd(l23, l23, 0x1);
  const auto s23 = simde_mm256_add_pd(l23, p23);

  /* r0123 = { s01[0], s01[1], s23[2], r23[3] } */
  return simde_mm256_blend_pd(s01, s23, 0b1100);
#else
  /* m[0..3] = v[0..3] * M[0..3] */
  const auto m0 = simde_mm256_mul_pd(y, M0);

  /* p0[0,1,2,3] = m[2,3,0,1] */
  const auto p00 = simde_mm256_permute2f128_pd(m0, m0, 0x1);

  /* s0[0,1,2,3] = m[0,1,2,3] + p0[0,1,2,3]
   *             = m[0,1,2,3] + m[2,3,0,1]
   *             = {m[0]+m[2], m[1]+m[3], m[0]+m[2], m[1]+m[3]}
   *             = {m02, m13, m02, m13}
   */
  const auto s00 = simde_mm256_add_pd(m0, p00);

  /* p0[0,1,2,3] = s0[1,0,3,2]
   *             = {m13, m02, m13, m02}
   */
  const auto p01 = simde_mm256_shuffle_pd(s00, s00, 0b0101);

  /* x[0,1,2,3] = s0[0,1,2,3] + p0[0,1,2,3]
   *            = {m02+m13, m13+m02, m02+m13, m13+m02}
   *            = {m0123, ... }
   */
  const auto x0 = simde_mm256_add_pd(s00, p01);

  /* Compute x1, x2, and x3: */
  const auto m1 = simde_mm256_mul_pd(y, M1);
  const auto p10 = simde_mm256_permute2f128_pd(m1, m1, 0x1);
  const auto s10 = simde_mm256_add_pd(m1, p10);
  const auto p11 = simde_mm256_shuffle_pd(s10, s10, 0b0101);
  const auto x1 = simde_mm256_add_pd(s10, p11);

  const auto m2 = simde_mm256_mul_pd(y, M2);
  const auto p20 = simde_mm256_permute2f128_pd(m2, m2, 0x1);
  const auto s20 = simde_mm256_add_pd(m2, p20);
  const auto p21 = simde_mm256_shuffle_pd(s20, s20, 0b0101);
  const auto x2 = simde_mm256_add_pd(s20, p21);

  const auto m3 = simde_mm256_mul_pd(y, M3);
  const auto p30 = simde_mm256_permute2f128_pd(m3, m3, 0x1);
  const auto s30 = simde_mm256_add_pd(m3, p30);
  const auto p31 = simde_mm256_shuffle_pd(s30, s30, 0b0101);
  const auto x3 = simde_mm256_add_pd(s30, p31);

  /* Combine sums into the final result vector: */

  /* r01 = { x0[0], x1[1], x0[2], x1[3] }
   *     = { m0:0123, m1:0123, m0:0123, m1:0123 }
   */
  const auto r01 = simde_mm256_blend_pd(x0, x1, 0b1010);

  /* r23 = { x2[0], x3[1], x2[2], x3[3] }
   *     = { m2:0123, m3:0123, m2:0123, m3:0123 }
   */
  const auto r23 = simde_mm256_blend_pd(x2, x3, 0b1010);

  /* r0123 = { r01[0], r01[1], r23[0], r23[1] } */
  return simde_mm256_blend_pd(r01, r23, 0b1100);
#endif
}

}  // namespace cml::detail
