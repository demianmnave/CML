/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
//#include <cml/matrix/functions.h>

#include <cml/matrix/fixed.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_functions1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::matrix<double, cml::fixed<2,2>> M;
  M.zero();
  BOOST_CHECK_EQUAL(M(0,0), 0.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 0.);
}

BOOST_AUTO_TEST_CASE(random1)
{
  cml::matrix<double, cml::fixed<2,2>> M;
  M.random(0.,1.);
  for(const auto& v : M) {
    BOOST_CHECK_GE(v, 0.);
    BOOST_CHECK_LT(v, 1.);
  }
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
