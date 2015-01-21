/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/coordinate_conversion.h>

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_rotation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(from_cartesian)

BOOST_AUTO_TEST_CASE(to_polar1)
{
  cml::vector2d x;
  cml::polar_to_cartesian(x, 1., cml::rad(45.));
  BOOST_CHECK_CLOSE(x[0], .707107, .001);
  BOOST_CHECK_CLOSE(x[1], .707107, .001);
}

BOOST_AUTO_TEST_CASE(to_polar2)
{
  cml::vector2d x;
  cml::polar_to_cartesian(1., cml::rad(45.), x);
  BOOST_CHECK_CLOSE(x[0], .707107, .001);
  BOOST_CHECK_CLOSE(x[1], .707107, .001);
}


BOOST_AUTO_TEST_CASE(to_cylindrical1)
{
  cml::vector3d x;
  cml::cylindrical_to_cartesian(x, 2, 1., cml::rad(45.), 1.);
  BOOST_CHECK_CLOSE(x[0], .707107, .001);
  BOOST_CHECK_CLOSE(x[1], .707107, .001);
  BOOST_CHECK_CLOSE(x[2], 1., .001);
}

BOOST_AUTO_TEST_CASE(to_cylindrical2)
{
  cml::vector3d x;
  cml::cylindrical_to_cartesian(1., cml::rad(45.), 1., 2, x);
  BOOST_CHECK_CLOSE(x[0], .707107, .001);
  BOOST_CHECK_CLOSE(x[1], .707107, .001);
  BOOST_CHECK_CLOSE(x[2], 1., .001);
}


BOOST_AUTO_TEST_CASE(to_spherical1)
{
  cml::vector3d x;
  cml::spherical_to_cartesian(
    x, 2, cml::colatitude, 1., cml::rad(45.), cml::rad(45.));
  BOOST_CHECK_CLOSE(x[0], .5, .001);
  BOOST_CHECK_CLOSE(x[1], .5, .001);
  BOOST_CHECK_CLOSE(x[2], .707107, .001);
}

BOOST_AUTO_TEST_CASE(to_spherical2)
{
  cml::vector3d x;
  cml::spherical_to_cartesian(
    1., cml::rad(45.), cml::rad(45.), 2, cml::colatitude, x);
  BOOST_CHECK_CLOSE(x[0], .5, .001);
  BOOST_CHECK_CLOSE(x[1], .5, .001);
  BOOST_CHECK_CLOSE(x[2], .707107, .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(to_cartesian)

BOOST_AUTO_TEST_CASE(from_polar1)
{
  cml::vector2d x(std::sqrt(.5), std::sqrt(.5));
  double radius, theta;
  cml::cartesian_to_polar(x, radius, theta);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
}

BOOST_AUTO_TEST_CASE(from_polar2)
{
  cml::vector2d x(std::sqrt(.5), std::sqrt(.5));
  double radius, theta, tolerance = 1e-7;
  cml::cartesian_to_polar(x, radius, theta, tolerance);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
}


BOOST_AUTO_TEST_CASE(from_cylindrical1)
{
  cml::vector3d x(std::sqrt(.5), std::sqrt(.5), 1.);
  double radius, theta, height;
  cml::cartesian_to_cylindrical(x, 2, radius, theta, height);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(height, 1., .001);
}

BOOST_AUTO_TEST_CASE(from_cylindrical2)
{
  cml::vector3d x(std::sqrt(.5), std::sqrt(.5), 1.);
  double radius, theta, height, tolerance = 1e-7;
  cml::cartesian_to_cylindrical(x, 2, radius, theta, height, tolerance);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(height, 1., .001);
}

BOOST_AUTO_TEST_CASE(from_cylindrical3)
{
  cml::vector3d x(std::sqrt(.5), std::sqrt(.5), 1.);
  double radius, theta, height;
  cml::cartesian_to_cylindrical(x, radius, theta, height, 2);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(height, 1., .001);
}


BOOST_AUTO_TEST_CASE(from_spherical1)
{
  cml::vector3d x(.5, .5, std::sqrt(.5));
  double radius, theta, phi;
  cml::cartesian_to_spherical(x, 2, cml::colatitude, radius, theta, phi);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(phi, cml::rad(45.), .001);
}

BOOST_AUTO_TEST_CASE(from_spherical2)
{
  cml::vector3d x(.5, .5, std::sqrt(.5));
  double radius, theta, phi, tolerance = 1e-7;
  cml::cartesian_to_spherical(
    x, 2, cml::colatitude, radius, theta, phi, tolerance);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(phi, cml::rad(45.), .001);
}

BOOST_AUTO_TEST_CASE(from_spherical3)
{
  cml::vector3d x(.5, .5, std::sqrt(.5));
  double radius, theta, phi;
  cml::cartesian_to_spherical(
    x, radius, theta, phi, 2, cml::colatitude);
  BOOST_CHECK_CLOSE(radius, 1., .001);
  BOOST_CHECK_CLOSE(theta, cml::rad(45.), .001);
  BOOST_CHECK_CLOSE(phi, cml::rad(45.), .001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
