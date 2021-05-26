/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
#error "make_rotation_matrix_pairs.tpp not included correctly"
#endif

#include "uniform_random_rotation.h"

namespace cml {
namespace testing {

template<class Matrix44T>
std::vector<std::pair<Matrix44T, Matrix44T>>
make_rotation_matrix_pairs(int N)
{
  std::mt19937 rng(0xdeadbeef);
  std::uniform_real_distribution<> d(0., std::nextafter(0., 1.));
  std::vector<std::pair<Matrix44T, Matrix44T>> rotations(N);
  for(int i = 0; i < N; ++ i) {
    cml::testing::uniform_random_rotation_4(rng, d, rotations[i].first);
    cml::testing::uniform_random_rotation_4(rng, d, rotations[i].second);
  }
  return rotations;
}

}} // cml::testing
