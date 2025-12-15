/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/vector/detail/get.h>
#include "uniform_random_rotation.h"

namespace cml::testing {

template<class Matrix44dT, class Vector4dT>
auto
make_matrix_vector_pairs(int N, cml::int_c<4>)
  -> std::vector<std::tuple<Matrix44dT, Vector4dT, cml::vector4d>>
{
  using layout = cml::layout_tag_trait_of_t<Matrix44dT>;
#ifdef CML_TIMING_ROW_MAJOR
  static_assert(std::is_same_v<layout, cml::row_major>);
#endif
#ifdef CML_TIMING_COL_MAJOR
  static_assert(std::is_same_v<layout, cml::col_major>);
#endif

  constexpr auto K = 4;
  std::vector<std::tuple<Matrix44dT, Vector4dT, cml::vector4d>> rotations(N);
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<> d(0., std::nextafter(1., 2.));
  for(int i = 0; i < N; ++i) {
    auto& M = std::get<0>(rotations[i]);
    cml::testing::uniform_random_rotation_4(rng, d, M);

    auto& v = std::get<1>(rotations[i]);
    for(int j = 0; j < K; ++j) {
      cml::detail::get(v, j) = cml::random_real<double>(-1., 1.);
    }

    auto& x = std::get<2>(rotations[i]);
    for(int row = 0; row < K; ++row) {
      auto sum = 0.;
      for(int col = 0; col < K; ++col) {
        sum += cml::detail::get(M, row, col) * cml::detail::get(v, col);
      }
      x[row] = sum;
    }
  }
  return rotations;
}

}  // namespace cml::testing
