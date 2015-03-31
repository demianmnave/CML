/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/invert.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_invert1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(invert_2D)

BOOST_AUTO_TEST_CASE(invert_2D_1)
{
  auto M = cml::matrix33d(
    1., 0., 3.,
    0., 1., 2.,
    0., 0., 1.
    );
  cml::matrix_invert_RT_only_2D(M);
  BOOST_CHECK_EQUAL(M.basis_element(2,0), -3.);
  BOOST_CHECK_EQUAL(M.basis_element(2,1), -2.);
}

BOOST_AUTO_TEST_CASE(invert_nD_1)
{
  auto M = cml::matrix33d_r(
    1., 0., 0.,
    0., 1., 0.,
    3., 2., 1.
    );
  cml::matrix_invert_RT(M);
  BOOST_CHECK_EQUAL(M.basis_element(2,0), -3.);
  BOOST_CHECK_EQUAL(M.basis_element(2,1), -2.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(invert_3D)

BOOST_AUTO_TEST_CASE(invert_3D_1)
{
  auto M = cml::matrix44d(
    1., 0., 0., 3.,
    0., 1., 0., 2.,
    0., 0., 1., 1.,
    0., 0., 0., 1.
    );
  cml::matrix_invert_RT_only(M);
  BOOST_CHECK_EQUAL(M.basis_element(3,0), -3.);
  BOOST_CHECK_EQUAL(M.basis_element(3,1), -2.);
  BOOST_CHECK_EQUAL(M.basis_element(3,2), -1.);
}

BOOST_AUTO_TEST_CASE(invert_3D_2)
{
  auto M = cml::matrix44d_c(
    1., 0., 0., 3.,
    0., 1., 0., 2.,
    0., 0., 1., 1.,
    0., 0., 0., 1.
    );
  cml::matrix_invert_RT_only(M);
  BOOST_CHECK_EQUAL(M.basis_element(3,0), -3.);
  BOOST_CHECK_EQUAL(M.basis_element(3,1), -2.);
  BOOST_CHECK_EQUAL(M.basis_element(3,2), -1.);
}

BOOST_AUTO_TEST_CASE(invert_nD_1)
{
  auto M = cml::matrix44d_r(
    1., 0., 0., 0.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    3., 2., 1., 1.
    );
  cml::matrix_invert_RT(M);
  BOOST_CHECK_EQUAL(M.basis_element(3,0), -3.);
  BOOST_CHECK_EQUAL(M.basis_element(3,1), -2.);
  BOOST_CHECK_EQUAL(M.basis_element(3,2), -1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
