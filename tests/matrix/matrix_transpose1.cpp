/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <typeinfo>
#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/matrix/transpose.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/external.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_transpose1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(transpose_assign_3x3)
{
  auto M = cml::matrix33d(
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );

  M.transpose();
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(M(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_1)
{
  auto M = cml::matrix33d(
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );

  auto T = cml::transpose(M);
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_2)
{
  auto T = cml::transpose(
    cml::matrix33d(
      1.,  2.,  3.,
      1.,  4.,  9.,
      1., 16., 25.
      )
    );

  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(transpose_assign_3x3)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::external33d M(avM);

  M.transpose();
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(M(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_1)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::external33d M(avM);

  auto T = cml::transpose(M);
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_2)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };

  auto T = cml::transpose(cml::external33d(avM));
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(transpose_assign_3x3)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::externalmnd M(3,3, avM);

  M.transpose();
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(M(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_1)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };
  cml::externalmnd M(3,3, avM);

  auto T = cml::transpose(M);
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_2)
{
  double avM[] = {
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
  };

  auto T = cml::transpose(cml::externalmnd(3,3, avM));
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(transpose_assign_3x3)
{
  auto M = cml::matrixd(
    3,3,
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );

  M.transpose();
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(M(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_1)
{
  auto M = cml::matrixd(
    3,3,
    1.,  2.,  3.,
    1.,  4.,  9.,
    1., 16., 25.
    );

  auto T = cml::transpose(M);
  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_CASE(transpose_3x3_2)
{
  auto T = cml::transpose(
    cml::matrixd(
      3,3,
      1.,  2.,  3.,
      1.,  4.,  9.,
      1., 16., 25.
      )
    );

  cml::matrix33d expected(
    1., 1.,  1.,
    2., 4., 16.,
    3., 9., 25.
    );

  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++ j)
      BOOST_CHECK_EQUAL(T(i,j), expected(i,j));
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
