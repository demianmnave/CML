/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/quaternion/comparison.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_comparison1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(less_greater1)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 2., 2., 2., 2. };
  BOOST_REQUIRE(v < w);
  BOOST_REQUIRE(w > v);
}

BOOST_AUTO_TEST_CASE(less_greater2)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 2., 4. };
  BOOST_REQUIRE(w < v);
  BOOST_REQUIRE(v > w);
}

BOOST_AUTO_TEST_CASE(less_greater3)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 3., 4. };
  BOOST_REQUIRE(!(w < v));
  BOOST_REQUIRE(!(v < w));
}

BOOST_AUTO_TEST_CASE(less_equal1)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 3., 4. };
  BOOST_REQUIRE(v <= w);
  BOOST_REQUIRE(w <= v);
}

BOOST_AUTO_TEST_CASE(less_equal2)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 4., 4. };
  BOOST_REQUIRE(v <= w);
  BOOST_REQUIRE(!(w <= v));
}

BOOST_AUTO_TEST_CASE(greater_equal1)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 3., 4. };
  BOOST_REQUIRE(v >= w);
  BOOST_REQUIRE(w >= v);
}

BOOST_AUTO_TEST_CASE(greater_equal2)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 4., 4. };
  BOOST_REQUIRE(w >= v);
  BOOST_REQUIRE(!(v >= w));
}

BOOST_AUTO_TEST_CASE(equal1)
{
  cml::quaterniond v = { 1., 2., 3., 4. };
  cml::quaterniond w = { 1., 2., 3., 4. };
  BOOST_REQUIRE(w == v);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
