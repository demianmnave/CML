/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_scalar_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = 2.*v1;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = 2.*v1;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::fixed<3>> w;
  w = v1/2.;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::fixed<3>> w = v1/2.;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double av1[] = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::fixed<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> w(aw);
  w = 2.*v1;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double av1[] = { 2., 4., 6. };
  double aw[3];
  cml::vector<double, cml::fixed<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> w(aw);
  w = v1/2.;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
