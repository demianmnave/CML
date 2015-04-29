/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/vector/rotation.h>

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_rotation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(rotation_3D)

BOOST_AUTO_TEST_CASE(world_axis1)
{
  auto vx = cml::rotate_vector(
    cml::vector3d(0., 1., 0.), cml::vector3d(1., 0., 0.), cml::rad(90.));
  BOOST_CHECK_SMALL(vx[0], 1e-7);
  BOOST_CHECK_SMALL(vx[1], 1e-7);
  BOOST_CHECK_CLOSE(vx[2], 1., .0001);

  auto vy = cml::rotate_vector(
    cml::vector3d(-1., 0., 0.), cml::vector3d(0., 1., 0.), cml::rad(90.));
  BOOST_CHECK_SMALL(vy[0], 1e-7);
  BOOST_CHECK_SMALL(vy[1], 1e-7);
  BOOST_CHECK_CLOSE(vy[2], 1., .0001);

  auto vz = cml::rotate_vector(
    cml::vector3d(1., 0., 0.), cml::vector3d(0., 0., 1.), cml::rad(90.));
  BOOST_CHECK_SMALL(vz[0], 1e-7);
  BOOST_CHECK_CLOSE(vz[1], 1., .0001);
  BOOST_CHECK_SMALL(vz[2], 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
