/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>
#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE scalar_node1
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  auto xpr = 2.*v1;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 4.);
  BOOST_CHECK_EQUAL(xpr[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  auto xpr = 2.*v1;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 4.);
  BOOST_CHECK_EQUAL(xpr[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  auto xpr = v1/2.;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 2.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  double av1[] = { 2., 4., 6. };
  cml::vector<double, cml::external<3>> v1(av1);
  auto xpr = v1/2.;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 2.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
