/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/frustum.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/mathlib/matrix/projection.h>

/* Testing headers: */
#define BOOST_TEST_MODULE frustum1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(orthographic_planes1)
{
  cml::matrix44d O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  BOOST_CHECK_CLOSE(planes[0][0], 1., .001);
  BOOST_CHECK_CLOSE(planes[1][0], -1., .001);
  BOOST_CHECK_CLOSE(planes[2][1], 1., .001);
  BOOST_CHECK_CLOSE(planes[3][1], -1., .001);
  BOOST_CHECK_CLOSE(planes[4][2], -1., .001);
  BOOST_CHECK_CLOSE(planes[5][2], 1., .001);
}

BOOST_AUTO_TEST_CASE(perspective_planes1)
{
  cml::matrix44d O;
  cml::matrix_perspective_RH(
    O, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  BOOST_CHECK_CLOSE(planes[0][0], .002, .001);
  BOOST_CHECK_CLOSE(planes[1][0], -.002, .001);
  BOOST_CHECK_CLOSE(planes[2][1], .002, .001);
  BOOST_CHECK_CLOSE(planes[3][1], -.002, .001);
  BOOST_CHECK_CLOSE(planes[4][2], -1., .001);
  BOOST_CHECK_CLOSE(planes[5][2], 1., .001);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
