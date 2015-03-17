/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/quaternion/basis.h>

#include <cml/vector.h>
#include <cml/quaternion.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_basis1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ip1)
{
  auto q = cml::quaterniond_ip(1., 2., 3., 4.).normalize();
  auto qx = cml::quaternion_get_x_basis_vector(q);
  BOOST_CHECK_CLOSE(qx[0], 0.13333333333333353, .001);
  BOOST_CHECK_CLOSE(qx[1], 0.93333333333333324, .001);
  BOOST_CHECK_CLOSE(qx[2], -0.3333333333333332, .001);

  auto qy = cml::quaternion_get_y_basis_vector(q);
  BOOST_CHECK_CLOSE(qy[0], -0.6666666666666666, .001);
  BOOST_CHECK_CLOSE(qy[1], 0.33333333333333348, .001);
  BOOST_CHECK_CLOSE(qy[2], 0.66666666666666652, .001);

  auto qz = cml::quaternion_get_z_basis_vector(q);
  BOOST_CHECK_CLOSE(qz[0], 0.73333333333333317, .001);
  BOOST_CHECK_CLOSE(qz[1], 0.13333333333333336, .001);
  BOOST_CHECK_CLOSE(qz[2], 0.66666666666666674, .001);
}

BOOST_AUTO_TEST_CASE(rp1)
{
  auto q = cml::quaterniond_rp(4., 1., 2., 3.).normalize();
  auto qx = cml::quaternion_get_x_basis_vector(q);
  BOOST_CHECK_CLOSE(qx[0], 0.13333333333333353, .001);
  BOOST_CHECK_CLOSE(qx[1], 0.93333333333333324, .001);
  BOOST_CHECK_CLOSE(qx[2], -0.3333333333333332, .001);

  auto qy = cml::quaternion_get_y_basis_vector(q);
  BOOST_CHECK_CLOSE(qy[0], -0.6666666666666666, .001);
  BOOST_CHECK_CLOSE(qy[1], 0.33333333333333348, .001);
  BOOST_CHECK_CLOSE(qy[2], 0.66666666666666652, .001);

  auto qz = cml::quaternion_get_z_basis_vector(q);
  BOOST_CHECK_CLOSE(qz[0], 0.73333333333333317, .001);
  BOOST_CHECK_CLOSE(qz[1], 0.13333333333333336, .001);
  BOOST_CHECK_CLOSE(qz[2], 0.66666666666666674, .001);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
