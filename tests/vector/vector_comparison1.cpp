/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/comparison.h>

#include <cml/vector/fixed.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_comparison1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(less_greater1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 2., 2., 2. };
  BOOST_REQUIRE(v < w);
  BOOST_REQUIRE(w > v);
}

BOOST_AUTO_TEST_CASE(less_greater2)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 2. };
  BOOST_REQUIRE(w < v);
  BOOST_REQUIRE(v > w);
}

BOOST_AUTO_TEST_CASE(less_greater3)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  BOOST_REQUIRE(!(w < v));
  BOOST_REQUIRE(!(v < w));
}

BOOST_AUTO_TEST_CASE(less_equal1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  BOOST_REQUIRE(v <= w);
  BOOST_REQUIRE(w <= v);
}

BOOST_AUTO_TEST_CASE(less_equal2)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 4. };
  BOOST_REQUIRE(v <= w);
  BOOST_REQUIRE(!(w <= v));
}

BOOST_AUTO_TEST_CASE(greater_equal1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  BOOST_REQUIRE(v >= w);
  BOOST_REQUIRE(w >= v);
}

BOOST_AUTO_TEST_CASE(greater_equal2)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 4. };
  BOOST_REQUIRE(w >= v);
  BOOST_REQUIRE(!(v >= w));
}

BOOST_AUTO_TEST_CASE(equal1)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  BOOST_REQUIRE(w == v);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
