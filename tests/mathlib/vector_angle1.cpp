/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/vector_angle.h>

#include <cml/scalar/functions.h>
#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_angle1
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(signed_2D_1)
{
  auto v1 = cml::vector2d(1., 0.);
  auto v2 = cml::vector2d(0., 1.);
  auto a = cml::signed_angle_2D(v1,v2);
  BOOST_CHECK_CLOSE(a, M_PI/2., .001);
}

BOOST_AUTO_TEST_CASE(signed_2D_2)
{
  auto v1 = cml::vector2d(1., 0.);
  auto v2 = cml::vector2d(0., 1.);
  auto a = cml::signed_angle_2D(v2,v1);
  BOOST_CHECK_CLOSE(a, - M_PI/2., .001);
}

BOOST_AUTO_TEST_CASE(unsigned_2D_2)
{
  auto v1 = cml::vector2d(1., 0.);
  auto v2 = cml::vector2d(0., 1.);
  auto a = cml::unsigned_angle_2D(v2,v1);
  BOOST_CHECK_CLOSE(a, M_PI/2., .001);
}


BOOST_AUTO_TEST_CASE(signed_3D_1)
{
  auto v1 = cml::vector3d(1., 0., 0.);
  auto v2 = cml::vector3d(0., 1., 0.);
  auto reference = cml::vector3d(0., 0., 1.);
  auto a = cml::signed_angle(v1,v2, reference);
  BOOST_CHECK_CLOSE(a, M_PI/2., .001);
}

BOOST_AUTO_TEST_CASE(signed_3D_2)
{
  auto v1 = cml::vector3d(1., 0., 0.);
  auto v2 = cml::vector3d(0., 1., 0.);
  auto reference = - cml::vector3d(0., 0., 1.);
  auto a = cml::signed_angle(v1, v2, reference);
  BOOST_CHECK_CLOSE(a, - M_PI/2., .001);
}

BOOST_AUTO_TEST_CASE(unsigned_3D_1)
{
  auto v1 = cml::vector3d(1., 0., 0.);
  auto v2 = cml::vector3d(0., 1., 0.);
  auto a = cml::unsigned_angle(v1,v2);
  BOOST_CHECK_CLOSE(a, M_PI/2., .001);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
