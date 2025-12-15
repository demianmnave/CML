/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/detail/resize.h>
#include <cml/matrix/size_checking.h>

#ifndef CML_DISABLE_SIMD
#include <cml/matrix/detail/simd_primitives.h>
#endif

namespace cml::detail {

template<class Result, class Sub1, class Sub2>
auto
vector_product_N1(Result& x, const Sub1& sub1, const Sub2& sub2)
{
  detail::check_or_resize(x, array_rows_of(sub1));
  for(int i = 0; i < sub1.rows(); ++i) {
    auto m = sub1(i, 0) * sub2[0];
    for(int k = 1; k < sub2.size(); ++k) m += sub1(i, k) * sub2[k];
    x[i] = m;
  }
}

template<class Result, class Sub1, class Sub2>
auto
vector_product_1N(Result& x, const Sub1& sub1, const Sub2& sub2)
{
  detail::check_or_resize(x, array_cols_of(sub2));
  for(int j = 0; j < sub2.cols(); ++j) {
    auto m = sub1[0] * sub2(0, j);
    for(int k = 1; k < sub1.size(); ++k) m += sub1[k] * sub2(k, j);
    x[j] = m;
  }
}

#ifndef CML_DISABLE_SIMD
/* AVX2 1x4 float row-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_14(float* x, const float* const v, const float* const M,
  row_major)
{
  /* Cache rows of M: */
  const auto M0 = simde_mm_loadu_ps(M + (0 << 2));
  const auto M1 = simde_mm_loadu_ps(M + (1 << 2));
  const auto M2 = simde_mm_loadu_ps(M + (2 << 2));
  const auto M3 = simde_mm_loadu_ps(M + (3 << 2));
  simde_mm_storeu_ps(x, vxm_14_rr(v, M0, M1, M2, M3));
}

/* AVX2 1x4 float col-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_14(float* x, const float* const v, const float* const M,
  col_major)
{
  /* Cache columns of M: */
  const auto M0 = simde_mm_loadu_ps(M + (0 << 2));
  const auto M1 = simde_mm_loadu_ps(M + (1 << 2));
  const auto M2 = simde_mm_loadu_ps(M + (2 << 2));
  const auto M3 = simde_mm_loadu_ps(M + (3 << 2));
  simde_mm_storeu_ps(x, vxm_14_rc(v, M0, M1, M2, M3));
}

/* AVX2 1x4 double row-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_14(double* x, const double* const v, const double* const M,
  row_major)
{
  /* Cache rows of M: */
  const auto M0 = simde_mm256_loadu_pd(M + (0 << 2));
  const auto M1 = simde_mm256_loadu_pd(M + (1 << 2));
  const auto M2 = simde_mm256_loadu_pd(M + (2 << 2));
  const auto M3 = simde_mm256_loadu_pd(M + (3 << 2));

  /* x[0..3] = v[0] * M[0][0..3] + ... + v[3] * M[3][0..3] */
  simde_mm256_storeu_pd(x, vxm_14_rr(v, M0, M1, M2, M3));
}

/* AVX2 1x4 double col-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_14(double* x, const double* const v, const double* const M,
  col_major)
{
  /* Cache columns of M: */
  const auto M0 = simde_mm256_loadu_pd(M + (0 << 2));
  const auto M1 = simde_mm256_loadu_pd(M + (1 << 2));
  const auto M2 = simde_mm256_loadu_pd(M + (2 << 2));
  const auto M3 = simde_mm256_loadu_pd(M + (3 << 2));

  simde_mm256_storeu_pd(x, vxm_14_rc(v, M0, M1, M2, M3));
}

/* AVX2 4x1 float row-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_41(float* x, const float* const M, const float* const v,
  row_major)
{
  /* Cache rows of M: */
  const auto M0 = simde_mm_loadu_ps(M + (0 << 2));
  const auto M1 = simde_mm_loadu_ps(M + (1 << 2));
  const auto M2 = simde_mm_loadu_ps(M + (2 << 2));
  const auto M3 = simde_mm_loadu_ps(M + (3 << 2));

  /* x = M*v = v^T*M^T: */
  simde_mm_storeu_ps(x, vxm_14_rc(v, M0, M1, M2, M3));
}

/* AVX2 41x1 float col-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_41(float* x, const float* const v, const float* const M,
  col_major)
{
  /* Cache columns of M: */
  const auto M0 = simde_mm_loadu_ps(M + (0 << 2));
  const auto M1 = simde_mm_loadu_ps(M + (1 << 2));
  const auto M2 = simde_mm_loadu_ps(M + (2 << 2));
  const auto M3 = simde_mm_loadu_ps(M + (3 << 2));

  /* x = M*v = v^T*M^T: */
  simde_mm_storeu_ps(x, vxm_14_rr(v, M0, M1, M2, M3));
}

/* AVX2 4x1 double row-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_41(double* x, const double* const M, const double* const v,
  row_major)
{
  /* Cache rows of M: */
  const auto M0 = simde_mm256_loadu_pd(M + (0 << 2));
  const auto M1 = simde_mm256_loadu_pd(M + (1 << 2));
  const auto M2 = simde_mm256_loadu_pd(M + (2 << 2));
  const auto M3 = simde_mm256_loadu_pd(M + (3 << 2));

  /* x = M*v = v^T*M^T: */
  simde_mm256_storeu_pd(x, vxm_14_rc(v, M0, M1, M2, M3));
}

