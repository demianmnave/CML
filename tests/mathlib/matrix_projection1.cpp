/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/projection.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_projection1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(orthographic)

BOOST_AUTO_TEST_CASE(rh1)
{
  cml::matrix44d O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  cml::vector4d o = O * cml::vector4d(.5, .5, 0., 1.);
  BOOST_CHECK_CLOSE(o[0], 1., .001);
  BOOST_CHECK_CLOSE(o[1], 1., .001);
  BOOST_CHECK_SMALL(o[2], 1e-7);
  BOOST_CHECK_CLOSE(o[3], 1., .001);
}

BOOST_AUTO_TEST_CASE(rh2)
{
  cml::matrix44d O;
  cml::matrix_orthographic_RH(O, 1., 1., -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  cml::vector4d o = O * cml::vector4d(.5, .5, 0., 1.);
  BOOST_CHECK_CLOSE(o[0], 1., .001);
  BOOST_CHECK_CLOSE(o[1], 1., .001);
  BOOST_CHECK_SMALL(o[2], 1e-7);
  BOOST_CHECK_CLOSE(o[3], 1., .001);
}

BOOST_AUTO_TEST_CASE(lh1)
{
  cml::matrix44d O;
  cml::matrix_orthographic_LH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_zero);
  // l, r, b, t, near, far

  cml::vector4d o = O * cml::vector4d(.5, .5, 0., 1.);
  BOOST_CHECK_CLOSE(o[0], 1., .001);
  BOOST_CHECK_CLOSE(o[1], 1., .001);
  BOOST_CHECK_CLOSE(o[2], .5, .001);
  BOOST_CHECK_CLOSE(o[3], 1., .001);
}

BOOST_AUTO_TEST_CASE(lh2)
{
  cml::matrix44d O;
  cml::matrix_orthographic_LH(O, 1., 1., -1., 1., cml::z_clip_zero);
  // width x height, near, far

  cml::vector4d o = O * cml::vector4d(.5, .5, 0., 1.);
  BOOST_CHECK_CLOSE(o[0], 1., .001);
  BOOST_CHECK_CLOSE(o[1], 1., .001);
  BOOST_CHECK_CLOSE(o[2], .5, .001);
  BOOST_CHECK_CLOSE(o[3], 1., .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(perspective)

BOOST_AUTO_TEST_CASE(rh1)
{
  cml::matrix44d P;
  cml::matrix_perspective_RH(
    P, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  cml::vector4d p = P * cml::vector4d(.5, .5, 1., 1.);
  BOOST_CHECK_CLOSE(p[0], .001, .001);
  BOOST_CHECK_CLOSE(p[1], .001, .001);
  BOOST_CHECK_CLOSE(p[2], -1.004, .001);
  BOOST_CHECK_CLOSE(p[3], -1., .001);
}

BOOST_AUTO_TEST_CASE(rh2)
{
  cml::matrix44d P;
  cml::matrix_perspective_RH(P, 1., 1., .001, 1., cml::z_clip_neg_one);
  // width x height, near, far

  cml::vector4d p = P * cml::vector4d(.5, .5, 1., 1.);
  BOOST_CHECK_CLOSE(p[0], .001, .001);
  BOOST_CHECK_CLOSE(p[1], .001, .001);
  BOOST_CHECK_CLOSE(p[2], -1.004, .001);
  BOOST_CHECK_CLOSE(p[3], -1., .001);
}

BOOST_AUTO_TEST_CASE(lh1)
{
  cml::matrix44d P;
  cml::matrix_perspective_LH(
    P, -.5, .5, -.5, .5, .001, 1., cml::z_clip_zero);
  // l, r, b, t, near, far

  cml::vector4d p = P * cml::vector4d(.5, .5, 1., 1.);
  BOOST_CHECK_CLOSE(p[0], .001, .001);
  BOOST_CHECK_CLOSE(p[1], .001, .001);
  BOOST_CHECK_CLOSE(p[2], 1., .001);
  BOOST_CHECK_CLOSE(p[3], 1., .001);
}

BOOST_AUTO_TEST_CASE(lh2)
{
  cml::matrix44d P;
  cml::matrix_perspective_LH(P, 1., 1., .001, 1., cml::z_clip_zero);
  // width x height, near, far

  cml::vector4d p = P * cml::vector4d(.5, .5, 1., 1.);
  BOOST_CHECK_CLOSE(p[0], .001, .001);
  BOOST_CHECK_CLOSE(p[1], .001, .001);
  BOOST_CHECK_CLOSE(p[2], 1., .001);
  BOOST_CHECK_CLOSE(p[3], 1., .001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
