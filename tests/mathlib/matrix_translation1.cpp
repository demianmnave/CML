/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/translation.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_translation1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(set_2D)

BOOST_AUTO_TEST_CASE(set1)
{
  cml::matrix33d M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);
  BOOST_CHECK_EQUAL(M(0,2), 2.);
  BOOST_CHECK_EQUAL(M(1,2), -3.);
}

BOOST_AUTO_TEST_CASE(set2)
{
  cml::matrix33d_r M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);
  BOOST_CHECK_EQUAL(M(2,0), 2.);
  BOOST_CHECK_EQUAL(M(2,1), -3.);
}

BOOST_AUTO_TEST_CASE(set3)
{
  cml::matrix33d M;
  cml::matrix_set_translation_2D(M.identity(), cml::vector2d(2.,-3.));
  BOOST_CHECK_EQUAL(M(0,2), 2.);
  BOOST_CHECK_EQUAL(M(1,2), -3.);
}

BOOST_AUTO_TEST_CASE(set4)
{
  cml::matrix33d_r M;
  cml::matrix_set_translation_2D(M.identity(), cml::vector2d(2., -3.));
  BOOST_CHECK_EQUAL(M(2,0), 2.);
  BOOST_CHECK_EQUAL(M(2,1), -3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(get_2D)

BOOST_AUTO_TEST_CASE(get1)
{
  cml::matrix33d M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);

  double e0, e1;
  cml::matrix_get_translation_2D(M, e0, e1);
  BOOST_CHECK_EQUAL(e0, 2.);
  BOOST_CHECK_EQUAL(e1, -3.);
}

BOOST_AUTO_TEST_CASE(get2)
{
  cml::matrix33d_r M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);

  double e0, e1;
  cml::matrix_get_translation_2D(M, e0, e1);
  BOOST_CHECK_EQUAL(e0, 2.);
  BOOST_CHECK_EQUAL(e1, -3.);
}

BOOST_AUTO_TEST_CASE(get3)
{
  cml::matrix33d M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);
  auto T = cml::matrix_get_translation_2D(M);
  BOOST_CHECK_EQUAL(T[0], 2.);
  BOOST_CHECK_EQUAL(T[1], -3.);
}

BOOST_AUTO_TEST_CASE(get4)
{
  cml::matrix33d_r M;
  cml::matrix_set_translation_2D(M.identity(), 2., -3.);
  auto T = cml::matrix_get_translation_2D(M);
  BOOST_CHECK_EQUAL(T[0], 2.);
  BOOST_CHECK_EQUAL(T[1], -3.);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(set_3D)

BOOST_AUTO_TEST_CASE(set1)
{
  cml::matrix44d M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);
  BOOST_CHECK_EQUAL(M(0,3), 2.);
  BOOST_CHECK_EQUAL(M(1,3), -3.);
  BOOST_CHECK_EQUAL(M(2,3), 1.);
}

BOOST_AUTO_TEST_CASE(set2)
{
  cml::matrix44d_r M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);
  BOOST_CHECK_EQUAL(M(3,0), 2.);
  BOOST_CHECK_EQUAL(M(3,1), -3.);
  BOOST_CHECK_EQUAL(M(3,2), 1.);
}

BOOST_AUTO_TEST_CASE(set3)
{
  cml::matrix44d M;
  cml::matrix_set_translation(M.identity(), cml::vector3d(2.,-3., 1.));
  BOOST_CHECK_EQUAL(M(0,3), 2.);
  BOOST_CHECK_EQUAL(M(1,3), -3.);
  BOOST_CHECK_EQUAL(M(2,3), 1.);
}

BOOST_AUTO_TEST_CASE(set4)
{
  cml::matrix44d_r M;
  cml::matrix_set_translation(M.identity(), cml::vector3d(2., -3., 1.));
  BOOST_CHECK_EQUAL(M(3,0), 2.);
  BOOST_CHECK_EQUAL(M(3,1), -3.);
  BOOST_CHECK_EQUAL(M(3,2), 1.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(get_3D)

BOOST_AUTO_TEST_CASE(get1)
{
  cml::matrix44d M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);

  double e0, e1, e2;
  cml::matrix_get_translation(M, e0, e1, e2);
  BOOST_CHECK_EQUAL(e0, 2.);
  BOOST_CHECK_EQUAL(e1, -3.);
  BOOST_CHECK_EQUAL(e2, 1.);
}

BOOST_AUTO_TEST_CASE(get2)
{
  cml::matrix44d_r M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);

  double e0, e1, e2;
  cml::matrix_get_translation(M, e0, e1, e2);
  BOOST_CHECK_EQUAL(e0, 2.);
  BOOST_CHECK_EQUAL(e1, -3.);
  BOOST_CHECK_EQUAL(e2, 1.);
}

BOOST_AUTO_TEST_CASE(get3)
{
  cml::matrix44d M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);
  auto T = cml::matrix_get_translation(M);
  BOOST_CHECK_EQUAL(T[0], 2.);
  BOOST_CHECK_EQUAL(T[1], -3.);
  BOOST_CHECK_EQUAL(T[2], 1.);
}

BOOST_AUTO_TEST_CASE(get4)
{
  cml::matrix44d_r M;
  cml::matrix_set_translation(M.identity(), 2., -3., 1.);
  auto T = cml::matrix_get_translation(M);
  BOOST_CHECK_EQUAL(T[0], 2.);
  BOOST_CHECK_EQUAL(T[1], -3.);
  BOOST_CHECK_EQUAL(T[2], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
