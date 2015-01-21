/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/rotation.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_rotation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(rotation_2D)

BOOST_AUTO_TEST_CASE(rotation1)
{
  cml::matrix22d M;
  cml::matrix_rotation_2D(M, cml::rad(90.));
  auto v = M*cml::vector2d(0., 1.);
  BOOST_CHECK_CLOSE(v[0], -1., .0001);
  BOOST_CHECK_SMALL(v[1], 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(rotation_3D)

BOOST_AUTO_TEST_CASE(rotation1)
{
  cml::matrix33d M;
  cml::matrix_rotation_axis_angle(
    M, cml::vector3d(1., 0., 0.), cml::rad(90.));
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(euler1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(90.), 0., 0., cml::euler_order_xyz);

  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(euler_derivaties1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler_derivatives(
    M, 0, cml::rad(90.), 0., 0., cml::euler_order_xyz);

  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_CLOSE(v[1], -1., .0001);
  BOOST_CHECK_SMALL(v[2], 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
