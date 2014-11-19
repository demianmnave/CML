/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/unary_ops.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_unary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M;
  M = - M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M = - M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M;
  M = + M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M = + M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M;
  auto xpr = - (-M1);
  M = xpr;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double data[2][2];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = - M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double data[2][2];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = + M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double data[2][2];
  cml::matrix<double, cml::external<2,2>> M(data);

  auto xpr = - (-M1);
  M = xpr;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = - M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = + M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);

  auto xpr = - (-M1);
  M = xpr;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M;
  M = - M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M = - M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -1.);
  BOOST_CHECK_EQUAL(M(0,1), -2.);
  BOOST_CHECK_EQUAL(M(1,0), -3.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M;
  M = + M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M = + M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M;
  auto xpr = - (-M1);
  M = xpr;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
