/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/detail/resize.h>

#ifndef CML_DISABLE_SIMD
#include <cml/matrix/detail/simd_primitives.h>
#endif

namespace cml::detail {

template<class Result, class Sub1, class Sub2>
auto
matrix_product_NN(Result& R, const Sub1& sub1, const Sub2& sub2)
{
  // TODO Implement version for col-major loop ordering.
  detail::check_or_resize(R, array_rows_of(sub1), array_cols_of(sub2));
  for(int i = 0; i < R.rows(); ++i) {
    for(int j = 0; j < R.cols(); ++j) {
      auto m = sub1(i, 0) * sub2(0, j);
      for(int k = 1; k < sub1.cols(); ++k) m += sub1(i, k) * sub2(k, j);
      R(i, j) = m;
    }
  }
}

/* Default matrix product. */
template<class Result, class Sub1, class Sub2>
auto
matrix_product(Result& R, const Sub1& sub1, const Sub2& sub2)
{
  matrix_product_NN(R, sub1, sub2);
}

}  // namespace cml::detail

#ifndef CML_DISABLE_SIMD
namespace cml::detail {

/* AVX2 3x3 float row-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_33(float* R, const float* const A, const float* const B,
  row_major)
{
  /* Cache rows of B: */
  const auto B0 = simde_mm_set_ps(0., B[0 * 3 + 2], B[0 * 3 + 1], B[0 * 3 + 0]);
  const auto B1 = simde_mm_set_ps(0., B[1 * 3 + 2], B[1 * 3 + 1], B[1 * 3 + 0]);
  const auto B2 = simde_mm_set_ps(0., B[2 * 3 + 2], B[2 * 3 + 1], B[2 * 3 + 0]);

  /* R[i][0..2] = A[i][0] * B[i][0..2] + ... + A[i][2] * B[i][0..2] */
  const auto row0 = vxm_13_rr(A + 0 * 3, B0, B1, B2);
  const auto row1 = vxm_13_rr(A + 1 * 3, B0, B1, B2);
  const auto row2 = vxm_13_rr(A + 2 * 3, B0, B1, B2);

  /* Store only the low 3 elements of each row: */
  const auto mask = simde_mm_set_epi32(0, -1, -1, -1);
  simde_mm_maskstore_ps(R + 0 * 3 + 0, mask, row0);
  simde_mm_maskstore_ps(R + 1 * 3 + 0, mask, row1);
  simde_mm_maskstore_ps(R + 2 * 3 + 0, mask, row2);
}

/* AVX2 3x3 float col-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_33(float* R, const float* const A, const float* const B,
  col_major)
{
  /* Cache columns of A: */
  const auto A0 = simde_mm_set_ps(0., A[0 * 3 + 2], A[0 * 3 + 1], A[0 * 3 + 0]);
  const auto A1 = simde_mm_set_ps(0., A[1 * 3 + 2], A[1 * 3 + 1], A[1 * 3 + 0]);
  const auto A2 = simde_mm_set_ps(0., A[2 * 3 + 2], A[2 * 3 + 1], A[2 * 3 + 0]);

  /* col[0..2][j] = B[0][j]*A[0..2][j] + ... + B[2][j]*A[0..2][j] */
  const auto col0 = vxm_13_rr(B + 0 * 3, A0, A1, A2);
  const auto col1 = vxm_13_rr(B + 1 * 3, A0, A1, A2);
  const auto col2 = vxm_13_rr(B + 2 * 3, A0, A1, A2);

  /* Store only the low 3 elements of each col: */
  const auto mask = simde_mm_set_epi32(0, -1, -1, -1);
  simde_mm_maskstore_ps(R + 0 * 3 + 0, mask, col0);
  simde_mm_maskstore_ps(R + 1 * 3 + 0, mask, col1);
  simde_mm_maskstore_ps(R + 2 * 3 + 0, mask, col2);
}

/* AVX2 4x4 float row-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_44(float* R, const float* const A, const float* const B,
  row_major)
{
  /* Cache rows of B: */
  const auto B0 = simde_mm_loadu_ps(B + (0 << 2));
  const auto B1 = simde_mm_loadu_ps(B + (1 << 2));
  const auto B2 = simde_mm_loadu_ps(B + (2 << 2));
  const auto B3 = simde_mm_loadu_ps(B + (3 << 2));

  /* R[i][0..3] = A[i][0] * B[i][0..3] + ... + A[i][3] * B[i][0..3] */
  const auto row0 = vxm_14_rr(A + (0 << 2), B0, B1, B2, B3);
  const auto row1 = vxm_14_rr(A + (1 << 2), B0, B1, B2, B3);
  const auto row2 = vxm_14_rr(A + (2 << 2), B0, B1, B2, B3);
  const auto row3 = vxm_14_rr(A + (3 << 2), B0, B1, B2, B3);

  simde_mm_storeu_ps(R + (0 << 2), row0);
  simde_mm_storeu_ps(R + (1 << 2), row1);
  simde_mm_storeu_ps(R + (2 << 2), row2);
  simde_mm_storeu_ps(R + (3 << 2), row3);
}

