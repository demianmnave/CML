/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <limits>
#include <format>
#include <iostream>

/* Need the matrix type and CML type system specializations: */
#include CML_TIMING_MxV_INL

#include "timing.h"
#include "make_matrix_vector_pairs.h"

using layout_tag = cml::layout_tag_trait_of_t<matrix44d>;
#ifdef CML_TIMING_ROW_MAJOR
static_assert(std::is_same_v<layout_tag, cml::row_major>);
#endif
#ifdef CML_TIMING_COL_MAJOR
static_assert(std::is_same_v<layout_tag, cml::col_major>);
#endif

using namespace cml::testing;

int
main(int argc, const char** argv)
{
  // int K = 4;

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

  /* Pre-generate N repeatable pairs of random vector rotations: */
  const auto prep_time_start = chrono_t::now();
  const auto rotations =
    cml::testing::make_matrix_vector_pairs<matrix44d, vector4d, 4>(N);
  const auto prep_time_end = chrono_t::now();
  const auto prep_time = prep_time_end - prep_time_start;

  std::cout
    << std::format("prep time ({} pairs): {:%Q} s\n", N, prep_time / 1e9);

  /* Time N multiplications: */
  using data_t = struct
  {
    vector4d x;
  };

  constexpr auto trials = 1000;

  std::vector<data_t> out(N);
  auto mxv_time = chrono_t::duration{};
  for(int i = 0; i < N; ++i) {
    const auto mxv_time_start = chrono_t::now();
    for(int j = 0; j < trials; ++j) {
      mxv_4x1(out[i].x, std::get<0>(rotations[i]), std::get<1>(rotations[i]));
    }
    const auto mxv_time_end = chrono_t::now();
    mxv_time += (mxv_time_end - mxv_time_start);
  }
  std::cout << std::format("mxv time ({} pairs): {:%Q} us\n", N,
    (mxv_time / 1e3) / N / trials);

  const auto check_time_start = chrono_t::now();
  std::uint_fast64_t errors = 0;
  int last_error = -1;
  for(int i = 0; i < N; ++i) {
    const auto& A = std::get<2>(rotations[i]);
    const auto& B = out[i].x;

    for(int j = 0; j < 4; ++j) {
      const auto diff =
        std::abs(cml::detail::get(A, j) - cml::detail::get(B, j));
      if(diff > 10. * cml::scalar_traits<double>::epsilon()) {
        ++errors;
        last_error = i;
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
    std::cerr << " got:\n" << out[last_error].x << '\n';
  }

  return 1;
}
