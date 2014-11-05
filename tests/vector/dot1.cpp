/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/dot.h>

/* Testing headers: */
#define BOOST_TEST_MODULE dot1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(dot1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 1., 1. };
  cml::vector<double, cml::fixed<3>> v2 = { 2., 2., 2. };
  double dp = cml::dot(v1,v2);
  BOOST_CHECK_EQUAL(dp, 6.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vector<double, cml::dynamic<>> v1;
  BOOST_REQUIRE_THROW(cml::dot(v1,v1), cml::minimum_vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  cml::vector<double, cml::dynamic<>> v1(2,3);
  cml::vector<double, cml::fixed<3>> v2(2,3,3);
  BOOST_REQUIRE_THROW(cml::dot(v1,v2), cml::incompatible_vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check3)
{
  cml::vector<double, cml::fixed<3>> v1(2,3,3);
  cml::vector<double, cml::dynamic<>> v2(2,3);
  BOOST_REQUIRE_THROW(cml::dot(v1,v2), cml::incompatible_vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
