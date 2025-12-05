/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/detail/resize.h>

namespace cml::detail {

/* Default matrix product. */
template<class Sub1, class Sub2>
auto
matrix_product(const Sub1& sub1,
  const Sub2& sub2) -> matrix_inner_product_promote_t<actual_type_of_t<Sub1>,
  actual_type_of_t<Sub2>>
{
  using result_type = matrix_inner_product_promote_t<actual_type_of_t<Sub1>,
    actual_type_of_t<Sub2>>;
  cml::check_same_inner_size(sub1, sub2);

  result_type M;
  detail::resize(M, array_rows_of(sub1), array_cols_of(sub2));
  for(int i = 0; i < M.rows(); ++i) {
    for(int j = 0; j < M.cols(); ++j) {
      auto m = sub1(i, 0) * sub2(0, j);
      for(int k = 1; k < sub1.cols(); ++k) m += sub1(i, k) * sub2(k, j);
      M(i, j) = m;
    }
  }
  return M;
}

}  // namespace cml::detail

#ifndef CML_DISABLE_SIMD
#include <simde/x86/fma.h>
#include <cml/matrix/fixed_compiled.h>

namespace cml::detail {

/* AVX2 4x4 float row-major matrix product. */
template<class S, class Basis1, class Basis2>
auto
matrix_product(
  // clang-format off
  const matrix<float, compiled<4, 4, S>, Basis1, row_major>& sub1,
  const matrix<float, compiled<4, 4, S>, Basis2, row_major>& sub2
  // clang-format on
  ) -> matrix<float, compiled<4, 4, S>, basis_tag_promote_t<Basis1, Basis2>,
  row_major>
{
  using result_type = matrix<float, compiled<4, 4, S>,
    basis_tag_promote_t<Basis1, Basis2>, row_major>;

  const auto* A = sub1.data();
  const auto* B = sub2.data();

  /* Cache sub2: */
  const auto B0 = simde_mm_loadu_ps(B + (0 << 2));
  const auto B1 = simde_mm_loadu_ps(B + (1 << 2));
  const auto B2 = simde_mm_loadu_ps(B + (2 << 2));
  const auto B3 = simde_mm_loadu_ps(B + (3 << 2));

  /* row[0..3] = A[i][0] * B[0][0..3] */
  auto row0 = simde_mm_mul_ps(simde_mm_broadcast_ss(A + (0 << 2) + 0), B0);
  /* row[0..3] += A[i][1] * B[1][0..3] */
  row0 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (0 << 2) + 1), B1, row0);
  /* row[0..3] += A[i][2] * B[2][0..3] */
  row0 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (0 << 2) + 2), B2, row0);
  /* row[0..3] += A[i][3] * B[3][0..3] */
  row0 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (0 << 2) + 3), B3, row0);

  auto row1 = simde_mm_mul_ps(simde_mm_broadcast_ss(A + (1 << 2) + 0), B0);
  row1 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (1 << 2) + 1), B1, row1);
  row1 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (1 << 2) + 2), B2, row1);
  row1 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (1 << 2) + 3), B3, row1);

  auto row2 = simde_mm_mul_ps(simde_mm_broadcast_ss(A + (2 << 2) + 0), B0);
  row2 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (2 << 2) + 1), B1, row2);
  row2 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (2 << 2) + 2), B2, row2);
  row2 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (2 << 2) + 3), B3, row2);

  auto row3 = simde_mm_mul_ps(simde_mm_broadcast_ss(A + (3 << 2) + 0), B0);
  row3 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (3 << 2) + 1), B1, row3);
  row3 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (3 << 2) + 2), B2, row3);
  row3 = simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (3 << 2) + 3), B3, row3);

  result_type result;
  auto* M = result.data();
  simde_mm_storeu_ps(M + (0 << 2), row0);
  simde_mm_storeu_ps(M + (1 << 2), row1);
  simde_mm_storeu_ps(M + (2 << 2), row2);
  simde_mm_storeu_ps(M + (3 << 2), row3);

  return result;
}