/* AVX2 4x4 float col-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_44(float* R, const float* const A, const float* const B,
  col_major)
{
  /* Cache columns of A: */
  const auto A0 = simde_mm_loadu_ps(A + (0 << 2));
  const auto A1 = simde_mm_loadu_ps(A + (1 << 2));
  const auto A2 = simde_mm_loadu_ps(A + (2 << 2));
  const auto A3 = simde_mm_loadu_ps(A + (3 << 2));

  /* col[0..3][j] = B[0][j]*A[0..3][j] + ... + B[3][j]*A[0..3][j] */
  const auto col0 = vxm_14_rr(B + (0 << 2), A0, A1, A2, A3);
  const auto col1 = vxm_14_rr(B + (1 << 2), A0, A1, A2, A3);
  const auto col2 = vxm_14_rr(B + (2 << 2), A0, A1, A2, A3);
  const auto col3 = vxm_14_rr(B + (3 << 2), A0, A1, A2, A3);

  simde_mm_storeu_ps(R + (0 << 2), col0);
  simde_mm_storeu_ps(R + (1 << 2), col1);
  simde_mm_storeu_ps(R + (2 << 2), col2);
  simde_mm_storeu_ps(R + (3 << 2), col3);
}

/* AVX2 3x3 double row-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_33(double* R, const double* const A, const double* const B,
  row_major)
{
  /* Cache rows of B: */
  const auto B0 =
    simde_mm256_set_pd(0., B[0 * 3 + 2], B[0 * 3 + 1], B[0 * 3 + 0]);
  const auto B1 =
    simde_mm256_set_pd(0., B[1 * 3 + 2], B[1 * 3 + 1], B[1 * 3 + 0]);
  const auto B2 =
    simde_mm256_set_pd(0., B[2 * 3 + 2], B[2 * 3 + 1], B[2 * 3 + 0]);

  /* R[i][0..2] = A[i][0] * B[i][0..2] + ... + A[i][2] * B[i][0..2] */
  const auto row0 = vxm_13_rr(A + 0 * 3, B0, B1, B2);
  const auto row1 = vxm_13_rr(A + 1 * 3, B0, B1, B2);
  const auto row2 = vxm_13_rr(A + 2 * 3, B0, B1, B2);

  /* Store only the low 3 elements of each row: */
  const auto mask = simde_mm256_set_epi64x(0, -1, -1, -1);
  simde_mm256_maskstore_pd(R + 0 * 3 + 0, mask, row0);
  simde_mm256_maskstore_pd(R + 1 * 3 + 0, mask, row1);
  simde_mm256_maskstore_pd(R + 2 * 3 + 0, mask, row2);
}

/* AVX2 3x3 double col-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_33(double* R, const double* const A, const double* const B,
  col_major)
{
  /* Cache columns of A: */
  const auto A0 =
    simde_mm256_set_pd(0., A[0 * 3 + 2], A[0 * 3 + 1], A[0 * 3 + 0]);
  const auto A1 =
    simde_mm256_set_pd(0., A[1 * 3 + 2], A[1 * 3 + 1], A[1 * 3 + 0]);
  const auto A2 =
    simde_mm256_set_pd(0., A[2 * 3 + 2], A[2 * 3 + 1], A[2 * 3 + 0]);

  /* col[0..2][j] = B[0][j]*A[0..2][j] + ... + B[2][j]*A[0..2][j] */
  const auto col0 = vxm_13_rr(B + 0 * 3, A0, A1, A2);
  const auto col1 = vxm_13_rr(B + 1 * 3, A0, A1, A2);
  const auto col2 = vxm_13_rr(B + 2 * 3, A0, A1, A2);

  /* Store only the low 3 elements of each col: */
  const auto mask = simde_mm256_set_epi64x(0, -1, -1, -1);
  simde_mm256_maskstore_pd(R + 0 * 3 + 0, mask, col0);
  simde_mm256_maskstore_pd(R + 1 * 3 + 0, mask, col1);
  simde_mm256_maskstore_pd(R + 2 * 3 + 0, mask, col2);
}

/* AVX2 4x4 double row-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_44(double* R, const double* const A, const double* const B,
  row_major)
{
  /* Cache rows of B: */
  const auto B0 = simde_mm256_loadu_pd(B + (0 << 2));
  const auto B1 = simde_mm256_loadu_pd(B + (1 << 2));
  const auto B2 = simde_mm256_loadu_pd(B + (2 << 2));
  const auto B3 = simde_mm256_loadu_pd(B + (3 << 2));

  /* R[i][0..3] = A[i][0] * B[i][0..3] + ... + A[i][3] * B[i][0..3] */
  const auto row0 = vxm_14_rr(A + (0 << 2), B0, B1, B2, B3);
  const auto row1 = vxm_14_rr(A + (1 << 2), B0, B1, B2, B3);
  const auto row2 = vxm_14_rr(A + (2 << 2), B0, B1, B2, B3);
  const auto row3 = vxm_14_rr(A + (3 << 2), B0, B1, B2, B3);

  simde_mm256_storeu_pd(R + (0 << 2), row0);
  simde_mm256_storeu_pd(R + (1 << 2), row1);
  simde_mm256_storeu_pd(R + (2 << 2), row2);
  simde_mm256_storeu_pd(R + (3 << 2), row3);
}

