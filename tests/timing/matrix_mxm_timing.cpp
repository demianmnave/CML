/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <limits>
#include <format>
#include <iostream>

/* Need the matrix type and CML type system specializations: */
#include CML_TIMING_MxM_INL

#include "timing.h"
#include "make_rotation_matrix_pairs.h"

using namespace cml::testing;

int
main(int argc, const char** argv)
{
  long N = std::numeric_limits<long>::max();
  if(argc == 2) {
    char* a_end = nullptr;
    N = std::strtol(argv[1], &a_end, 10);
  } else {
    N = 100'000;
  }

  if(0 >= N || N == LONG_MAX) {
    std::cerr << argv[0] << ": invalid sample count " << argv[1] << std::endl;
    return 1;
  }

  /* Pre-generate N repeatable pairs of random 4x4 rotations: */
  const auto prep_time_start = chrono_t::now();
  const auto rotations = cml::testing::make_rotation_matrix_pairs<matrix44d>(N);
  const auto prep_time_end = chrono_t::now();
  const auto prep_time = prep_time_end - prep_time_start;

  std::cout
    << std::format("prep time ({} pairs): {:%Q} s\n", N, prep_time / 1e9);

  /* Time N multiplications: */
  using data_t = struct
  {
    matrix44d M;
  };

  constexpr auto trials = 1000;

  std::vector<data_t> out(N);
  auto mxm_time = chrono_t::duration{};
  for(int i = 0; i < N; ++i) {
    const auto mxm_time_start = chrono_t::now();
    for(int j = 0; j < trials; ++j) {
      mxm_4x4(out[i].M, std::get<0>(rotations[i]), std::get<1>(rotations[i]));
    }
    const auto mxm_time_end = chrono_t::now();
    mxm_time += (mxm_time_end - mxm_time_start);
  }
  std::cout << std::format("mxm time ({} pairs): {:%Q} us\n", N, (mxm_time / 1e3) / N / trials);

  const auto check_time_start = chrono_t::now();
  std::uint_fast64_t errors = 0;
  int last_error = -1;
  for(int i = 0; i < N; ++i) {
    const auto& A = std::get<2>(rotations[i]);
    const auto& B = out[i].M;

    for(int j = 0; j < 4; ++j) {
      for(int k = 0; k < 4; ++k) {
        const auto diff =
          std::abs(cml::detail::get(A, j, k) - cml::detail::get(B, j, k));
        if(diff > 10. * cml::scalar_traits<double>::epsilon()) {
          ++errors;
          last_error = i;
        }
      }
    }
  }
  const auto check_time_end = chrono_t::now();
  const auto check_time = check_time_end - check_time_start;
  std::cout
    << std::format("check time ({} pairs): {:%Q} s\n", N, check_time / 1e9);
  if(errors == 0) return 0;

  std::cerr << std::format("error: found {} miscalculations\n", errors);
  {
    std::cerr << "have:\n" << std::get<0>(rotations[last_error]) << '\n';
    std::cerr << "    *\n" << std::get<1>(rotations[last_error]) << '\n';
    std::cerr << "want:\n" << std::get<2>(rotations[last_error]) << '\n';
    std::cerr << " got:\n" << out[last_error].M << '\n';
  }


  return 1;
}