/* AVX2 4x4 float col-major matrix product. */
template<class S, class Basis1, class Basis2>
auto
matrix_product(
  // clang-format off
  const matrix<float, compiled<4, 4, S>, Basis1, col_major>& sub1,
  const matrix<float, compiled<4, 4, S>, Basis2, col_major>& sub2
  // clang-format on
  ) -> matrix<float, compiled<4, 4, S>, basis_tag_promote_t<Basis1, Basis2>,
  col_major>
{
  using result_type = matrix<float, compiled<4, 4, S>,
    basis_tag_promote_t<Basis1, Basis2>, col_major>;

  const auto* A = sub1.data();
  const auto* B = sub2.data();

  /* Cache sub1: */
  const simde__m128 A0 = simde_mm_loadu_ps(A + (0 << 2));
  const simde__m128 A1 = simde_mm_loadu_ps(A + (1 << 2));
  const simde__m128 A2 = simde_mm_loadu_ps(A + (2 << 2));
  const simde__m128 A3 = simde_mm_loadu_ps(A + (3 << 2));

  auto col0 = simde_mm_mul_ps(A0, simde_mm_broadcast_ss(B + (0 << 2) + 0));
  col0 = simde_mm_fmadd_ps(A1, simde_mm_broadcast_ss(B + (0 << 2) + 1), col0);
  col0 = simde_mm_fmadd_ps(A2, simde_mm_broadcast_ss(B + (0 << 2) + 2), col0);
  col0 = simde_mm_fmadd_ps(A3, simde_mm_broadcast_ss(B + (0 << 2) + 3), col0);

  auto col1 = simde_mm_mul_ps(A0, simde_mm_broadcast_ss(B + (1 << 2) + 0));
  col1 = simde_mm_fmadd_ps(A1, simde_mm_broadcast_ss(B + (1 << 2) + 1), col1);
  col1 = simde_mm_fmadd_ps(A2, simde_mm_broadcast_ss(B + (1 << 2) + 2), col1);
  col1 = simde_mm_fmadd_ps(A3, simde_mm_broadcast_ss(B + (1 << 2) + 3), col1);

  auto col2 = simde_mm_mul_ps(A0, simde_mm_broadcast_ss(B + (2 << 2) + 0));
  col2 = simde_mm_fmadd_ps(A1, simde_mm_broadcast_ss(B + (2 << 2) + 1), col2);
  col2 = simde_mm_fmadd_ps(A2, simde_mm_broadcast_ss(B + (2 << 2) + 2), col2);
  col2 = simde_mm_fmadd_ps(A3, simde_mm_broadcast_ss(B + (2 << 2) + 3), col2);

  auto col3 = simde_mm_mul_ps(A0, simde_mm_broadcast_ss(B + (3 << 2) + 0));
  col3 = simde_mm_fmadd_ps(A1, simde_mm_broadcast_ss(B + (3 << 2) + 1), col3);
  col3 = simde_mm_fmadd_ps(A2, simde_mm_broadcast_ss(B + (3 << 2) + 2), col3);
  col3 = simde_mm_fmadd_ps(A3, simde_mm_broadcast_ss(B + (3 << 2) + 3), col3);

  result_type result;
  auto* M = result.data();
  simde_mm_storeu_ps(M + (0 << 2), col0);
  simde_mm_storeu_ps(M + (1 << 2), col1);
  simde_mm_storeu_ps(M + (2 << 2), col2);
  simde_mm_storeu_ps(M + (3 << 2), col3);

  return result;
}

