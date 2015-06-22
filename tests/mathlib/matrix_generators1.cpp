/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/generators.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_transform1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(zero)

BOOST_AUTO_TEST_CASE(zero_2x2_1)
{
  auto M = cml::zero_2x2();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 2);
  BOOST_CHECK_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 0.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 0.);
}

BOOST_AUTO_TEST_CASE(zero_3x3_1)
{
  auto M = cml::zero_3x3();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 3);
  BOOST_CHECK_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 0.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(0,2), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 0.);
  BOOST_CHECK_EQUAL(M(1,2), 0.);
  BOOST_CHECK_EQUAL(M(2,0), 0.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
}

BOOST_AUTO_TEST_CASE(zero_4x4_1)
{
  auto M = cml::zero_4x4();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 4);
  BOOST_CHECK_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M(0,0), 0.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(0,2), 0.);
  BOOST_CHECK_EQUAL(M(0,3), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 0.);
  BOOST_CHECK_EQUAL(M(1,2), 0.);
  BOOST_CHECK_EQUAL(M(1,3), 0.);
  BOOST_CHECK_EQUAL(M(2,0), 0.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
  BOOST_CHECK_EQUAL(M(3,0), 0.);
  BOOST_CHECK_EQUAL(M(3,1), 0.);
  BOOST_CHECK_EQUAL(M(3,2), 0.);
  BOOST_CHECK_EQUAL(M(3,3), 0.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(zero)

BOOST_AUTO_TEST_CASE(identity_2x2_1)
{
  auto M = cml::identity_2x2();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 2);
  BOOST_CHECK_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 1.);
}

BOOST_AUTO_TEST_CASE(identity_3x3_1)
{
  auto M = cml::identity_3x3();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 3);
  BOOST_CHECK_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(0,2), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 1.);
  BOOST_CHECK_EQUAL(M(1,2), 0.);
  BOOST_CHECK_EQUAL(M(2,0), 0.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 1.);
}

BOOST_AUTO_TEST_CASE(identity_4x4_1)
{
  auto M = cml::identity_4x4();
  typedef decltype(M) matrix_type;
  BOOST_CHECK((std::is_same<double, matrix_type::value_type>::value));
  BOOST_CHECK_EQUAL(M.rows(), 4);
  BOOST_CHECK_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(0,2), 0.);
  BOOST_CHECK_EQUAL(M(0,3), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 1.);
  BOOST_CHECK_EQUAL(M(1,2), 0.);
  BOOST_CHECK_EQUAL(M(1,3), 0.);
  BOOST_CHECK_EQUAL(M(2,0), 0.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 1.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
  BOOST_CHECK_EQUAL(M(3,0), 0.);
  BOOST_CHECK_EQUAL(M(3,1), 0.);
  BOOST_CHECK_EQUAL(M(3,2), 0.);
  BOOST_CHECK_EQUAL(M(3,3), 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
