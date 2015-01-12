/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/outer_product.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/util/vector_print.h>
#include <cml/util/matrix_print.h>

/* Testing headers: */
#define BOOST_TEST_MODULE outer_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(outer1)
{
  auto v = cml::vector3d(1., 2., 3.);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto expected = cml::matrix33d(
    1., 2., 3.,
    2., 4., 6.,
    3., 6., 9.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(C(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(outer1)
{
  double av[] = { 1., 2., 3. };
  auto v = cml::external3d(av);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto expected = cml::matrix33d(
    1., 2., 3.,
    2., 4., 6.,
    3., 6., 9.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(C(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(outer1)
{
  double av[] = { 1., 2., 3. };
  auto v = cml::externalnd(3, av);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto expected = cml::matrix33d(
    1., 2., 3.,
    2., 4., 6.,
    3., 6., 9.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(C(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(outer1)
{
  auto v = cml::vectord(1., 2., 3.);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto expected = cml::matrix33d(
    1., 2., 3.,
    2., 4., 6.,
    3., 6., 9.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(C(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
