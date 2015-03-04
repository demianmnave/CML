/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/functions.h>

#include <cml/quaternion.h>
#include <cml/util/vector_print.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_functions1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(real1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_EQUAL(cml::real(q), 4.);
}

BOOST_AUTO_TEST_CASE(real2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_EQUAL(cml::real(q), 1.);
}

BOOST_AUTO_TEST_CASE(length_squared1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_CLOSE(cml::length_squared(q), 30., .0001);
}

BOOST_AUTO_TEST_CASE(length1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_CLOSE(cml::length(q), std::sqrt(30.), .0001);
}

BOOST_AUTO_TEST_CASE(norm1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_CLOSE(cml::norm(q), 30., .0001);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  q.normalize();
  double l2 = q.length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  double l2 = cml::normalize(q).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(identity1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  double l2 = cml::identity(q).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::quaterniond q;
  q.zero();
  BOOST_CHECK_EQUAL(q[0], 0.);
  BOOST_CHECK_EQUAL(q[1], 0.);
  BOOST_CHECK_EQUAL(q[2], 0.);
  BOOST_CHECK_EQUAL(q[3], 0.);
  BOOST_CHECK_EQUAL(q.length(), 0.);
}

BOOST_AUTO_TEST_CASE(log1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  auto lnq = cml::log(q);
  BOOST_CHECK_CLOSE(lnq[0], 0.200991168205, .001);
  BOOST_CHECK_CLOSE(lnq[1], 0.401982336411, .001);
  BOOST_CHECK_CLOSE(lnq[2], 0.602973504616, .001);
  BOOST_CHECK_CLOSE(lnq[3], 1.700598690831, .001);
}

BOOST_AUTO_TEST_CASE(log2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  auto lnq = cml::log(q);
  BOOST_CHECK_CLOSE(lnq[0], 1.700598690831, .001);
  BOOST_CHECK_CLOSE(lnq[1], 0.515190292664, .001);
  BOOST_CHECK_CLOSE(lnq[2], 0.772785438996, .001);
  BOOST_CHECK_CLOSE(lnq[3], 1.030380585328, .001);
}

BOOST_AUTO_TEST_CASE(log3)
{
  auto lnq = cml::quaterniond_ip(1., 2., 3., 4.).log();
  BOOST_CHECK_CLOSE(lnq[0], 0.200991168205, .001);
  BOOST_CHECK_CLOSE(lnq[1], 0.401982336411, .001);
  BOOST_CHECK_CLOSE(lnq[2], 0.602973504616, .001);
  BOOST_CHECK_CLOSE(lnq[3], 1.700598690831, .001);
}

BOOST_AUTO_TEST_CASE(log4)
{
  auto lnq = cml::quaterniond_rp(1., 2., 3., 4.).log();
  BOOST_CHECK_CLOSE(lnq[0], 1.700598690831, .001);
  BOOST_CHECK_CLOSE(lnq[1], 0.515190292664, .001);
  BOOST_CHECK_CLOSE(lnq[2], 0.772785438996, .001);
  BOOST_CHECK_CLOSE(lnq[3], 1.030380585328, .001);
}

BOOST_AUTO_TEST_CASE(exp1)
{
  cml::quaterniond_ip q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  auto lnq = cml::exp(q);
  BOOST_CHECK_CLOSE(lnq[0], -8.24002526676, .001);
  BOOST_CHECK_CLOSE(lnq[1], -16.4800505335, .001);
  BOOST_CHECK_CLOSE(lnq[2], -24.7200758003, .001);
  BOOST_CHECK_CLOSE(lnq[3], -45.0598020134, .001);
}

BOOST_AUTO_TEST_CASE(exp2)
{
  cml::quaterniond_rp q = { 1., 2., 3., 4. };
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  auto lnq = cml::exp(q);
  BOOST_CHECK_CLOSE(lnq[0],  1.69392272368, .001);
  BOOST_CHECK_CLOSE(lnq[1], -0.78955962454, .001);
  BOOST_CHECK_CLOSE(lnq[2], -1.18433943681, .001);
  BOOST_CHECK_CLOSE(lnq[3], -1.57911924908, .001);
}

BOOST_AUTO_TEST_CASE(exp3)
{
  auto lnq = cml::quaterniond_ip(1., 2., 3., 4.).exp();
  BOOST_CHECK_CLOSE(lnq[0], -8.24002526676, .001);
  BOOST_CHECK_CLOSE(lnq[1], -16.4800505335, .001);
  BOOST_CHECK_CLOSE(lnq[2], -24.7200758003, .001);
  BOOST_CHECK_CLOSE(lnq[3], -45.0598020134, .001);
}

BOOST_AUTO_TEST_CASE(exp4)
{
  auto lnq = cml::quaterniond_rp(1., 2., 3., 4.).exp();
  BOOST_CHECK_CLOSE(lnq[0],  1.69392272368, .001);
  BOOST_CHECK_CLOSE(lnq[1], -0.78955962454, .001);
  BOOST_CHECK_CLOSE(lnq[2], -1.18433943681, .001);
  BOOST_CHECK_CLOSE(lnq[3], -1.57911924908, .001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
