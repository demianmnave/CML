/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <cstdio>
#include <vector>
#include <cml/matrix.h>
#include "cmatrix_mxm.h"
#include "timing.h"
#include "uniform_random_rotation.h"

using matrix_pair_t = std::pair<matrix44d, matrix44d>;

int main(int /*argc*/, char** /*argv*/)
{
  const int N = 1;
  //const int N = 1000000;

  /* Pre-generate N repeatable pairs of random 4x4 rotations: */
  const auto prep_time_start = cml::testing::usec_time();
  std::mt19937 rng(0xdeadbeef);
  std::uniform_real_distribution<> d(0., std::nextafter(0., 1.));
  std::vector<matrix_pair_t> rotations(N);
  for(int i = 0; i < N; ++ i) {
    cml::testing::uniform_random_rotation_4(rng, d, rotations[i].first);
    cml::testing::uniform_random_rotation_4(rng, d, rotations[i].second);
  }
  const auto prep_time_end = cml::testing::usec_time();
  const auto prep_time = prep_time_end - prep_time_start;
  std::printf("prep time (%d pairs): %.5lf s\n", N, static_cast<double>(prep_time)/1e6);

  /* Time N multiplications: */
  matrix44d out;
  const auto mxm_time_start = cml::testing::usec_time();
  for(int i = 0; i < N; ++ i) {

    mxm_4x4(out, rotations[i].first, rotations[i].second);

  }
  const auto mxm_time_end = cml::testing::usec_time();
  const auto mxm_time = mxm_time_end - mxm_time_start;
  std::printf("mxm time (%d pairs): %.5lf s\n", N, static_cast<double>(mxm_time)/1e6);

  return 0;
}