/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/rotation.h>

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/quaternion.h>
#include <cml/mathlib/quaternion/rotation.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_rotation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(rotation_2D)

BOOST_AUTO_TEST_CASE(rotation1)
{
  cml::matrix22d M;
  cml::matrix_rotation_2D(M, cml::rad(90.));
  auto v = M*cml::vector2d(0., 1.);
  BOOST_CHECK_CLOSE(v[0], -1., .0001);
  BOOST_CHECK_SMALL(v[1], 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(rotation_3D)

BOOST_AUTO_TEST_CASE(world_axis1)
{
  cml::matrix33d Mx; cml::matrix_rotation_world_x(Mx, cml::rad(90.));
  auto vx = Mx*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(vx[0], 1e-7);
  BOOST_CHECK_SMALL(vx[1], 1e-7);
  BOOST_CHECK_CLOSE(vx[2], 1., .0001);

  cml::matrix33d My; cml::matrix_rotation_world_y(My, cml::rad(90.));
  auto vy = My*cml::vector3d(-1., 0., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(vy[0], 1e-7);
  BOOST_CHECK_SMALL(vy[1], 1e-7);
  BOOST_CHECK_CLOSE(vy[2], 1., .0001);

  cml::matrix33d Mz; cml::matrix_rotation_world_z(Mz, cml::rad(90.));
  auto vz = Mz*cml::vector3d(1., 0., 0.);	// 0,1,0
  BOOST_CHECK_SMALL(vz[0], 1e-7);
  BOOST_CHECK_CLOSE(vz[1], 1., .0001);
  BOOST_CHECK_SMALL(vz[2], 1e-7);
}

BOOST_AUTO_TEST_CASE(rotation1)
{
  cml::matrix33d M;
  cml::matrix_rotation_axis_angle(
    M, cml::vector3d(1., 0., 0.), cml::rad(90.));
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(euler1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(90.), 0., 0., cml::euler_order_xyz);

  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(euler_derivaties1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler_derivatives(
    M, 0, cml::rad(90.), 0., 0., cml::euler_order_xyz);

  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_CLOSE(v[1], -1., .0001);
  BOOST_CHECK_SMALL(v[2], 1e-7);
}

BOOST_AUTO_TEST_CASE(quaternion1)
{
  cml::quaterniond q; cml::quaternion_rotation_axis_angle(
    q, cml::vector3d(1., 0., 0.), cml::rad(90.));
  cml::matrix33d M; cml::matrix_rotation_quaternion(M, q);
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_SMALL(v[0], 1e-7);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_CLOSE(v[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(align_ref1)
{
  cml::matrix33d M; cml::matrix_rotation_align(
    M, cml::vector3d(0., 0., 1.), cml::vector3d(1., 0., 0.));
  auto v = M*cml::vector3d(0., 1., 0.);	// 0,0,1
  BOOST_CHECK_CLOSE(v[0], 1., .0001);
  BOOST_CHECK_SMALL(v[1], 1e-7);
  BOOST_CHECK_SMALL(v[2], 1e-7);
}

BOOST_AUTO_TEST_CASE(to_axis_angle1)
{
  cml::matrix33d M;
  cml::matrix_rotation_axis_angle(
    M, cml::vector3d(1., 2., 3.).normalize(), cml::rad(23.));

  cml::vector3d axis;
  double angle;
  cml::matrix_to_axis_angle(M, axis, angle);

  BOOST_CHECK_CLOSE(axis[0], 0.2672612419124244, .01);
  BOOST_CHECK_CLOSE(axis[1], 0.53452248382484879, .01);
  BOOST_CHECK_CLOSE(axis[2], 0.80178372573727308, .01);
}

BOOST_AUTO_TEST_CASE(to_euler1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(22.), cml::rad(10.), cml::rad(89.9), cml::euler_order_xyz);

  cml::vector3d v;
  cml::matrix_to_euler(M, v[0], v[1], v[2], cml::euler_order_xyz);

  BOOST_CHECK_CLOSE(v[0], cml::rad(22.), .01);
  BOOST_CHECK_CLOSE(v[1], cml::rad(10.), .01);
  BOOST_CHECK_CLOSE(v[2], cml::rad(89.9), .01);
}

BOOST_AUTO_TEST_CASE(to_euler2)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(22.), cml::rad(10.), cml::rad(89.9), cml::euler_order_xyx);

  cml::vector3d v;
  cml::matrix_to_euler(M, v[0], v[1], v[2], cml::euler_order_xyx);

  BOOST_CHECK_CLOSE(v[0], cml::rad(22.), .01);
  BOOST_CHECK_CLOSE(v[1], cml::rad(10.), .01);
  BOOST_CHECK_CLOSE(v[2], cml::rad(89.9), .01);
}

BOOST_AUTO_TEST_CASE(to_euler_vector1)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(22.), cml::rad(10.), cml::rad(89.9), cml::euler_order_xyz);

  auto v = cml::matrix_to_euler(M, cml::euler_order_xyz);
  BOOST_CHECK_CLOSE(v[0], cml::rad(22.), .01);
  BOOST_CHECK_CLOSE(v[1], cml::rad(10.), .01);
  BOOST_CHECK_CLOSE(v[2], cml::rad(89.9), .01);
}

BOOST_AUTO_TEST_CASE(to_euler_vector2)
{
  cml::matrix33d M;
  cml::matrix_rotation_euler(
    M, cml::rad(22.), cml::rad(10.), cml::rad(89.9), cml::euler_order_xyz);

  auto v = cml::matrix_to_euler<cml::vectord>(M, cml::euler_order_xyz);
  BOOST_CHECK_CLOSE(v[0], cml::rad(22.), .01);
  BOOST_CHECK_CLOSE(v[1], cml::rad(10.), .01);
  BOOST_CHECK_CLOSE(v[2], cml::rad(89.9), .01);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
