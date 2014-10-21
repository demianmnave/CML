/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE unary_node1
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::vector<double, cml::fixed<3>> v;
  auto xpr = - v;
  BOOST_CHECK_EQUAL(xpr.size(), 3);

  v[0] = 1.;
  BOOST_CHECK_EQUAL(xpr[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  double av[3] = { 0., 0., 0. };
  cml::vector<double, cml::external<3>> v(av);
  auto xpr = - v;
  BOOST_CHECK_EQUAL(xpr.size(), 3);

  v[0] = 1.;
  BOOST_CHECK_EQUAL(xpr[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::vector<double, cml::fixed<3>> v;
  auto xpr = + v;
  BOOST_CHECK_EQUAL(xpr.size(), 3);

  v[0] = 1.;
  BOOST_CHECK_EQUAL(xpr[0], 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  double av[3] = { 0., 0., 0. };
  cml::vector<double, cml::external<3>> v(av);
  auto xpr = + v;
  BOOST_CHECK_EQUAL(xpr.size(), 3);

  v[0] = 1.;
  BOOST_CHECK_EQUAL(xpr[0], 1.);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
