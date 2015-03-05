/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/quaternion/product.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/types.h>
#include <cml/util/vector_print.h>
#include <cml/util/quaternion_print.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(ip1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  cml::quaterniond_ip r = { 4., 3., 2., 1. };
  auto w = q*r;
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 24.);
  BOOST_CHECK_EQUAL(w[2], 6.);
  BOOST_CHECK_EQUAL(w[3], -12.);
}

BOOST_AUTO_TEST_CASE(rp1)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  cml::quaterniond_rp r = { 4., 3., 2., 1. };
  auto w = q*r;
  BOOST_CHECK_EQUAL(w[0], -12.);
  BOOST_CHECK_EQUAL(w[1], 6.);
  BOOST_CHECK_EQUAL(w[2], 24.);
  BOOST_CHECK_EQUAL(w[3], 12.);
}

BOOST_AUTO_TEST_CASE(in1)
{
  cml::quaterniond_in q = { 1., 2., 3., 4. };
  cml::quaterniond_in r = { 4., 3., 2., 1. };
  auto w = q*r;
  BOOST_CHECK_EQUAL(w[0], 22.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 16.);
  BOOST_CHECK_EQUAL(w[3], -12.);
}

BOOST_AUTO_TEST_CASE(rn1)
{
  cml::quaterniond_rn q = { 1., 2., 3., 4. };
  cml::quaterniond_rn r = { 4., 3., 2., 1. };
  auto w = q*r;
  BOOST_CHECK_EQUAL(w[0], -12.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 4.);
  BOOST_CHECK_EQUAL(w[3], 22.);
}

BOOST_AUTO_TEST_CASE(ip_assign1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  cml::quaterniond_ip r = { 4., 3., 2., 1. };
  q *= r;
  BOOST_CHECK_EQUAL(q[0], 12.);
  BOOST_CHECK_EQUAL(q[1], 24.);
  BOOST_CHECK_EQUAL(q[2], 6.);
  BOOST_CHECK_EQUAL(q[3], -12.);
}

BOOST_AUTO_TEST_CASE(rp_assign1)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  cml::quaterniond_rp r = { 4., 3., 2., 1. };
  q *= r;
  BOOST_CHECK_EQUAL(q[0], -12.);
  BOOST_CHECK_EQUAL(q[1], 6.);
  BOOST_CHECK_EQUAL(q[2], 24.);
  BOOST_CHECK_EQUAL(q[3], 12.);
}

BOOST_AUTO_TEST_CASE(in_assign1)
{
  cml::quaterniond_in q = { 1., 2., 3., 4. };
  cml::quaterniond_in r = { 4., 3., 2., 1. };
  q *= r;
  BOOST_CHECK_EQUAL(q[0], 22.);
  BOOST_CHECK_EQUAL(q[1], 4.);
  BOOST_CHECK_EQUAL(q[2], 16.);
  BOOST_CHECK_EQUAL(q[3], -12.);
}

BOOST_AUTO_TEST_CASE(rn_assign1)
{
  cml::quaterniond_rn q = { 1., 2., 3., 4. };
  cml::quaterniond_rn r = { 4., 3., 2., 1. };
  q *= r;
  BOOST_CHECK_EQUAL(q[0], -12.);
  BOOST_CHECK_EQUAL(q[1], 16.);
  BOOST_CHECK_EQUAL(q[2], 4.);
  BOOST_CHECK_EQUAL(q[3], 22.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
