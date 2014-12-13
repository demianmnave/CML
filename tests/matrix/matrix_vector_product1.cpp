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

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_vector_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrix<double, cml::fixed<2,2>> M(
    1., 2.,
    3., 4.
    );
  cml::vector<double, cml::fixed<2>> v1(
    5., 6.
    );

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::fixed<2>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrix<double, cml::fixed<2,2>> M(
    1., 2.,
    3., 4.
    );
  cml::vector<double, cml::fixed<2>> v1(
    5., 6.
    );

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::fixed<2>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::matrix<double, cml::external<2,2>> M(aM);

  double av1[] = { 5., 6. };
  cml::vector<double, cml::external<2>> v1(av1);

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::fixed<2>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::matrix<double, cml::external<2,2>> M(aM);

  double av1[] = { 5., 6. };
  cml::vector<double, cml::external<2>> v1(av1);

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::fixed<2>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::matrix<double, cml::external<>> M(aM, 2,2);

  double av1[] = { 5., 6. };
  cml::vector<double, cml::external<>> v1(av1, 2);

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::dynamic<>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM[] = { 1., 2., 3., 4. };
  cml::matrix<double, cml::external<>> M(aM, 2,2);

  double av1[] = { 5., 6. };
  cml::vector<double, cml::external<>> v1(av1, 2);

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::dynamic<>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  double aM1[4], av1[3];
  BOOST_REQUIRE_THROW(
    (cml::matrix<double, cml::external<>>(aM1, 2,2)
     * cml::vector<double, cml::external<>>(av1, 3)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_CASE(size_checking2)
{
  double aM1[4], av1[3];
  BOOST_REQUIRE_THROW(
    (cml::vector<double, cml::external<>>(av1, 3)
     * cml::matrix<double, cml::external<>>(aM1, 2,2)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrix<double, cml::dynamic<>> M(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::vector<double, cml::dynamic<>> v1(
    5., 6.
    );

  auto v = M*v1;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::dynamic<>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 17.);
  BOOST_CHECK_EQUAL(v[1], 39.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrix<double, cml::dynamic<>> M(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::vector<double, cml::dynamic<>> v1(
    5., 6.
    );

  auto v = v1*M;
  BOOST_REQUIRE((std::is_same<
      decltype(v), cml::vector<double, cml::dynamic<>>>::value));
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 23.);
  BOOST_CHECK_EQUAL(v[1], 34.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  BOOST_REQUIRE_THROW(
    (cml::matrix<double, cml::dynamic<>>(2,2)
    * cml::vector<double, cml::dynamic<>>(3)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_CASE(size_checking2)
{
  BOOST_REQUIRE_THROW(
    (cml::vector<double, cml::dynamic<>>(3)
     * cml::matrix<double, cml::dynamic<>>(2,2)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
