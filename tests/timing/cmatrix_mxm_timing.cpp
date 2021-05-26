/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <cstdio>

/* Need the matrix type and CML type system specializations: */
#include CML_TIMING_MxM_INL

#include "timing.h"
#include "make_rotation_matrix_pairs.h"

int main(int /*argc*/, char** /*argv*/)
{
  const int N = 1;
  //const int N = 1000000;

  /* Pre-generate N repeatable pairs of random 4x4 rotations: */
  const auto prep_time_start = cml::testing::usec_time();
  const auto rotations = cml::testing::make_rotation_matrix_pairs<matrix44d>(N);
  const auto prep_time_end = cml::testing::usec_time();
  const auto prep_time = prep_time_end - prep_time_start;
  std::printf("prep time (%d pairs): %.5lf s\n", N, static_cast<double>(prep_time)/1e6);

  /* Time N multiplications: */
  using data_t = struct { matrix44d M; };
  std::vector<data_t> out(N);
  const auto mxm_time_start = cml::testing::usec_time();
  for(int i = 0; i < N; ++ i) {
    mxm_4x4(out[i].M, rotations[i].first, rotations[i].second);
  }
  const auto mxm_time_end = cml::testing::usec_time();
  const auto mxm_time = mxm_time_end - mxm_time_start;
  std::printf("mxm time (%d pairs): %.5lf s\n", N, static_cast<double>(mxm_time)/1e6);

  return 0;
}