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

BOOST_AUTO_TEST_SUITE(transform_2D)

BOOST_AUTO_TEST_CASE(vector1)
{
  auto v = cml::vector2d(1., 1.);
  auto M = cml::matrix22d(
    1., 2.,
    0., 1.);
  auto w = cml::transform_vector_2D(M,v);
  BOOST_CHECK_CLOSE(w[0], 3., .0001);
  BOOST_CHECK_CLOSE(w[1], 1., .0001);
}

BOOST_AUTO_TEST_CASE(vector2)
{
  auto v = cml::vector2d(1., 1.);
  auto M = cml::matrix22d_r(
    1., 2.,
    0., 1.);
  auto w = cml::transform_vector_2D(M,v);
  BOOST_CHECK_CLOSE(w[0], 1., .0001);
  BOOST_CHECK_CLOSE(w[1], 3., .0001);
}

BOOST_AUTO_TEST_CASE(point1)
{
  auto p = cml::vector2d(2., 2.);
  auto M = cml::matrix33d(
    1., 0., 1.,
    0., 1., 0.,
    0., 0., 2.
    );
  auto q = cml::transform_point_2D(M,p);
  BOOST_CHECK_CLOSE(q[0], 3., .0001);
  BOOST_CHECK_CLOSE(q[1], 2., .0001);
}

BOOST_AUTO_TEST_CASE(point2)
{
  auto p = cml::vector2d(2., 2.);
  auto M = cml::matrix33d_r(
    1., 0., 0.,
    0., 1., 0.,
    1., 0., 2.
    );
  auto q = cml::transform_point_2D(M,p);
  BOOST_CHECK_CLOSE(q[0], 3., .0001);
  BOOST_CHECK_CLOSE(q[1], 2., .0001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(transform_3D)

BOOST_AUTO_TEST_CASE(vector1)
{
  auto v = cml::vector3d(1., 1., 1.);
  auto M = cml::matrix33d(
    1., 0., 2.,
    0., 1., 0.,
    0., 0., 1.);
  auto w = cml::transform_vector(M,v);
  BOOST_CHECK_CLOSE(w[0], 3., .0001);
  BOOST_CHECK_CLOSE(w[1], 1., .0001);
  BOOST_CHECK_CLOSE(w[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(vector2)
{
  auto v = cml::vector3d(1., 1., 1.);
  auto M = cml::matrix33d_r(
    1., 0., 2.,
    0., 1., 0.,
    0., 0., 1.);
  auto w = cml::transform_vector(M,v);
  BOOST_CHECK_CLOSE(w[0], 1., .0001);
  BOOST_CHECK_CLOSE(w[1], 1., .0001);
  BOOST_CHECK_CLOSE(w[2], 3., .0001);
}

BOOST_AUTO_TEST_CASE(point1)
{
  auto p = cml::vector3d(2., 2., 2.);
  auto M = cml::matrix44d(
    1., 0., 0., 1.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 2.
    );
  auto q = cml::transform_point(M,p);
  BOOST_CHECK_CLOSE(q[0], 3., .0001);
  BOOST_CHECK_CLOSE(q[1], 2., .0001);
  BOOST_CHECK_CLOSE(q[2], 2., .0001);
}

BOOST_AUTO_TEST_CASE(point2)
{
  auto p = cml::vector3d(2., 2., 2.);
  auto M = cml::matrix44d_r(
    1., 0., 0., 0.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    1., 0., 0., 2.
    );
  auto q = cml::transform_point(M,p);
  BOOST_CHECK_CLOSE(q[0], 3., .0001);
  BOOST_CHECK_CLOSE(q[1], 2., .0001);
  BOOST_CHECK_CLOSE(q[2], 2., .0001);
}

BOOST_AUTO_TEST_CASE(hvector1)
{
  auto v = cml::vector4d(1., 1., 1., 0.);
  auto M = cml::matrix44d(
    1., 2., 3., 4.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 1.
    );
  auto w = cml::transform_vector_4D(M,v);
  BOOST_CHECK_CLOSE(w[0], 6., .0001);
  BOOST_CHECK_EQUAL(w[1], 1.);
  BOOST_CHECK_EQUAL(w[2], 1.);
  BOOST_CHECK_EQUAL(w[3], 0.);
}

BOOST_AUTO_TEST_CASE(hvector2)
{
  auto v = cml::vector4d(1., 1., 1., 0.);
  auto M = cml::matrix44d_r(
    1., 2., 3., 4.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 1.
    );
  auto w = cml::transform_vector_4D(M,v);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_CLOSE(w[1], 3., .0001);
  BOOST_CHECK_CLOSE(w[2], 4., .0001);
  BOOST_CHECK_CLOSE(w[3], 4., .0001);
}

BOOST_AUTO_TEST_CASE(hpoint1)
{
  auto p = cml::vector3d(2., 2., 2.);
  auto M = cml::matrix44d(
    1., 0., 0., 1.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 2.
    );
  auto q = cml::transform_point_4D(M,p);
  BOOST_CHECK_CLOSE(q[0], 1.5, .0001);
  BOOST_CHECK_CLOSE(q[1], 1., .0001);
  BOOST_CHECK_CLOSE(q[2], 1., .0001);
}

BOOST_AUTO_TEST_CASE(hpoint2)
{
  auto p = cml::vector3d(2., 2., 2.);
  auto M = cml::matrix44d_r(
    1., 0., 0., 1.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 2.
    );
  auto q = cml::transform_point_4D(M,p);
  BOOST_CHECK_CLOSE(q[0], .5, .0001);
  BOOST_CHECK_CLOSE(q[1], .5, .0001);
  BOOST_CHECK_CLOSE(q[2], .5, .0001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
