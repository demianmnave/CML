/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/imaginary_node.h>

#include <cml/vector/fixed.h>
#include <cml/quaternion/fixed.h>
#include <cml/quaternion/imaginary.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE imaginary1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(imaginary1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  auto xpr = cml::imaginary(q);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 3);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 2.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

BOOST_AUTO_TEST_CASE(imaginary2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  auto xpr = cml::imaginary(q);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 3);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
  BOOST_CHECK_EQUAL(xpr[2], 4.);
}

BOOST_AUTO_TEST_SUITE_END()


// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
