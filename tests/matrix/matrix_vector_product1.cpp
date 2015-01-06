/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <typeinfo>
#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/matrix/vector_product.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>
#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>
#include <cml/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_vector_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrix22d M(
    1., 2.,
    3., 4.
    );
  cml::vector2d v1(
    5., 6.
    );

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vector2d>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrix22d M(
    1., 2.,
    3., 4.
    );
  cml::vector2d v1(
    5., 6.
    );

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vector2d>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::external22d M(aM);

  double av1[] = { 5., 6. };
  cml::external2d v1(av1);

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vector2d>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::external22d M(aM);

  double av1[] = { 5., 6. };
  cml::external2d v1(av1);

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vector2d>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::externalmnd M(aM, 2,2);

  double av1[] = { 5., 6. };
  cml::externalnd v1(2, av1);

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vectord>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::externalmnd M(aM, 2,2);

  double av1[] = { 5., 6. };
  cml::externalnd v1(2, av1);

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vectord>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  double aM1[4], av1[3];
  BOOST_REQUIRE_THROW(
    (cml::externalmnd(aM1, 2,2) * cml::externalnd(3, av1)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_CASE(size_checking2)
{
  double aM1[4], av1[3];
  BOOST_REQUIRE_THROW(
    (cml::externalnd(3, av1) * cml::externalmnd(2,2, aM1)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrixd M(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::vectord v1(
    5., 6.
    );

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vectord>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrixd M(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::vectord v1(
    5., 6.
    );

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<decltype(v), cml::vectord>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  BOOST_REQUIRE_THROW(
    (cml::matrixd(2,2) * cml::vectord(3)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_CASE(size_checking2)
{
  BOOST_REQUIRE_THROW(
    (cml::vectord(3) * cml::matrixd(2,2)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
