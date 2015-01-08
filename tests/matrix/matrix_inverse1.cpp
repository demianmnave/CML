/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/inverse.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/external.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_inverse1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(inverse_assign_2x2)
{
  cml::matrix22d M(
    1., 2.,
    3., 4.
    );
  M.inverse();
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_3x3)
{
  cml::matrix33d M(
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );
  M.inverse();

  cml::matrix33d expected(
    22.,   1., -3.,
     8., -11.,  3.,
    -6.,   7., -1.
    );
  expected *= 1./20.;

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_4x4)
{
  cml::matrix44d M(
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );
  M.inverse();

  cml::matrix44d expected(
    242.,  20., -33., -1.,
     12., -48.,  45., -9.,
     46., -32., -27., 13.,
    -44.,  43.,   6., -5.
    );
  expected *= 1./228.;

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_2x2)
{
  auto M = cml::inverse(
    cml::matrix22d(
      1., 2.,
      3., 4.
      )
    );
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(inverse_assign_2x2)
{
  double avM[] = {
    1., 2.,
    3., 4.
  };
  cml::external22d M(avM);
  M.inverse();
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_3x3)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::external33d M(avM);
  M.inverse();

  cml::matrix33d expected(
    22.,   1., -3.,
     8., -11.,  3.,
    -6.,   7., -1.
    );
  expected *= 1./20.;

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_4x4)
{
  double avM[] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  cml::external44d M(avM);
  M.inverse();

  cml::matrix44d expected(
    242.,  20., -33., -1.,
     12., -48.,  45., -9.,
     46., -32., -27., 13.,
    -44.,  43.,   6., -5.
    );
  expected *= 1./228.;

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_2x2)
{
  double avM[] = {
    1., 2.,
    3., 4.
  };
  auto M = cml::inverse(cml::external22d(avM));
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(inverse_assign_2x2)
{
  double avM[] = {
    1., 2.,
    3., 4.
  };
  cml::externalmnd M(2,2, avM);
  M.inverse();
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_3x3)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::externalmnd M(3,3, avM);
  M.inverse();

  cml::matrix33d expected(
    22.,   1., -3.,
     8., -11.,  3.,
    -6.,   7., -1.
    );
  expected *= 1./20.;

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_4x4)
{
  double avM[] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  cml::externalmnd M(4,4, avM);
  M.inverse();

  cml::matrix44d expected(
    242.,  20., -33., -1.,
     12., -48.,  45., -9.,
     46., -32., -27., 13.,
    -44.,  43.,   6., -5.
    );
  expected *= 1./228.;

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_2x2)
{
  double avM[] = {
    1., 2.,
    3., 4.
  };
  auto M = cml::inverse(cml::externalmnd(2,2, avM));
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  double avM[3*4];
  cml::externalmnd M(3,4, avM);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_THROW(M.inverse(), cml::non_square_matrix_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(inverse_assign_2x2)
{
  cml::matrixd M(
    2,2,
    1., 2.,
    3., 4.
    );
  M.inverse();
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_3x3)
{
  cml::matrixd M(
    3,3,
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );
  M.inverse();

  cml::matrix33d expected(
    22.,   1., -3.,
     8., -11.,  3.,
    -6.,   7., -1.
    );
  expected *= 1./20.;

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_assign_4x4)
{
  cml::matrixd M(
    4,4,
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );
  M.inverse();

  cml::matrix44d expected(
    242.,  20., -33., -1.,
     12., -48.,  45., -9.,
     46., -32., -27., 13.,
    -44.,  43.,   6., -5.
    );
  expected *= 1./228.;

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(M(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(inverse_2x2)
{
  auto M = cml::inverse(
    cml::matrixd(
      2,2,
      1., 2.,
      3., 4.
      )
    );
  BOOST_CHECK_CLOSE(M(0,0), -2.0, .001);
  BOOST_CHECK_CLOSE(M(0,1),  1.0, .001);
  BOOST_CHECK_CLOSE(M(1,0),  1.5, .001);
  BOOST_CHECK_CLOSE(M(1,1), -0.5, .001);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::matrixd M(3,4);
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_THROW(M.inverse(), cml::non_square_matrix_error);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