/* AVX2 3x3 double row-major matrix product. */
template<class S, class Basis1, class Basis2>
auto
matrix_product(
  // clang-format off
  const matrix<double, compiled<3, 3, S>, Basis1, row_major>& sub1,
  const matrix<double, compiled<3, 3, S>, Basis2, row_major>& sub2
  // clang-format on
  ) -> matrix<double, compiled<3, 3, S>, basis_tag_promote_t<Basis1, Basis2>,
  row_major>
{
  using result_type = matrix<double, compiled<3, 3, S>,
    basis_tag_promote_t<Basis1, Basis2>, row_major>;

  const auto* A = sub1.data();
  const auto* B = sub2.data();

  /* Cache sub2: */
  const auto B0 =
    simde_mm256_set_pd(0., B[0 * 3 + 2], B[0 * 3 + 1], B[0 * 3 + 0]);
  const auto B1 =
    simde_mm256_set_pd(0., B[1 * 3 + 2], B[1 * 3 + 1], B[1 * 3 + 0]);
  const auto B2 =
    simde_mm256_set_pd(0., B[2 * 3 + 2], B[2 * 3 + 1], B[2 * 3 + 0]);

  /* row[0..2] = A[i][0] * B[0][0..2] */
  auto row0 = simde_mm256_mul_pd(simde_mm256_set1_pd(A[0 * 3 + 0]), B0);
  /* row[0..2] += A[i][1] * B[1][0..3] */
  row0 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[0 * 3 + 1]), B1, row0);
  /* row[0..2] += A[i][2] * B[2][0..3] */
  row0 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[0 * 3 + 2]), B2, row0);

  auto row1 = simde_mm256_mul_pd(simde_mm256_set1_pd(A[1 * 3 + 0]), B0);
  row1 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[1 * 3 + 1]), B1, row1);
  row1 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[1 * 3 + 2]), B2, row1);

  auto row2 = simde_mm256_mul_pd(simde_mm256_set1_pd(A[2 * 3 + 0]), B0);
  row2 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[2 * 3 + 1]), B1, row2);
  row2 = simde_mm256_fmadd_pd(simde_mm256_set1_pd(A[2 * 3 + 2]), B2, row2);

  /* Store only the low 3 elements of each row: */
  result_type result;
  auto* M = result.data();
  const auto mask = simde_mm256_set_epi64x(0, -1, -1, -1);
  simde_mm256_maskstore_pd(M + 0 * 3 + 0, mask, row0);
  simde_mm256_maskstore_pd(M + 1 * 3 + 0, mask, row1);
  simde_mm256_maskstore_pd(M + 2 * 3 + 0, mask, row2);
  return result;
}

/* AVX2 4x4 double row-major matrix product. */
template<class S, class Basis1, class Basis2>
auto
matrix_product(
  // clang-format off
  const matrix<double, compiled<4, 4, S>, Basis1, row_major>& sub1,
  const matrix<double, compiled<4, 4, S>, Basis2, row_major>& sub2
  // clang-format on
  ) -> matrix<double, compiled<4, 4, S>, basis_tag_promote_t<Basis1, Basis2>,
  row_major>
{
  using result_type = matrix<double, compiled<4, 4, S>,
    basis_tag_promote_t<Basis1, Basis2>, row_major>;

  const auto* A = sub1.data();
  const auto* B = sub2.data();

  /* Cache sub2: */
  const auto B0 = simde_mm256_loadu_pd(B + (0 << 2));
  const auto B1 = simde_mm256_loadu_pd(B + (1 << 2));
  const auto B2 = simde_mm256_loadu_pd(B + (2 << 2));
  const auto B3 = simde_mm256_loadu_pd(B + (3 << 2));

  /* row[0..3] = A[i][0] * B[0][0..3] */
  auto row0 =
    simde_mm256_mul_pd(simde_mm256_broadcast_sd(A + (0 << 2) + 0), B0);
  /* row[0..3] += A[i][1] * B[1][0..3] */
  row0 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (0 << 2) + 1), B1, row0);
  /* row[0..3] += A[i][2] * B[2][0..3] */
  row0 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (0 << 2) + 2), B2, row0);
  /* row[0..3] += A[i][3] * B[3][0..3] */
  row0 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (0 << 2) + 3), B3, row0);

  auto row1 =
    simde_mm256_mul_pd(simde_mm256_broadcast_sd(A + (1 << 2) + 0), B0);
  row1 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (1 << 2) + 1), B1, row1);
  row1 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (1 << 2) + 2), B2, row1);
  row1 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (1 << 2) + 3), B3, row1);

  auto row2 =
    simde_mm256_mul_pd(simde_mm256_broadcast_sd(A + (2 << 2) + 0), B0);
  row2 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (2 << 2) + 1), B1, row2);
  row2 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (2 << 2) + 2), B2, row2);
  row2 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (2 << 2) + 3), B3, row2);

  auto row3 =
    simde_mm256_mul_pd(simde_mm256_broadcast_sd(A + (3 << 2) + 0), B0);
  row3 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (3 << 2) + 1), B1, row3);
  row3 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (3 << 2) + 2), B2, row3);
  row3 =
    simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (3 << 2) + 3), B3, row3);

  result_type result;
  auto* M = result.data();
  simde_mm256_storeu_pd(M + (0 << 2), row0);
  simde_mm256_storeu_pd(M + (1 << 2), row1);
  simde_mm256_storeu_pd(M + (2 << 2), row2);
  simde_mm256_storeu_pd(M + (3 << 2), row3);

  return result;
}

