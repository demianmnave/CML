/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <type_traits>

// Make sure the main header compiles cleanly:
#include <cml/vector/functions.h>

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_functions1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(length_squared1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  double l2 = v1.length_squared();
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length_squared2)
{
  cml::vector3d v1 = { 1., 1., 1. };
  double l2 = cml::length_squared(v1);
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  double l = v1.length();
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(length2)
{
  cml::vector3d v1 = { 1., 1., 1. };
  double l = cml::length(v1);
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  v1.normalize();
  double l2 = v1.length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize2)
{
  cml::vector3d v1 = { 1., 1., 1. };
  double l2 = cml::normalize(v1).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize3)
{
  BOOST_CHECK_EQUAL(
    (std::is_same<
     decltype(cml::normalize(cml::vector3d())),
     cml::vector3d>::value), true);
  double l2 = cml::normalize(
    cml::vector3d(1., 1., 1.)).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize4)
{
  cml::vector3d v1 = { 1., 1., 1. };
  cml::vector3d v2 = { 1., 1., 1. };
  cml::vector3d v3 = { 1., 1., 1. };
  auto xpr = cml::normalize(v1 + 2.*v2);
  BOOST_CHECK_EQUAL(
    (std::is_same<decltype(xpr), cml::vector3d>::value), true);
  BOOST_CHECK_CLOSE(xpr.length_squared(), 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  v1.zero();
  BOOST_CHECK_EQUAL(v1[0], 0.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
  BOOST_CHECK_EQUAL(v1.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  cml::vector3d v2 = { 2., 0., 3. };
  v1.minimize(v2);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  cml::vector3d v2 = { 2., 0., 3. };
  v1.maximize(v2);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 1.);
  BOOST_CHECK_EQUAL(v1[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  cml::vector3d v1;
  v1.cardinal(0);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
}

BOOST_AUTO_TEST_CASE(random1)
{
  cml::vector4d v1;
  v1.random(0.,1.);
  for(const auto& e : v1) {
    BOOST_CHECK_GE(e, 0.);
    BOOST_CHECK_LT(e, 1.);
  }
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(length_squared1)
{
  double av1[] = { 1., 1., 1. };
  cml::external3d v1(av1);
  double l2 = v1.length_squared();
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length1)
{
  double av1[] = { 1., 1., 1. };
  cml::external3d v1(av1);
  double l = v1.length();
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  double av1[] = { 1., 1., 1. };
  cml::external3d v1(av1);
  double l2 = v1.normalize().length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize2)
{
  double av1[] = { 1., 1., 1. };
  cml::external3d v1(av1);
  double l2 = cml::normalize(v1).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  double av1[] = { 1., 1., 1. };
  cml::external3d v1(av1);
  v1.zero();
  BOOST_CHECK_EQUAL(v1[0], 0.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
  BOOST_CHECK_EQUAL(v1.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  double av1[] = { 1., 1., 1. };
  double av2[] = { 2., 0., 3. };
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  v1.minimize(v2);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  double av1[] = { 1., 1., 1. };
  double av2[] = { 2., 0., 3. };
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  v1.maximize(v2);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 1.);
  BOOST_CHECK_EQUAL(v1[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  double av1[3];
  cml::external3d v1(av1);
  v1.cardinal(0);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
}

BOOST_AUTO_TEST_CASE(random1)
{
  double av1[4];
  cml::external3d v1(av1);
  v1.random(0.,1.);
  for(const auto& e : v1) {
    BOOST_CHECK_GE(e, 0.);
    BOOST_CHECK_LT(e, 1.);
  }
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(length_squared1)
{
  cml::vectord v1 = { 1., 1., 1. };
  double l2 = v1.length_squared();
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length1)
{
  cml::vectord v1 = { 1., 1., 1. };
  double l = v1.length();
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  cml::vectord v1 = { 1., 1., 1. };
  double l2 = v1.normalize().length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize2)
{
  cml::vectord v1 = { 1., 1., 1. };
  double l2 = cml::normalize(v1).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::vectord v1 = { 1., 1., 1. };
  v1.zero();
  BOOST_CHECK_EQUAL(v1[0], 0.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
  BOOST_CHECK_EQUAL(v1.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  cml::vectord v1 = { 1., 1., 1. };
  cml::vectord v2 = { 2., 0., 3. };
  v1.minimize(v2);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  cml::vectord v1 = { 1., 1., 1. };
  cml::vectord v2 = { 2., 0., 3. };
  v1.maximize(v2);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 1.);
  BOOST_CHECK_EQUAL(v1[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  cml::vectord v1(3);
  v1.cardinal(0);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
}

BOOST_AUTO_TEST_CASE(random1)
{
  cml::vectord v1(4);
  v1.random(0.,1.);
  for(const auto& e : v1) {
    BOOST_CHECK_GE(e, 0.);
    BOOST_CHECK_LT(e, 1.);
  }
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(length_squared1)
{
  double av1[] = { 1., 1., 1. };
  cml::externalnd v1(av1, 3);
  double l2 = v1.length_squared();
  BOOST_CHECK_EQUAL(l2, 3.);
}

BOOST_AUTO_TEST_CASE(length1)
{
  double av1[] = { 1., 1., 1. };
  cml::externalnd v1(av1, 3);
  double l = v1.length();
  BOOST_CHECK_CLOSE(l, std::sqrt(3.), 1e-4);
}

BOOST_AUTO_TEST_CASE(normalize1)
{
  double av1[] = { 1., 1., 1. };
  cml::externalnd v1(av1, 3);
  double l2 = v1.normalize().length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(normalize2)
{
  double av1[] = { 1., 1., 1. };
  cml::externalnd v1(av1, 3);
  double l2 = cml::normalize(v1).length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  double av1[] = { 1., 1., 1. };
  cml::externalnd v1(av1, 3);
  v1.zero();
  BOOST_CHECK_EQUAL(v1[0], 0.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
  BOOST_CHECK_EQUAL(v1.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  double av1[] = { 1., 1., 1. };
  double av2[] = { 2., 0., 3. };
  cml::externalnd v1(av1, 3);
  cml::externalnd v2(av2, 3);
  v1.minimize(v2);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  double av1[] = { 1., 1., 1. };
  double av2[] = { 2., 0., 3. };
  cml::externalnd v1(av1, 3);
  cml::externalnd v2(av2, 3);
  v1.maximize(v2);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 1.);
  BOOST_CHECK_EQUAL(v1[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  double av1[3];
  cml::externalnd v1(av1, 3);
  v1.cardinal(0);
  BOOST_CHECK_EQUAL(v1[0], 1.);
  BOOST_CHECK_EQUAL(v1[1], 0.);
  BOOST_CHECK_EQUAL(v1[2], 0.);
}

BOOST_AUTO_TEST_CASE(random1)
{
  double av1[4];
  cml::externalnd v1(av1, 4);
  v1.random(0.,1.);
  for(const auto& e : v1) {
    BOOST_CHECK_GE(e, 0.);
    BOOST_CHECK_LT(e, 1.);
  }
}

BOOST_AUTO_TEST_SUITE_END()


#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
BOOST_AUTO_TEST_SUITE(rv_from_this1)

BOOST_AUTO_TEST_CASE(normalize1)
{
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<decltype(
	cml::vector3d(1., 1., 1.).normalize())>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.).normalize();
  double l2 = xpr.length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<decltype(
	cml::vector3d(1., 1., 1.).zero())>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.).zero();
  BOOST_CHECK_EQUAL(xpr[0], 0.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 0.);
  BOOST_CHECK_EQUAL(xpr.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<decltype(
	cml::vector3d(1., 1., 1.)
	.minimize(cml::vector3d(2., 0., 3.))
	)>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.)
    .minimize(cml::vector3d(2., 0., 3.));
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<decltype(
	cml::vector3d(1., 1., 1.)
	.maximize(cml::vector3d(2., 0., 3.))
	)>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.)
    .maximize(cml::vector3d(2., 0., 3.));
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 1.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<decltype(
	cml::vector3d().cardinal(0))>::value)
    , true);
  auto xpr = cml::vector3d().cardinal(0);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 0.);
}

BOOST_AUTO_TEST_SUITE_END()
#else
BOOST_AUTO_TEST_SUITE(rv_from_this1)

BOOST_AUTO_TEST_CASE(normalize1)
{
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<decltype(
	cml::vector3d(1., 1., 1.).normalize())>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.).normalize();
  BOOST_CHECK_EQUAL((std::is_reference<decltype(xpr)>::value), false);

  double l2 = xpr.length_squared();
  BOOST_CHECK_CLOSE(l2, 1.0, 1e-12);
}

BOOST_AUTO_TEST_CASE(zero1)
{
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<decltype(
	cml::vector3d(1., 1., 1.).zero())>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.).zero();
  BOOST_CHECK_EQUAL((std::is_reference<decltype(xpr)>::value), false);
  BOOST_CHECK_EQUAL(xpr[0], 0.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 0.);
  BOOST_CHECK_EQUAL(xpr.length(), 0.);
}

BOOST_AUTO_TEST_CASE(minimize1)
{
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<decltype(
	cml::vector3d(1., 1., 1.)
	.minimize(cml::vector3d(2., 0., 3.))
	)>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.)
    .minimize(cml::vector3d(2., 0., 3.));
  BOOST_CHECK_EQUAL((std::is_reference<decltype(xpr)>::value), false);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 1.);
}

BOOST_AUTO_TEST_CASE(maximize1)
{
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<decltype(
	cml::vector3d(1., 1., 1.)
	.maximize(cml::vector3d(2., 0., 3.))
	)>::value)
    , true);
  auto xpr = cml::vector3d(1., 1., 1.)
    .maximize(cml::vector3d(2., 0., 3.));
  BOOST_CHECK_EQUAL((std::is_reference<decltype(xpr)>::value), false);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 1.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

BOOST_AUTO_TEST_CASE(cardinal1)
{
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<decltype(
	cml::vector3d().cardinal(0))>::value)
    , true);
  auto xpr = cml::vector3d().cardinal(0);
  BOOST_CHECK_EQUAL((std::is_reference<decltype(xpr)>::value), false);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 0.);
  BOOST_CHECK_EQUAL(xpr[2], 0.);
}

BOOST_AUTO_TEST_SUITE_END()
#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