/* AVX2 4x1 double col-major vector-matrix product. */
static HEDLEY_ALWAYS_INLINE auto
vector_product_41(double* x, const double* const M, const double* const v,
  col_major)
{
  /* Cache columns of M: */
  const auto M0 = simde_mm256_loadu_pd(M + (0 << 2));
  const auto M1 = simde_mm256_loadu_pd(M + (1 << 2));
  const auto M2 = simde_mm256_loadu_pd(M + (2 << 2));
  const auto M3 = simde_mm256_loadu_pd(M + (3 << 2));

  /* x = M*v = v^T*M^T: */
  simde_mm256_storeu_pd(x, vxm_14_rr(v, M0, M1, M2, M3));
}

template<typename Scalar, class StorageR, class StorageV, class StorageM,
  class BasisM, class LayoutM>
static HEDLEY_ALWAYS_INLINE auto
vector_product(vector<Scalar, StorageR>& x,
  const matrix<Scalar, StorageM, BasisM, LayoutM>& M,
  const vector<Scalar, StorageV>& v)
{
  using M_type = cml::unqualified_type_t<decltype(M)>;
  using v_type = cml::unqualified_type_t<decltype(v)>;
  using result_type = cml::unqualified_type_t<decltype(x)>;
  using result_traits = vector_traits<result_type>;

  /* If R is statically sized, then sub1 and sub2 are statically sized: */
  if constexpr(is_fixed_size_v<result_traits>) {
    constexpr auto rows = array_size_of_v<v_type> == array_rows_of_v<M_type>
      ? array_rows_of_v<M_type>
      : -1;

    if constexpr(rows == 4) {
      detail::check_size(x, rows);
      vector_product_41(x.data(), M.data(), v.data(), LayoutM());
    }

    else
      vector_product_N1(x, M, v);
  }

  /* Otherwise, at least one is dynamically sized: */
  else {
    const auto rows = array_rows_of(M);
    if(rows == 4) {
      detail::check_or_resize(x, rows);
      vector_product_41(x.data(), M.data(), v.data(), LayoutM());
    }

    else
      vector_product_N1(x, M, v);
  }
}

template<typename Scalar, class StorageR, class StorageV, class StorageM,
  class BasisM, class LayoutM>
static HEDLEY_ALWAYS_INLINE auto
vector_product(vector<Scalar, StorageR>& x, const vector<Scalar, StorageV>& v,
  const matrix<Scalar, StorageM, BasisM, LayoutM>& M)
{
  using v_type = cml::unqualified_type_t<decltype(v)>;
  using M_type = cml::unqualified_type_t<decltype(M)>;
  using result_type = cml::unqualified_type_t<decltype(x)>;
  using result_traits = vector_traits<result_type>;

  /* If R is statically sized, then sub1 and sub2 are statically sized: */
  if constexpr(is_fixed_size_v<result_traits>) {
    constexpr auto cols = array_size_of_v<v_type> == array_cols_of_v<M_type>
      ? array_cols_of_v<M_type>
      : -1;

    if constexpr(cols == 4) {
      detail::check_size(x, cols);
      vector_product_14(x.data(), v.data(), M.data(), LayoutM());
    }

    else
      vector_product_1N(x, v, M);
  }

  /* Otherwise, at least one is dynamically sized: */
  else {
    const auto cols = array_cols_of(M);
    if(cols == 4) {
      detail::check_or_resize(x, cols);
      vector_product_41(x.data(), v.data(), M.data(), LayoutM());
    }

    else
      vector_product_1N(x, v, M);
  }
}
#endif

template<class Result, class Sub1, class Sub2>
auto
vector_product(Result& v, const Sub1& sub1, const Sub2& sub2)
{
  using left_type = cml::unqualified_type_t<decltype(sub1)>;
  using right_type = cml::unqualified_type_t<decltype(sub2)>;

  if constexpr(is_vector_v<left_type> && is_matrix_v<right_type>) {
    vector_product_1N(v, sub1, sub2);
  }

  if constexpr(is_matrix_v<left_type> && is_vector_v<right_type>) {
    vector_product_N1(v, sub1, sub2);
  }
}

}  // namespace cml::detail

namespace cml {
template<class Sub1, class Sub2, enable_if_matrix_t<Sub1>*,
  enable_if_vector_t<Sub2>*>
auto
operator*(Sub1&& sub1, Sub2&& sub2)
  -> matrix_inner_product_promote_t<actual_operand_type_of_t<decltype(sub1)>,
    actual_operand_type_of_t<decltype(sub2)>>
{
  using result_type =
    matrix_inner_product_promote_t<actual_operand_type_of_t<decltype(sub1)>,
      actual_operand_type_of_t<decltype(sub2)>>;
  cml::check_same_inner_size(std::forward<Sub1>(sub1),
    std::forward<Sub2>(sub2));

  result_type v;
  detail::vector_product(v, std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
  return v;
}

template<class Sub1, class Sub2, enable_if_vector_t<Sub1>*,
  enable_if_matrix_t<Sub2>*>
auto
operator*(Sub1&& sub1, Sub2&& sub2)
  -> matrix_inner_product_promote_t<actual_operand_type_of_t<decltype(sub1)>,
    actual_operand_type_of_t<decltype(sub2)>>
{
  using result_type =
    matrix_inner_product_promote_t<actual_operand_type_of_t<decltype(sub1)>,
      actual_operand_type_of_t<decltype(sub2)>>;
  cml::check_same_inner_size(std::forward<Sub1>(sub1),
    std::forward<Sub2>(sub2));

  result_type v;
  detail::vector_product(v, std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
  return v;
}

}  // namespace cml
