/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/mathlib/vector/misc.h>

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_misc1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(project_to_hplane1)
{
  auto v = cml::vector3d(1., 1., 1.);
  auto n = cml::vector3d(0., 0., 1.);
  auto p = cml::project_to_hplane(v, n);
  BOOST_CHECK_EQUAL(p[0], 1.);
  BOOST_CHECK_EQUAL(p[1], 1.);
  BOOST_CHECK_EQUAL(p[2], 0.);
}

BOOST_AUTO_TEST_CASE(perp1)
{
  auto v = cml::vector2d(1., 1.);
  auto p = cml::perp(v);
  BOOST_CHECK_EQUAL(p[0], -1.);
  BOOST_CHECK_EQUAL(p[1], 1.);
}

BOOST_AUTO_TEST_CASE(city_block1)
{
  auto v1 = cml::vector3d(3., 7., 1.);
  auto v2 = cml::vector3d(1., 9., 2.);
  auto c = cml::manhattan_distance(v1, v2);
  BOOST_CHECK_CLOSE(c, 5., .001);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
