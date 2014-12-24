/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/dot.h>

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE dot1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(dot1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  cml::vector3d v2 = { 2., 2., 2. };
  double dp = cml::dot(v1,v2);
  BOOST_CHECK_EQUAL(dp, 6.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vectord v1;
  BOOST_CHECK_THROW(cml::dot(v1,v1), cml::minimum_vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  cml::vectord v1(2,3);
  cml::vector3d v2(2,3,3);
  BOOST_CHECK_THROW(cml::dot(v1,v2), cml::incompatible_vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check3)
{
  cml::vector3d v1(2,3,3);
  cml::vectord v2(2,3);
  BOOST_CHECK_THROW(cml::dot(v1,v2), cml::incompatible_vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