/* AVX2 4x4 double col-major matrix product. */
template<class S, class Basis1, class Basis2>
auto
matrix_product(
  // clang-format off
  const matrix<double, compiled<4, 4, S>, Basis1, col_major>& sub1,
  const matrix<double, compiled<4, 4, S>, Basis2, col_major>& sub2
  // clang-format on
  ) -> matrix<double, compiled<4, 4, S>, basis_tag_promote_t<Basis1, Basis2>,
  col_major>
{
  using result_type = matrix<double, compiled<4, 4, S>,
    basis_tag_promote_t<Basis1, Basis2>, col_major>;

  const auto* A = sub1.data();
  const auto* B = sub2.data();

  /* Cache sub1: */
  const auto A0 = simde_mm256_loadu_pd(A + (0 << 2));
  const auto A1 = simde_mm256_loadu_pd(A + (1 << 2));
  const auto A2 = simde_mm256_loadu_pd(A + (2 << 2));
  const auto A3 = simde_mm256_loadu_pd(A + (3 << 2));

  /* col[0..3] = A[0..3][j] * B[j][0] */
  auto col0 =
    simde_mm256_mul_pd(A0, simde_mm256_broadcast_sd(B + (0 << 2) + 0));
  /* col[0..3] += A[0..3][j] * B[j][1] */
  col0 =
    simde_mm256_fmadd_pd(A1, simde_mm256_broadcast_sd(B + (0 << 2) + 1), col0);
  /* col[0..3] += A[0..3][j] * B[j][2] */
  col0 =
    simde_mm256_fmadd_pd(A2, simde_mm256_broadcast_sd(B + (0 << 2) + 2), col0);
  /* col[0..3] += A[0..3][j] * B[j][3] */
  col0 =
    simde_mm256_fmadd_pd(A3, simde_mm256_broadcast_sd(B + (0 << 2) + 3), col0);

  auto col1 =
    simde_mm256_mul_pd(A0, simde_mm256_broadcast_sd(B + (1 << 2) + 0));
  col1 =
    simde_mm256_fmadd_pd(A1, simde_mm256_broadcast_sd(B + (1 << 2) + 1), col1);
  col1 =
    simde_mm256_fmadd_pd(A2, simde_mm256_broadcast_sd(B + (1 << 2) + 2), col1);
  col1 =
    simde_mm256_fmadd_pd(A3, simde_mm256_broadcast_sd(B + (1 << 2) + 3), col1);

  auto col2 =
    simde_mm256_mul_pd(A0, simde_mm256_broadcast_sd(B + (2 << 2) + 0));
  col2 =
    simde_mm256_fmadd_pd(A1, simde_mm256_broadcast_sd(B + (2 << 2) + 1), col2);
  col2 =
    simde_mm256_fmadd_pd(A2, simde_mm256_broadcast_sd(B + (2 << 2) + 2), col2);
  col2 =
    simde_mm256_fmadd_pd(A3, simde_mm256_broadcast_sd(B + (2 << 2) + 3), col2);

  auto col3 =
    simde_mm256_mul_pd(A0, simde_mm256_broadcast_sd(B + (3 << 2) + 0));
  col3 =
    simde_mm256_fmadd_pd(A1, simde_mm256_broadcast_sd(B + (3 << 2) + 1), col3);
  col3 =
    simde_mm256_fmadd_pd(A2, simde_mm256_broadcast_sd(B + (3 << 2) + 2), col3);
  col3 =
    simde_mm256_fmadd_pd(A3, simde_mm256_broadcast_sd(B + (3 << 2) + 3), col3);

  result_type result;
  auto* M = result.data();
  simde_mm256_storeu_pd(M + (0 << 2), col0);
  simde_mm256_storeu_pd(M + (1 << 2), col1);
  simde_mm256_storeu_pd(M + (2 << 2), col2);
  simde_mm256_storeu_pd(M + (3 << 2), col3);
  return result;
}

}  // namespace cml::detail
#endif

namespace cml {

template<class Sub1, class Sub2, typename, typename>
auto
operator*(Sub1&& sub1, Sub2&& sub2) -> matrix_inner_product_promote_t<
  actual_type_of_t<Sub1>, actual_type_of_t<Sub2>>
{
  return detail::matrix_product(std::forward<Sub1>(sub1),
    std::forward<Sub2>(sub2));
}

}  // namespace cml
