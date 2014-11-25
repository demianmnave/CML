/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
//#include <cml/matrix/functions.h>

#include <cml/vector/fixed.h>
#include <cml/matrix/fixed.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_functions1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

typedef cml::matrix<
	double, cml::fixed<3,4>, cml::row_basis, cml::row_major> matrix34d_r;
typedef cml::matrix<
	double, cml::fixed<3,4>, cml::col_basis, cml::col_major> matrix34d_c;

BOOST_AUTO_TEST_CASE(zero1)
{
  cml::matrix<double, cml::fixed<2,2>> M;
  M.zero();
  BOOST_CHECK_EQUAL(M(0,0), 0.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 0.);
}

BOOST_AUTO_TEST_CASE(identity1)
{
  cml::matrix<double, cml::fixed<2,2>> M;
  M.identity();
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 0.);
  BOOST_CHECK_EQUAL(M(1,0), 0.);
  BOOST_CHECK_EQUAL(M(1,1), 1.);
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

BOOST_AUTO_TEST_CASE(set_basis_element1)
{
  matrix34d_c M;
  M.set_basis_element(0, 0, 1.);
  M.set_basis_element(0, 1, 2.);
  M.set_basis_element(0, 2, 3.);

  BOOST_CHECK_EQUAL(M.basis_element(0,0), 1.);
  BOOST_CHECK_EQUAL(M.basis_element(0,1), 2.);
  BOOST_CHECK_EQUAL(M.basis_element(0,2), 3.);

  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(1,0), 2.);
  BOOST_CHECK_EQUAL(M(2,0), 3.);
}

BOOST_AUTO_TEST_CASE(set_basis_element2)
{
  matrix34d_r M;
  M.set_basis_element(0, 0, 1.);
  M.set_basis_element(0, 1, 2.);
  M.set_basis_element(0, 2, 3.);
  M.set_basis_element(0, 3, 4.);

  BOOST_CHECK_EQUAL(M.basis_element(0,0), 1.);
  BOOST_CHECK_EQUAL(M.basis_element(0,1), 2.);
  BOOST_CHECK_EQUAL(M.basis_element(0,2), 3.);
  BOOST_CHECK_EQUAL(M.basis_element(0,3), 4.);

  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(0,2), 3.);
  BOOST_CHECK_EQUAL(M(0,3), 4.);
}

BOOST_AUTO_TEST_CASE(set_row1)
{
  typedef cml::vector<double, cml::fixed<3>> vector3d;
  cml::matrix<double, cml::fixed<3,3>> M;
  M.set_row(0, vector3d(1., 2., 3.));
  M.set_row(1, vector3d(4., 5., 6.));
  M.set_row(2, vector3d(7., 8., 9.));
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 3.);
  BOOST_CHECK_EQUAL(M(2,0), 7.);
}

BOOST_AUTO_TEST_CASE(set_col1)
{
  typedef cml::vector<double, cml::fixed<3>> vector3d;
  cml::matrix<double, cml::fixed<3,3>> M;
  M.set_col(0, vector3d(1., 4., 7.));
  M.set_col(1, vector3d(2., 5., 8.));
  M.set_col(2, vector3d(3., 6., 9.));
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 3.);
  BOOST_CHECK_EQUAL(M(2,0), 7.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
