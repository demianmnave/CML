/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/vector/transform.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_transform1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(transform_3D)

BOOST_AUTO_TEST_CASE(transform1)
{
  auto v = cml::vector3d(1., 0., 0.);
  auto M = cml::matrix33d(
    1., 0., 0.,
    0., 1., 0.,
    0., 0., 1.);
  auto w = cml::transform_vector(M,v);
  BOOST_CHECK_CLOSE(w[0], 1., .0001);
  BOOST_CHECK_SMALL(w[1], 1e-7);
  BOOST_CHECK_SMALL(w[2], 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
