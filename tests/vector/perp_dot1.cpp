/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/perp_dot.h>

/* Testing headers: */
#define BOOST_TEST_MODULE perp_dot1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(perp_dot1)
{
  cml::vector<double, cml::fixed<2>> v1 = { 1., 0. };
  cml::vector<double, cml::fixed<2>> v2 = { 0., 1. };
  double pd = cml::perp_dot(v1,v2);
  BOOST_CHECK_EQUAL(pd, 1.);
}

BOOST_AUTO_TEST_CASE(perp_dot2)
{
  cml::vector<double, cml::dynamic<>> v1(2., 8.);
  cml::vector<double, cml::fixed<2>> v2(3., 7.);
  double pd = cml::perp_dot(v1,v2);
  BOOST_CHECK_EQUAL(pd, -10.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vector<double, cml::dynamic<>> v1(2,3,3);
  cml::vector<double, cml::fixed<2>> v2(2,3);
  BOOST_CHECK_THROW(cml::perp_dot(v1,v2), cml::vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  cml::vector<double, cml::fixed<2>> v1(2,3);
  cml::vector<double, cml::dynamic<>> v2(2,3,3);
  BOOST_CHECK_THROW(cml::perp_dot(v1,v2), cml::vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
