/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef __CML_MATRIX_MATRIX_PRODUCT_TPP
#error "matrix/matrix_product.tpp not included correctly"
#endif

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
  const simde__m128 B0 = simde_mm_loadu_ps(B + (0 << 2));
  const simde__m128 B1 = simde_mm_loadu_ps(B + (1 << 2));
  const simde__m128 B2 = simde_mm_loadu_ps(B + (2 << 2));
  const simde__m128 B3 = simde_mm_loadu_ps(B + (3 << 2));

  simde__m128 row[4];
  for(uint32_t i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    row[i] = simde_mm_mul_ps(simde_mm_broadcast_ss(A + (i << 2) + 0), B0);

    /* row[0..3] += A[i][1] * B[1][0..3] */
    row[i] =
      simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (i << 2) + 1), B1, row[i]);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    row[i] =
      simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (i << 2) + 2), B2, row[i]);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    row[i] =
      simde_mm_fmadd_ps(simde_mm_broadcast_ss(A + (i << 2) + 3), B3, row[i]);
  }

  /* result[i] = row[i] */
  result_type result;
  auto* M = result.data();
  for(uint32_t i = 0; i < 4; ++i) {
    simde_mm_storeu_ps(M + (i << 2), row[i]);
  }

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

  simde__m128 col[4];
  for(uint32_t j = 0; j < 4; ++j) {
    /* col[0..3] = A[0..3][j] * B[j][0] */
    col[j] = simde_mm_mul_ps(A0, simde_mm_broadcast_ss(B + (j << 2) + 0));

    /* col[0..3] += A[0..3][j] * B[j][1] */
    col[j] =
      simde_mm_fmadd_ps(A1, simde_mm_broadcast_ss(B + (j << 2) + 1), col[j]);

    /* col[0..3] += A[0..3][j] * B[j][2] */
    col[j] =
      simde_mm_fmadd_ps(A2, simde_mm_broadcast_ss(B + (j << 2) + 2), col[j]);

    /* col[0..3] += A[0..3][j] * B[j][3] */
    col[j] =
      simde_mm_fmadd_ps(A3, simde_mm_broadcast_ss(B + (j << 2) + 3), col[j]);
  }

  /* result[j] = col[j] */
  result_type result;
  auto* M = result.data();
  for(uint32_t j = 0; j < 4; ++j) {
    simde_mm_storeu_ps(M + (j << 2), col[j]);
  }

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
  const simde__m256d B0 = simde_mm256_loadu_pd(B + (0 << 2));
  const simde__m256d B1 = simde_mm256_loadu_pd(B + (1 << 2));
  const simde__m256d B2 = simde_mm256_loadu_pd(B + (2 << 2));
  const simde__m256d B3 = simde_mm256_loadu_pd(B + (3 << 2));

  simde__m256d row[4];
  for(uint32_t i = 0; i < 4; ++i) {
    /* row[0..3] = A[i][0] * B[0][0..3] */
    row[i] = simde_mm256_mul_pd(simde_mm256_broadcast_sd(A + (i << 2) + 0), B0);

    /* row[0..3] += A[i][1] * B[1][0..3] */
    row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (i << 2) + 1),
      B1, row[i]);

    /* row[0..3] += A[i][2] * B[2][0..3] */
    row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (i << 2) + 2),
      B2, row[i]);

    /* row[0..3] += A[i][3] * B[3][0..3] */
    row[i] = simde_mm256_fmadd_pd(simde_mm256_broadcast_sd(A + (i << 2) + 3),
      B3, row[i]);
  }

  /* result[i] = row[i] */
  result_type result;
  auto* M = result.data();
  for(uint32_t i = 0; i < 4; ++i) {
    simde_mm256_storeu_pd(M + (i << 2), row[i]);
  }

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
  const simde__m256d A0 = simde_mm256_loadu_pd(A + (0 << 2));
  const simde__m256d A1 = simde_mm256_loadu_pd(A + (1 << 2));
  const simde__m256d A2 = simde_mm256_loadu_pd(A + (2 << 2));
  const simde__m256d A3 = simde_mm256_loadu_pd(A + (3 << 2));

  simde__m256d col[4];
  for(uint32_t j = 0; j < 4; ++j) {
    /* col[0..3] = A[0..3][j] * B[j][0] */
    col[j] = simde_mm256_mul_pd(A0, simde_mm256_broadcast_sd(B + (j << 2) + 0));

    /* col[0..3] += A[0..3][j] * B[j][1] */
    col[j] = simde_mm256_fmadd_pd(A1,
      simde_mm256_broadcast_sd(B + (j << 2) + 1), col[j]);

    /* col[0..3] += A[0..3][j] * B[j][2] */
    col[j] = simde_mm256_fmadd_pd(A2,
      simde_mm256_broadcast_sd(B + (j << 2) + 2), col[j]);

    /* col[0..3] += A[0..3][j] * B[j][3] */
    col[j] = simde_mm256_fmadd_pd(A3,
      simde_mm256_broadcast_sd(B + (j << 2) + 3), col[j]);
  }

  /* result[j] = col[j] */
  result_type result;
  auto* M = result.data();
  for(uint32_t j = 0; j < 4; ++j) {
    simde_mm256_storeu_pd(M + (j << 2), col[j]);
  }
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
