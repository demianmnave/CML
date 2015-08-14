/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/transform.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/mathlib/vector/transform.h>
#include <cml/mathlib/matrix/generators.h>

#include <cml/util.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_transform1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(transform_3D)

BOOST_AUTO_TEST_CASE(look_at_rh_1)
{
  auto M = cml::zero_4x4();
  cml::matrix_look_at_RH(M,
    cml::vector3d(1.,0.,0.),
    cml::vector3d(0.,0.,0.),
    cml::vector3d(0.,0.,1.));

  auto v = cml::vector3d(1., 1., 1.);
  auto w = cml::transform_point(M,v);

  BOOST_CHECK_CLOSE(w[0], 1., .0001);
  BOOST_CHECK_CLOSE(w[1], 1., .0001);
  BOOST_CHECK_SMALL(w[2], 1e-8);
}

BOOST_AUTO_TEST_CASE(look_at_lh_1)
{
  auto M = cml::zero_4x4();
  cml::matrix_look_at_LH(M,
    cml::vector3d(1.,0.,0.),
    cml::vector3d(0.,0.,0.),
    cml::vector3d(0.,0.,1.));

  auto v = cml::vector3d(1., 1., 1.);
  auto w = cml::transform_point(M,v);

  BOOST_CHECK_CLOSE(w[0], -1., .0001);
  BOOST_CHECK_CLOSE(w[1],  1., .0001);
  BOOST_CHECK_SMALL(w[2],  1e-8);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
