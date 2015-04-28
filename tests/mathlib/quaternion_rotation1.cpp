/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/quaternion/rotation.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/quaternion.h>
#include <cml/mathlib/matrix/rotation.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_rotation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(world_axis1)
{
  cml::quaterniond qx; cml::quaternion_rotation_world_x(qx, M_PI/3.);
  BOOST_CHECK_CLOSE(qx.real(), 0.86602540378443871, .001);
  BOOST_CHECK_CLOSE(qx.imaginary()[0], 0.49999999999999994, .001);
  BOOST_CHECK_EQUAL(qx.imaginary()[1], 0.);
  BOOST_CHECK_EQUAL(qx.imaginary()[2], 0.);

  cml::quaterniond qy; cml::quaternion_rotation_world_y(qy, M_PI/2.);
  BOOST_CHECK_CLOSE(qy.real(), 0.70710678118654757, .001);
  BOOST_CHECK_EQUAL(qy.imaginary()[0], 0.);
  BOOST_CHECK_CLOSE(qy.imaginary()[1], 0.70710678118654757, .001);
  BOOST_CHECK_EQUAL(qy.imaginary()[2], 0.);

  cml::quaterniond qz; cml::quaternion_rotation_world_z(qz, M_PI);
  BOOST_CHECK_SMALL(qz.real(), 2e-16);
  BOOST_CHECK_EQUAL(qz.imaginary()[0], 0.);
  BOOST_CHECK_EQUAL(qz.imaginary()[1], 0.);
  BOOST_CHECK_CLOSE(qz.imaginary()[2], 1., .001);
}

BOOST_AUTO_TEST_CASE(axis_angle1)
{
  cml::quaterniond q; cml::quaternion_rotation_axis_angle(
    q, cml::vector3d(1.,1.,1.).normalize(), M_PI/3.);
  BOOST_CHECK_CLOSE(q.real(), 0.86602540378443871, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[0], 0.28867513459481287, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[1], 0.28867513459481287, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[2], 0.28867513459481287, .001);
}

BOOST_AUTO_TEST_CASE(matrix1)
{
  cml::matrix33d M; cml::matrix_rotation_axis_angle(
    M, cml::vector3d(1.,1.,1.).normalize(), M_PI/3.);
  cml::quaterniond q; cml::quaternion_rotation_matrix(q, M);

  BOOST_CHECK_CLOSE(q.real(), 0.86602540378443871, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[0], 0.28867513459481287, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[1], 0.28867513459481287, .001);
  BOOST_CHECK_CLOSE(q.imaginary()[2], 0.28867513459481287, .001);
}

BOOST_AUTO_TEST_CASE(align_ref1)
{
  cml::quaterniond q; cml::quaternion_rotation_align(
    q, cml::vector3d(0., 0., 1.), cml::vector3d(1., 0., 0.));
  cml::matrix33d M; cml::matrix_rotation_quaternion(M, q);
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_CLOSE(v[0], 1., .0001);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_SMALL(v[2], 1e-7);
}

BOOST_AUTO_TEST_CASE(aim_at_ref1)
{
  cml::quaterniond q; cml::quaternion_rotation_aim_at(
    q, cml::vector3d(0.,0.,0.), cml::vector3d(0., 0., 1.),
    cml::vector3d(1., 0., 0.));
  cml::matrix33d M; cml::matrix_rotation_quaternion(M, q);
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_CLOSE(v[0], 1., .0001);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_SMALL(v[2], 1e-7);
}

BOOST_AUTO_TEST_CASE(euler1)
{
  cml::quaterniond q; cml::quaternion_rotation_euler(
    q, cml::rad(90.), 0., 0., cml::euler_order_xyz);
  cml::matrix33d M; cml::matrix_rotation_quaternion(M, q);
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
