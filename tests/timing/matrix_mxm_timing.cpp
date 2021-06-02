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

int main(int argc, const char** argv)
{
  long N = LONG_MAX;
  if(argc == 2) {
    char* a_end = nullptr;
    N = std::strtol(argv[1], &a_end, 10);
  } else {
    // N = 1;
    N = 10000000;
  }

  if(0 >= N || N == LONG_MAX) {
    std::cerr << argv[0] << ": invalid sample count " << argv[1] << std::endl;
    return 1;
  }

  /* Pre-generate N repeatable pairs of random 4x4 rotations: */
  const auto prep_time_start = cml::testing::usec_time();
  const auto rotations = cml::testing::make_rotation_matrix_pairs<matrix44d>(N);
  const auto prep_time_end = cml::testing::usec_time();
  const auto prep_time = prep_time_end - prep_time_start;
  std::printf("prep time (%d pairs): %.5lf s\n", N, static_cast<double>(prep_time) / 1e6);

  /* Time N multiplications: */
  using data_t = struct { matrix44d M; };
  std::vector<data_t> out(N);
  const auto mxm_time_start = cml::testing::usec_time();
  for(int i = 0; i < N; ++ i) {
    mxm_4x4(out[i].M, rotations[i].first, rotations[i].second);
  }
  const auto mxm_time_end = cml::testing::usec_time();
  const auto mxm_time = mxm_time_end - mxm_time_start;
  std::printf("mxm time (%d pairs): %.5lf s\n", N, static_cast<double>(mxm_time) / 1e6);

  if(N == 1) for(int i = 0; i < N; ++ i) {
    std::clog << rotations[i].first << std::endl;
    std::clog << rotations[i].second << std::endl;
    std::clog << out[i].M << std::endl;
    cml::matrix44d A(rotations[i].first), B(rotations[i].second);
    std::clog << A * B << std::endl;
  }

  return 0;
}