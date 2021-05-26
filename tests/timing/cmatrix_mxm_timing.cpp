/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <cstdio>
#include <random>
#include <vector>
#include <cml/matrix.h>
#include <cml/quaternion.h>
#include <cml/common/exception.h>
#include <cml/mathlib/matrix/rotation.h>
#include "cmatrix_mxm.h"
#include "timing.h"

using matrix_pair_t = std::pair<matrix44d, matrix44d>;

/* NOTE: d must return values in [0.,1.) */
template<class Gen, class Matrix44T>
void uniform_random_rotation_4(
  Gen& g, std::uniform_real_distribution<>& d, Matrix44T& M)
{
  cml_require(0. <= d.a() && d.a() <= 1.,
    std::invalid_argument, "d not in [0,1.]");

  /* First, create a random unit quaternion (see K. Shoemake, Graphics Gems
   * III):
   */
  const auto two_pi = cml::constants<double>::two_pi();
  const auto u1 = d(g), u2 = d(g), u3 = d(g);
  const auto s1 = std::sqrt(1. - u1), s2 = std::sqrt(u1);
  const auto t1 = two_pi * d(g), t2 = two_pi * d(g);
  const auto w = std::cos(t2) * s2;
  const auto x = std::sin(t1) * s1;
  const auto y = std::cos(t1) * s1;
  const auto z = std::sin(t2) * s2;
  const auto q = cml::quaterniond(w, x, y, z).normalize();

  cml::external44d M_out(&M[0][0]);
  cml::matrix_rotation_quaternion(M_out, q);
}


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
    uniform_random_rotation_4(rng, d, rotations[i].first);
    uniform_random_rotation_4(rng, d, rotations[i].second);
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