/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/detail/resize.h>
#include <cml/matrix/size_checking.h>

namespace cml::detail {

template<class Result, class Sub1, class Sub2>
auto
vector_product_Nx1(Result& v, const Sub1& sub1, const Sub2& sub2)
{
  detail::check_or_resize(v, array_rows_of(sub1));
  for(int i = 0; i < sub1.rows(); ++i) {
    auto m = sub1(i, 0) * sub2[0];
    for(int k = 1; k < sub2.size(); ++k) m += sub1(i, k) * sub2[k];
    v[i] = m;
  }
}

template<class Result, class Sub1, class Sub2>
auto
vector_product_1xN(Result& v, const Sub1& sub1, const Sub2& sub2)
{
  detail::check_or_resize(v, array_cols_of(sub2));
  for(int j = 0; j < sub2.cols(); ++j) {
    auto m = sub1[0] * sub2(0, j);
    for(int k = 1; k < sub1.size(); ++k) m += sub1[k] * sub2(k, j);
    v[j] = m;
  }
}

/* Default 1xN vector product. */
template<class Result, class Sub1, class Sub2>
auto
vector_product(Result& v, const Sub1& sub1, const Sub2& sub2)
{
  using left_type = cml::unqualified_type_t<decltype(sub1)>;
  using right_type = cml::unqualified_type_t<decltype(sub2)>;

  if constexpr(is_vector_v<left_type> && is_matrix_v<right_type>) {
    vector_product_1xN(v, sub1, sub2);
  }

  if constexpr(is_matrix_v<left_type> && is_vector_v<right_type>) {
    vector_product_Nx1(v, sub1, sub2);
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
