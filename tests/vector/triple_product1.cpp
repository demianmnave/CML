/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/triple_product.h>

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE triple_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(triple_product1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> v2 = { 4., 5., 6. };
  double a3[3] = { 7., 8., 9. };
  cml::vector<double, cml::external<3>> v3(a3);
  double tp = cml::triple_product(v1,v2,v3);
  BOOST_CHECK_EQUAL(tp, 0.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vector<double, cml::dynamic<>> v1 = { 1., 2. };
  cml::vector<double, cml::dynamic<>> v2 = { 4., 5., 6. };
  double a3[3] = { 7., 8., 9. };
  cml::vector<double, cml::external<3>> v3(a3);
  BOOST_CHECK_THROW(cml::triple_product(v1,v2,v3), cml::vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
