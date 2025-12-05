/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
#  error "make_rotation_matrix_pairs.tpp not included correctly"
#endif

#include "uniform_random_rotation.h"

namespace cml::testing {

template<class Matrix44dT>
std::vector<std::tuple<Matrix44dT, Matrix44dT, cml::matrix44d>>
make_rotation_matrix_pairs(int N)
{
  std::vector<std::tuple<Matrix44dT, Matrix44dT, cml::matrix44d>> rotations(N);
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<> d(0., std::nextafter(1., 2.));
  for(int i = 0; i < N; ++i) {
    auto& m1 = std::get<0>(rotations[i]);
    auto& m2 = std::get<1>(rotations[i]);
    cml::testing::uniform_random_rotation_4(rng, d, m1);
    cml::testing::uniform_random_rotation_4(rng, d, m2);

    auto& m3 = std::get<2>(rotations[i]);
    for(int row = 0; row < 4; ++row) {
      for(int col = 0; col < 4; ++col) {
        auto sum = 0.;
        for(int k = 0; k < 4; ++k)
          sum += cml::detail::get(m1, row, k) * cml::detail::get(m2, k, col);
        m3(row, col) = sum;
      }
    }
  }
  return rotations;
}

}  // namespace cml::testing
