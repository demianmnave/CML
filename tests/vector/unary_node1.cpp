/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE unary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = - v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = - v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = + v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = + v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  BOOST_CHECK_EQUAL(w.size(), 3);
  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);

  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);

  w = - v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);

  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);

  w = + v;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);

  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);
  BOOST_CHECK_EQUAL(w.size(), 3);

  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
