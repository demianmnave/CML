/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE functions1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(length_squared1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  double l2 = v1.length_squared();
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  double l = v1.length();
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  double l2 = v1.normalize().length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  v1.zero();
  BOOST_CHECK_EQUAL(v1[0], 0.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
  BOOST_CHECK_EQUAL(v1.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  cml::vector<double, cml::fixed<3>> v2 = { 2., 0., 3. };
  v1.minimize(v2);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  cml::vector<double, cml::fixed<3>> v2 = { 2., 0., 3. };
  v1.maximize(v2);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 1.);
  BOOST_CHECK_EQUAL(v1[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 0., 0., 0. };
  v1.cardinal(0);
  BOOST_CHECK_EQUAL(v1[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
