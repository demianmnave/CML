/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE binary_node1
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 - v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], -3.);
  BOOST_CHECK_EQUAL(xpr[1], -3.);
  BOOST_CHECK_EQUAL(xpr[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 + v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 5.);
  BOOST_CHECK_EQUAL(xpr[1], 7.);
  BOOST_CHECK_EQUAL(xpr[2], 9.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 - v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], -3.);
  BOOST_CHECK_EQUAL(xpr[1], -3.);
  BOOST_CHECK_EQUAL(xpr[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 + v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 5.);
  BOOST_CHECK_EQUAL(xpr[1], 7.);
  BOOST_CHECK_EQUAL(xpr[2], 9.);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
