/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/conjugate_node.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/conjugate.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE conjugate1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(readable1)
{
  const cml::quaterniond_ip q(1., 2., 3., 4.);
  auto xpr = q.conjugate();
  BOOST_CHECK_EQUAL(xpr[0], - 1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3],   4.);
}

BOOST_AUTO_TEST_CASE(readable2)
{
  const cml::quaterniond_rp q(1., 2., 3., 4.);
  auto xpr = q.conjugate();
  BOOST_CHECK_EQUAL(xpr[0],   1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3], - 4.);
}

BOOST_AUTO_TEST_CASE(writable1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  q.conjugate();
  BOOST_CHECK_EQUAL(q[0], - 1.);
  BOOST_CHECK_EQUAL(q[1], - 2.);
  BOOST_CHECK_EQUAL(q[2], - 3.);
  BOOST_CHECK_EQUAL(q[3],   4.);
}

BOOST_AUTO_TEST_CASE(writable2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  q.conjugate();
  BOOST_CHECK_EQUAL(q[0],   1.);
  BOOST_CHECK_EQUAL(q[1], - 2.);
  BOOST_CHECK_EQUAL(q[2], - 3.);
  BOOST_CHECK_EQUAL(q[3], - 4.);
}

BOOST_AUTO_TEST_CASE(function1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  auto xpr = cml::conjugate(q);
  BOOST_CHECK_EQUAL(xpr[0], - 1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3],   4.);
}

BOOST_AUTO_TEST_CASE(function2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  auto xpr = cml::conjugate(q);
  BOOST_CHECK_EQUAL(xpr[0],   1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3], - 4.);
}

BOOST_AUTO_TEST_CASE(temporary1)
{
  auto xpr = cml::conjugate(cml::quaterniond_ip(1., 2., 3., 4.));
  BOOST_CHECK_EQUAL(xpr[0], - 1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3],   4.);
}

BOOST_AUTO_TEST_CASE(conjugate2)
{
  auto xpr = cml::conjugate(cml::quaterniond_rp(1., 2., 3., 4.));
  BOOST_CHECK_EQUAL(xpr[0],   1.);
  BOOST_CHECK_EQUAL(xpr[1], - 2.);
  BOOST_CHECK_EQUAL(xpr[2], - 3.);
  BOOST_CHECK_EQUAL(xpr[3], - 4.);
}

BOOST_AUTO_TEST_SUITE_END()


// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