/* AVX2 4x4 double col-major matrix product. */
static HEDLEY_ALWAYS_INLINE auto
matrix_product_44(double* R, const double* const A, const double* const B,
  col_major)
{
  /* Cache columns of A: */
  const auto A0 = simde_mm256_loadu_pd(A + (0 << 2));
  const auto A1 = simde_mm256_loadu_pd(A + (1 << 2));
  const auto A2 = simde_mm256_loadu_pd(A + (2 << 2));
  const auto A3 = simde_mm256_loadu_pd(A + (3 << 2));

  /* col[0..3][j] = B[0][j]*A[0..3][j] + ... + B[3][j]*A[0..3][j] */
  const auto col0 = vxm_14_rr(B + (0 << 2), A0, A1, A2, A3);
  const auto col1 = vxm_14_rr(B + (1 << 2), A0, A1, A2, A3);
  const auto col2 = vxm_14_rr(B + (2 << 2), A0, A1, A2, A3);
  const auto col3 = vxm_14_rr(B + (3 << 2), A0, A1, A2, A3);

  simde_mm256_storeu_pd(R + (0 << 2), col0);
  simde_mm256_storeu_pd(R + (1 << 2), col1);
  simde_mm256_storeu_pd(R + (2 << 2), col2);
  simde_mm256_storeu_pd(R + (3 << 2), col3);
}

template<typename Scalar, class StorageR, class BasisR, class Storage1,
  class Basis1, class Storage2, class Basis2, class Layout>
static HEDLEY_ALWAYS_INLINE auto
matrix_product(matrix<Scalar, StorageR, BasisR, Layout>& R,
  const matrix<Scalar, Storage1, Basis1, Layout>& sub1,
  const matrix<Scalar, Storage2, Basis2, Layout>& sub2)
{
  using left_type = cml::unqualified_type_t<decltype(sub1)>;
  using right_type = cml::unqualified_type_t<decltype(sub2)>;
  using result_type = cml::unqualified_type_t<decltype(R)>;
  using result_traits = matrix_traits<result_type>;

  /* If R is statically sized, then sub1 and sub2 are statically sized: */
  if constexpr(is_fixed_size_v<result_traits>) {
    constexpr auto rows =
      array_rows_of_v<left_type> == array_rows_of_v<right_type>
      ? array_rows_of_v<left_type>
      : -1;
    constexpr auto cols =
      array_cols_of_v<left_type> == array_cols_of_v<right_type>
      ? array_cols_of_v<left_type>
      : -1;

    if constexpr(rows == 3 && cols == 3) {
      cml::check_size(R, rows, cols);
      matrix_product_33(R.data(), sub1.data(), sub2.data(), Layout());
    }

    else if constexpr(rows == 4 && cols == 4) {
      cml::check_size(R, rows, cols);
      matrix_product_44(R.data(), sub1.data(), sub2.data(), Layout());
    }

    else
      matrix_product_NN(R, sub1, sub2);
  }

  /* Otherwise, at least one is dynamically sized: */
  else {
    const auto rows =
      array_rows_of(sub1) == array_rows_of(sub2) ? array_rows_of(sub1) : -1;
    const auto cols =
      array_cols_of(sub1) == array_cols_of(sub2) ? array_cols_of(sub1) : -1;

    if(rows == 4 && cols == 4) {
      detail::check_or_resize(R, rows, cols);
      matrix_product_44(R.data(), sub1.data(), sub2.data(), Layout());
    }

    else if(rows == 3 && cols == 3) {
      detail::check_or_resize(R, rows, cols);
      matrix_product_33(R.data(), sub1.data(), sub2.data(), Layout());
    }

    else
      matrix_product_NN(R, sub1, sub2);
  }
}

}  // namespace cml::detail
#endif

namespace cml {

template<class Sub1, class Sub2, typename, typename>
auto
operator*(Sub1&& sub1, Sub2&& sub2) -> matrix_inner_product_promote_t<
  actual_type_of_t<Sub1>, actual_type_of_t<Sub2>>
{
  using result_type = matrix_inner_product_promote_t<actual_type_of_t<Sub1>,
    actual_type_of_t<Sub2>>;
  cml::check_same_inner_size(std::forward<Sub1>(sub1),
    std::forward<Sub2>(sub2));
  result_type R;
  detail::matrix_product(R, std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
  return R;
  // TODO Is there any way to avoid vextractf128 -> R for msvc? (clang fully inlines s_access)
}

}  // namespace cml
