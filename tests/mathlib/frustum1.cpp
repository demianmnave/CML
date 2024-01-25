/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/frustum.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include "cml/mathlib/matrix/generators.h"
#include <cml/mathlib/matrix/projection.h>

/* Testing headers: */
#include "catch_runner.h"
#include "cml/mathlib/matrix/rotation.h"
#include "cml/mathlib/matrix/translation.h"
#include "cml/matrix/lu.h"

CATCH_TEST_CASE("orthographic_planes1")
{
  cml::matrix44d O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("orthographic_planes2")
{
  cml::matrix44d O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  cml::matrix44d M = cml::identity_4x4();
  cml::matrix_rotation_world_y(M, cml::rad(180.));

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(M, O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(-1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("orthographic_planes_row1")
{
  cml::matrix44d_r O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("orthographic_planes_row2")
{
  cml::matrix44d_r O;
  cml::matrix_orthographic_RH(
    O, -.5, .5, -.5, .5, -1., 1., cml::z_clip_neg_one);
  // width x height, near, far

  cml::matrix44d_r M = cml::identity_4x4();
  cml::matrix_rotation_world_y(M, cml::rad(180.));

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(M, O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(-1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("perspective_planes1")
{
  cml::matrix44d O;
  cml::matrix_perspective_RH(
    O, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("perspective_planes2")
{
  cml::matrix44d O;
  cml::matrix_perspective_RH(
    O, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  cml::matrix44d M = cml::identity_4x4();
  cml::matrix_rotation_world_y(M, cml::rad(180.));

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(M, O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(-1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("perspective_planes_row1")
{
  cml::matrix44d_r O;
  cml::matrix_perspective_RH(
    O, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(-1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(1.).epsilon(1.5e-8));
}

CATCH_TEST_CASE("perspective_planes_row2")
{
  cml::matrix44d_r O;
  cml::matrix_perspective_RH(
    O, -.5, .5, -.5, .5, .001, 1., cml::z_clip_neg_one);
  // l, r, b, t, near, far

  cml::matrix44d_r M = cml::identity_4x4();
  cml::matrix_rotation_world_y(M, cml::rad(180.));

  double planes[6][4]; // l, r, b, t, n ,f
  cml::extract_frustum_planes(M, O, planes, cml::z_clip_neg_one);

  CATCH_CHECK(planes[0][0] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[1][0] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[2][1] == Approx(.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[3][1] == Approx(-.0019999960).epsilon(1.5e-8));
  CATCH_CHECK(planes[4][2] == Approx(1.).epsilon(1.5e-8));
  CATCH_CHECK(planes[5][2] == Approx(-1.).epsilon(1.5e-8));
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
