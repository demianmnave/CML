/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/subvector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE subvector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(sub1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(sub1)
{
  cml::vector<double, cml::dynamic<>> v1 = { 1., 2., 3. };
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, -1);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
