/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/matrix/dynamic_external.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE dynamic_external_matrix1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(typecheck)
{
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::externalmnd::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::externalmnd::layout_tag,cml::row_major>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::externalmnd_c::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::externalmnd_c::layout_tag,cml::col_major>::value),
    true);
}

BOOST_AUTO_TEST_CASE(array_construct1)
{
  double data[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::externalmnd M(data, 3,4);
  // Note: external<> refers to the wrapped data in the layout assigned to
  // the matrix.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_construct2)
{
  double data[] = {
    1., 5., 9.,
    2., 6., 0.,
    3., 7., 0.,
    4., 8., 0.
  };
  cml::externalmnd_c M(data, 3,4);
  // Note: external<> refers to the wrapped data in the layout assigned to
  // the matrix.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_assign1)
{
  double data[3*4];
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::externalmnd_c M(data, 3,4);
  M = aM;
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_assign2)
{
  double data[3*4];
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::externalmnd_c M(data, 3,4);
  M = aM;
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_construct1)
{
  double data[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::externalmnd M(data);
  // Note: external<> refers to the wrapped data in the layout assigned to
  // the matrix.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0][0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_construct2)
{
  double data[4][3] = {
    { 1., 5., 9. },
    { 2., 6., 0. },
    { 3., 7., 0. },
    { 4., 8., 0. }
  };
  cml::externalmnd_c M(data);
  // Note: external<> refers to the wrapped data in the layout assigned to
  // the matrix.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0][0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_assign1)
{
  double data[3*4];
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::externalmnd_c M(data, 3,4);
  M = aM;
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_assign2)
{
  double data[3*4];
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::externalmnd_c M(data, 3,4);
  M = aM;
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_assign1)
{
  double data[3*4];
  cml::externalmnd_c M(data, 3,4);
  M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_assign2)
{
  double data[3*4];
  cml::externalmnd_c M(data, 3,4);
  M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  // Note: external<> copies arrays using row-major layout.

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(resize1)
{
  double data[3*4];
  cml::externalmnd_c M(3,4, data);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_REQUIRE_NO_THROW(M.resize(4,3));
}

BOOST_AUTO_TEST_CASE(resize2)
{
  double data[3*4];
  cml::externalmnd_c M(3,4, data);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_REQUIRE_THROW(M.resize(3,3), cml::matrix_size_error);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  double data[3*4];
  cml::externalmnd_c M(data, 3,4);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_REQUIRE_THROW(
    (M = {
     1.,  2.,  3.,  4.,
     5.,  6.,  7.,  8.,
     9.
     }), cml::incompatible_matrix_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  double data[3*4];
  cml::externalmnd_c M(data, 3,4);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_EQUAL(M.data(), &data[0]);
  BOOST_REQUIRE_THROW(
    (M = {
     1.,  2.,  3.,  4.,
     5.,  6.,  7.,  8.,
     9.
     }), cml::incompatible_matrix_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
