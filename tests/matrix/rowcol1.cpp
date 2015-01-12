/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/row_col.h>

#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE rowcol1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(row1)
{
  auto M = cml::matrix44d(
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto row1 = cml::row(M, 1);
  BOOST_CHECK_EQUAL(row1.size(), 4);
  for(int j = 0; j < row1.size(); ++ j)
    BOOST_CHECK_EQUAL(row1[j], M(1,j));
}

BOOST_AUTO_TEST_CASE(col1)
{
  auto M = cml::matrix44d(
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto col3 = cml::col(M, 3);
  BOOST_CHECK_EQUAL(col3.size(), 4);
  for(int i = 0; i < col3.size(); ++ i)
    BOOST_CHECK_EQUAL(col3[i], M(i,3));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(row1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::external44d(avM);

  auto row1 = cml::row(M, 1);
  BOOST_CHECK_EQUAL(row1.size(), 4);
  for(int j = 0; j < row1.size(); ++ j)
    BOOST_CHECK_EQUAL(row1[j], M(1,j));
}

BOOST_AUTO_TEST_CASE(col1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::external44d(avM);

  auto col3 = cml::col(M, 3);
  BOOST_CHECK_EQUAL(col3.size(), 4);
  for(int i = 0; i < col3.size(); ++ i)
    BOOST_CHECK_EQUAL(col3[i], M(i,3));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(row1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::externalmnd(4,4, avM);

  auto row1 = cml::row(M, 1);
  BOOST_CHECK_EQUAL(row1.size(), 4);
  for(int j = 0; j < row1.size(); ++ j)
    BOOST_CHECK_EQUAL(row1[j], M(1,j));
}

BOOST_AUTO_TEST_CASE(col1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::externalmnd(4,4, avM);

  auto col3 = cml::col(M, 3);
  BOOST_CHECK_EQUAL(col3.size(), 4);
  for(int i = 0; i < col3.size(); ++ i)
    BOOST_CHECK_EQUAL(col3[i], M(i,3));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(row1)
{
  auto M = cml::matrixd(
    4,4,
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto row1 = cml::row(M, 1);
  BOOST_CHECK_EQUAL(row1.size(), 4);
  for(int j = 0; j < row1.size(); ++ j)
    BOOST_CHECK_EQUAL(row1[j], M(1,j));
}

BOOST_AUTO_TEST_CASE(col1)
{
  auto M = cml::matrixd(
    4,4,
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto col3 = cml::col(M, 3);
  BOOST_CHECK_EQUAL(col3.size(), 4);
  for(int i = 0; i < col3.size(); ++ i)
    BOOST_CHECK_EQUAL(col3[i], M(i,3));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed)

BOOST_AUTO_TEST_CASE(row1)
{
  auto v = cml::vector3d(1., 2., 3.);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto row1 = cml::row(C,1);
  for(int j = 0; j < row1.size(); ++ j)
    BOOST_CHECK_EQUAL(row1[j], C(1,j));
}

BOOST_AUTO_TEST_CASE(col1)
{
  auto v = cml::vector3d(1., 2., 3.);
  auto C = cml::outer(v,v);
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto col1 = cml::col(C,1);
  for(int i = 0; i < col1.size(); ++ i)
    BOOST_CHECK_EQUAL(col1[i], C(i,1));
}

BOOST_AUTO_TEST_CASE(row2)
{
  auto M1 = cml::matrix22d(
    1., 2.,
    3., 4.
    );
  auto M2 = cml::matrix22d(
    5., 6.,
    7., 8.
    );

  auto M = M1 - M2;
  auto row2 = cml::row(M,2);
  for(int j = 0; j < row2.size(); ++ j)
    BOOST_CHECK_EQUAL(row2[j], M(2,j));
}

BOOST_AUTO_TEST_CASE(col2)
{
  auto M1 = cml::matrix22d(
    1., 2.,
    3., 4.
    );
  auto M2 = cml::matrix22d(
    5., 6.,
    7., 8.
    );

  auto M = M1 - M2;
  auto col2 = cml::col(M,2);
  for(int i = 0; i < col2.size(); ++ i)
    BOOST_CHECK_EQUAL(col2[i], M(i,2));
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
