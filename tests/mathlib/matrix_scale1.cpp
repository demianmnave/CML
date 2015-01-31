/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/scale.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_scale1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(scale_2D)

BOOST_AUTO_TEST_CASE(set1)
{
  cml::matrix33d M;
  cml::matrix_scale_2D(M, 2., 2.);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
}

BOOST_AUTO_TEST_CASE(set2)
{
  cml::matrix33d M;
  cml::matrix_scale_2D(M, cml::vector2d(2., 2.));
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
}

BOOST_AUTO_TEST_CASE(uniform1)
{
  cml::matrix33d M;
  cml::matrix_uniform_scale_2D(M, 2.);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
}

BOOST_AUTO_TEST_CASE(inverse1)
{
  cml::matrix33d M;
  cml::matrix_inverse_scale_2D(M, .5, .5);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
}

BOOST_AUTO_TEST_CASE(inverse2)
{
  cml::matrix33d M;
  cml::matrix_inverse_scale_2D(M, cml::vector2d(.5, .5));
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(scale_3D)

BOOST_AUTO_TEST_CASE(set1)
{
  cml::matrix44d M;
  cml::matrix_scale(M, 2., 2., 2.);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
  BOOST_CHECK_EQUAL(M(2,2), 2.);
}

BOOST_AUTO_TEST_CASE(set2)
{
  cml::matrix44d M;
  cml::matrix_scale(M, cml::vector3d(2., 2., 2.));
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
  BOOST_CHECK_EQUAL(M(2,2), 2.);
}

BOOST_AUTO_TEST_CASE(uniform1)
{
  cml::matrix44d M;
  cml::matrix_uniform_scale(M, 2.);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
  BOOST_CHECK_EQUAL(M(2,2), 2.);
}

BOOST_AUTO_TEST_CASE(inverse1)
{
  cml::matrix44d M;
  cml::matrix_inverse_scale(M, .5, .5, .5);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
  BOOST_CHECK_EQUAL(M(2,2), 2.);
}

BOOST_AUTO_TEST_CASE(inverse2)
{
  cml::matrix44d M;
  cml::matrix_inverse_scale(M, cml::vector3d(.5, .5, .5));
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(1,1), 2.);
  BOOST_CHECK_EQUAL(M(2,2), 2.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
