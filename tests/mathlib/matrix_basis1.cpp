/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/mathlib/matrix/basis.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_basis1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(basis_2D)

BOOST_AUTO_TEST_CASE(basis1)
{
  cml::matrix22d M;	// column basis

  cml::matrix_set_x_basis_vector_2D(M, cml::vector2d(1., 2.));
  cml::matrix_set_y_basis_vector_2D(M, cml::vector2d(3., 4.));

  auto b1 = cml::matrix_get_x_basis_vector_2D(M);
  auto b2 = cml::matrix_get_y_basis_vector_2D(M);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b2[0], 3.);
  BOOST_CHECK_EQUAL(b2[1], 4.);
}

BOOST_AUTO_TEST_CASE(basis2)
{
  cml::matrix22d M;	// column basis

  cml::matrix_set_transposed_x_basis_vector_2D(M, cml::vector2d(1., 2.));
  cml::matrix_set_transposed_y_basis_vector_2D(M, cml::vector2d(3., 4.));

  auto b1 = cml::matrix_get_transposed_x_basis_vector_2D(M);
  auto b2 = cml::matrix_get_transposed_y_basis_vector_2D(M);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b2[0], 3.);
  BOOST_CHECK_EQUAL(b2[1], 4.);
}

BOOST_AUTO_TEST_CASE(basis3)
{
  cml::matrix22d M;	// column basis

  cml::matrix_set_basis_vectors_2D(
    M, cml::vector2d(1., 2.), cml::vector2d(3., 4.));

  cml::vectord b1, b2;
  cml::matrix_get_basis_vectors_2D(M, b1, b2);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b2[0], 3.);
  BOOST_CHECK_EQUAL(b2[1], 4.);
}

BOOST_AUTO_TEST_CASE(basis4)
{
  cml::matrix22d M;	// column basis

  cml::matrix_set_transposed_basis_vectors_2D(
    M, cml::vector2d(1., 2.), cml::vector2d(3., 4.));

  cml::vectord b1, b2;
  cml::matrix_get_transposed_basis_vectors_2D(M, b1, b2);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b2[0], 3.);
  BOOST_CHECK_EQUAL(b2[1], 4.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(basis_3D)

BOOST_AUTO_TEST_CASE(basis1)
{
  cml::matrix33d M;	// column basis

  cml::matrix_set_x_basis_vector(M, cml::vector3d(1., 2., 3.));
  cml::matrix_set_y_basis_vector(M, cml::vector3d(4., 5., 6.));
  cml::matrix_set_z_basis_vector(M, cml::vector3d(7., 8., 9.));

  auto b1 = cml::matrix_get_x_basis_vector(M);
  auto b2 = cml::matrix_get_y_basis_vector(M);
  auto b3 = cml::matrix_get_z_basis_vector(M);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b1[2], 3.);

  BOOST_CHECK_EQUAL(b2[0], 4.);
  BOOST_CHECK_EQUAL(b2[1], 5.);
  BOOST_CHECK_EQUAL(b2[2], 6.);

  BOOST_CHECK_EQUAL(b3[0], 7.);
  BOOST_CHECK_EQUAL(b3[1], 8.);
  BOOST_CHECK_EQUAL(b3[2], 9.);
}

BOOST_AUTO_TEST_CASE(basis2)
{
  cml::matrix33d M;	// column basis

  cml::matrix_set_transposed_x_basis_vector(M, cml::vector3d(1., 2., 3.));
  cml::matrix_set_transposed_y_basis_vector(M, cml::vector3d(4., 5., 6.));
  cml::matrix_set_transposed_z_basis_vector(M, cml::vector3d(7., 8., 9.));

  auto b1 = cml::matrix_get_transposed_x_basis_vector(M);
  auto b2 = cml::matrix_get_transposed_y_basis_vector(M);
  auto b3 = cml::matrix_get_transposed_z_basis_vector(M);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b1[2], 3.);

  BOOST_CHECK_EQUAL(b2[0], 4.);
  BOOST_CHECK_EQUAL(b2[1], 5.);
  BOOST_CHECK_EQUAL(b2[2], 6.);

  BOOST_CHECK_EQUAL(b3[0], 7.);
  BOOST_CHECK_EQUAL(b3[1], 8.);
  BOOST_CHECK_EQUAL(b3[2], 9.);
}

BOOST_AUTO_TEST_CASE(basis3)
{
  cml::matrix33d M;	// column basis

  cml::matrix_set_basis_vectors(M, cml::vector3d(1., 2., 3.),
    cml::vector3d(4., 5., 6.), cml::vector3d(7., 8., 9.));

  cml::vectord b1, b2, b3;
  cml::matrix_get_basis_vectors(M, b1, b2, b3);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b1[2], 3.);

  BOOST_CHECK_EQUAL(b2[0], 4.);
  BOOST_CHECK_EQUAL(b2[1], 5.);
  BOOST_CHECK_EQUAL(b2[2], 6.);

  BOOST_CHECK_EQUAL(b3[0], 7.);
  BOOST_CHECK_EQUAL(b3[1], 8.);
  BOOST_CHECK_EQUAL(b3[2], 9.);
}

BOOST_AUTO_TEST_CASE(basis4)
{
  cml::matrix33d M;	// column basis

  cml::matrix_set_transposed_basis_vectors(M, cml::vector3d(1., 2., 3.),
    cml::vector3d(4., 5., 6.), cml::vector3d(7., 8., 9.));

  cml::vectord b1, b2, b3;
  cml::matrix_get_transposed_basis_vectors(M, b1, b2, b3);

  BOOST_CHECK_EQUAL(b1[0], 1.);
  BOOST_CHECK_EQUAL(b1[1], 2.);
  BOOST_CHECK_EQUAL(b1[2], 3.);

  BOOST_CHECK_EQUAL(b2[0], 4.);
  BOOST_CHECK_EQUAL(b2[1], 5.);
  BOOST_CHECK_EQUAL(b2[2], 6.);

  BOOST_CHECK_EQUAL(b3[0], 7.);
  BOOST_CHECK_EQUAL(b3[1], 8.);
  BOOST_CHECK_EQUAL(b3[2], 9.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(basis_nD)

BOOST_AUTO_TEST_CASE(basis1)
{
  auto M = cml::matrix34d_c(
    1., 0., 0., 3.,
    0., 1., 0., 2.,
    0., 0., 1., 1.
    );
  auto T = cml::matrix_get_basis_vector_nD(M, 3);
  BOOST_CHECK_EQUAL(T[0], 3.);
  BOOST_CHECK_EQUAL(T[1], 2.);
  BOOST_CHECK_EQUAL(T[2], 1.);
}

BOOST_AUTO_TEST_CASE(basis2)
{
  auto M = cml::matrix43d_r(
    1., 0., 0.,
    0., 1., 0.,
    0., 0., 1.,
    3., 2., 1.
    );
  auto T = cml::matrix_get_basis_vector_nD(M, 3);
  BOOST_CHECK_EQUAL(T[0], 3.);
  BOOST_CHECK_EQUAL(T[1], 2.);
  BOOST_CHECK_EQUAL(T[2], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
