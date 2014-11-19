/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/vector/scalar_node.h>
#include <cml/vector/scalar_ops.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_scalar_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::fixed<3>> w;
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::fixed<3>> w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::vector<double, cml::fixed<3>> w;
  w = (cml::vector<double,cml::fixed<3>>(1.,2.,3.) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double av1[] = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> w(aw);
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double av1[] = { 2., 4., 6. };
  double aw[3];
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> w(aw);
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> w;
  w = (cml::vector<double,cml::external<3>>(av1) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w.data(), &av1[0]);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
#else
  BOOST_ERROR("Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double av1[] = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<>> v1(av1,3);
  cml::vector<double, cml::external<>> w(aw,3);
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double av1[] = { 2., 4., 6. };
  double aw[3];
  cml::vector<double, cml::external<>> v1(av1,3);
  cml::vector<double, cml::external<>> w(aw,3);
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v1(av1,3);
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> w;
  w = (cml::vector<double,cml::external<>>(av1,3) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w.data(), &av1[0]);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
#else
  BOOST_ERROR("Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::vector<double, cml::dynamic<>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w;
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::vector<double, cml::dynamic<>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector<double, cml::dynamic<>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::dynamic<>> w;
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::vector<double, cml::dynamic<>> v1 = { 2., 4., 6. };
  cml::vector<double, cml::dynamic<>> w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::vector<double, cml::dynamic<>> v1 = { 1., 2., 3. };
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::vector<double, cml::dynamic<>> w;
  w = (cml::vector<double,cml::dynamic<>>(1.,2.,3.) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
