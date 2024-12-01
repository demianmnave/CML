/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <cstdio>
#include <iostream>

/* Need the matrix type and CML type system specializations: */
#include CML_TIMING_MxM_INL

#include "timing.h"
#include "make_rotation_matrix_pairs.h"

int
main(int argc, const char** argv)
{
  long N = LONG_MAX;
  if(argc == 2) {
    char* a_end = nullptr;
    N = std::strtol(argv[1], &a_end, 10);
  } else {
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
  std::printf("prep time (%d pairs): %.5lf s\n", N,
    static_cast<double>(prep_time) / 1e6);

  /* Time N multiplications: */
  using data_t = struct
  {
    matrix44d M;
  };

  std::vector<data_t> out(N);
  const auto mxm_time_start = cml::testing::usec_time();
  for(int i = 0; i < N; ++i) {
    mxm_4x4(out[i].M, std::get<0>(rotations[i]), std::get<1>(rotations[i]));
  }
  const auto mxm_time_end = cml::testing::usec_time();
  const auto mxm_time = mxm_time_end - mxm_time_start;
  std::printf("mxm time (%d pairs): %.5lf s\n", N,
    static_cast<double>(mxm_time) / 1e6);

  const auto check_time_start = cml::testing::usec_time();
  std::uint_fast64_t errors = 0;
  for(int i = 0; i < N; ++i) {
    const auto& A = std::get<2>(rotations[i]);
    const auto& B = out[i].M;

    for(int j = 0; j < 4; ++j) {
      for(int k = 0; k < 4; ++k) {
        const auto diff =
          std::abs(cml::detail::get(A, j, k) - cml::detail::get(B, j, k));
        if(diff > 10. * cml::scalar_traits<double>::epsilon()) {
          ++errors;
        }
      }
    }
  }
  const auto check_time_end = cml::testing::usec_time();
  const auto check_time = check_time_end - check_time_start;
  std::printf("check time (%d pairs): %.5lf s\n", N,
    static_cast<double>(check_time) / 1e6);
  if(errors > 0) std::printf(" Warning: found %llu errors\n", errors);

  return 0;
}
