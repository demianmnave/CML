/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/quaternion.h>
#include <cml/common/exception.h>
#include <cml/mathlib/matrix/rotation.h>

namespace cml::testing {

/* NOTE: d must return values in [0.,1.) */
// TODO make this an official CML function?
template<class Gen, class Matrix44dT>
void
uniform_random_rotation_4(Gen& g, std::uniform_real_distribution<>& d,
  Matrix44dT& M)
{
  using layout = layout_tag_trait_of_t<Matrix44dT>;
  using scalar_type = value_type_trait_of_t<Matrix44dT>;
  using external_type =
    cml::matrix<scalar_type, external<4, 4>, col_basis, layout>;
  cml_require(0. <= d.a() && d.a() <= 1., std::invalid_argument,
    "d not in [0,1.]");

  /* Create a random unit quaternion (see K. Shoemake, Graphics Gems III): */
  const auto two_pi = cml::constants<scalar_type>::two_pi();
  const auto u = d(g), u1 = d(g), u2 = d(g);
  const auto s1 = std::sqrt(1. - u), s2 = std::sqrt(u);
  const auto t1 = two_pi * u1, t2 = two_pi * u2;
  const auto w = std::cos(t2) * s2;
  const auto x = std::sin(t1) * s1;
  const auto y = std::cos(t1) * s1;
  const auto z = std::sin(t2) * s2;
  const auto q = cml::quaterniond(x, y, z, w).normalize();

  external_type M_out(std::addressof(cml::detail::get(M, 0, 0)));
  cml::matrix_rotation_quaternion(M_out, q);
}

}  // namespace cml::testing
