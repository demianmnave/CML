/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/hadamard_product.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_hadamard_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(hadamard1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w;
  w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(hadamard2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w;
  w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(hadamard1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d w(aw);
  w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d v3(av3);
  cml::external3d w(aw);
  w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(hadamard1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::externalnd v1(av1,3);
  cml::externalnd v2(av2,3);
  cml::externalnd w(aw,3);
  w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::externalnd v1(av1,3);
  cml::externalnd v2(av2,3);
  cml::externalnd v3(av3,3);
  cml::externalnd w(aw,3);
  w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(hadamard1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w;
  w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(hadamard2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w = cml::hadamard(v1,v2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 4.);
  BOOST_CHECK_EQUAL(w[1], 10.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w;
  w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w = v2 - cml::hadamard(v1,v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -11.);
  BOOST_CHECK_EQUAL(w[2], -21.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
