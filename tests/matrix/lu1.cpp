/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/lu.h>

#include <cml/vector.h>
#include <cml/matrix.h>

#include <cml/util/matrix_print.h>
#include <cml/util/vector_print.h>

/* Testing headers: */
#define BOOST_TEST_MODULE lu1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(lu1)
{
  auto M = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(M);
  double D = LU(0,0)*LU(1,1)*LU(2,2)*LU(3,3);
  BOOST_CHECK_CLOSE(D, -120., .001);

  auto expected = cml::matrix44d(
    2., 0., 2., .6,
    1.5, 3., 1., -2.9,
    2.5, (1.+2./3.), -(2.+2./3.), (5.+1./3.),
    -.5, (-2./3.), -1.9, 7.5
    );

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(LU(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot1)
{
  auto M = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(M);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}

BOOST_AUTO_TEST_CASE(lu_pivot2)
{
  auto M = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );

  cml::lu_pivot_result<cml::matrix44d> lup(M);
  cml::lu_pivot(lup);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}


BOOST_AUTO_TEST_CASE(lu_solve1)
{
  auto A = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(A);
  auto b = cml::vector4d(5., 1., 8., 3.);
  auto x = cml::lu_solve(LU, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_solve2)
{
  auto A = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(A);
  auto b = cml::vector4d(5., 1., 8., 3.);
  auto x = cml::vector4d();
  cml::lu_solve(LU, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}


BOOST_AUTO_TEST_CASE(lu_pivot_solve1)
{
  auto A = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto b = cml::vector4d(5., 1., 8., 3.);
  auto x = cml::lu_solve(lup, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot_solve2)
{
  auto A = cml::matrix44d(
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto b = cml::vector4d(5., 1., 8., 3.);
  auto x = cml::vector4d();
  cml::lu_solve(lup, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(lu1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::external44d(avM);
  auto LU = cml::lu(M);
  double D = LU(0,0)*LU(1,1)*LU(2,2)*LU(3,3);
  BOOST_CHECK_CLOSE(D, -120., .001);

  auto expected = cml::matrix44d(
    2., 0., 2., .6,
    1.5, 3., 1., -2.9,
    2.5, (1.+2./3.), -(2.+2./3.), (5.+1./3.),
    -.5, (-2./3.), -1.9, 7.5
    );

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(LU(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::external44d(avM);
  auto lup = cml::lu_pivot(M);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}

BOOST_AUTO_TEST_CASE(lu_pivot2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::external44d(avM);

  cml::lu_pivot_result<cml::matrix44d> lup(M);
  cml::lu_pivot(lup);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}


BOOST_AUTO_TEST_CASE(lu_solve1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto LU = cml::lu(A);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::external4d(avb);
  auto x = cml::lu_solve(LU, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_solve2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto LU = cml::lu(A);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::external4d(avb);

  double avx[4];
  auto x = cml::external4d(avx);

  cml::lu_solve(LU, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}


BOOST_AUTO_TEST_CASE(lu_pivot_solve1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::external4d(avb);
  auto x = cml::lu_solve(lup, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot_solve2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::external4d(avb);

  double avx[4];
  auto x = cml::external4d(avx);

  cml::lu_solve(lup, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(lu1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::externalmnd(4,4, avM);
  auto LU = cml::lu(M);
  double D = LU(0,0)*LU(1,1)*LU(2,2)*LU(3,3);
  BOOST_CHECK_CLOSE(D, -120., .001);

  auto expected = cml::matrix44d(
    2., 0., 2., .6,
    1.5, 3., 1., -2.9,
    2.5, (1.+2./3.), -(2.+2./3.), (5.+1./3.),
    -.5, (-2./3.), -1.9, 7.5
    );

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(LU(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::externalmnd(4,4, avM);
  auto lup = cml::lu_pivot(M);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}

BOOST_AUTO_TEST_CASE(lu_pivot2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto M = cml::externalmnd(4,4, avM);

  cml::lu_pivot_result<cml::matrix44d> lup(M);
  cml::lu_pivot(lup);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}


BOOST_AUTO_TEST_CASE(lu_solve1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::externalmnd(4,4, avM);
  auto LU = cml::lu(A);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::externalnd(4, avb);

  auto x = cml::lu_solve(LU, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_solve2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto LU = cml::lu(A);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::externalnd(4, avb);

  double avx[4];
  auto x = cml::externalnd(4, avx);

  cml::lu_solve(LU, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}


BOOST_AUTO_TEST_CASE(lu_pivot_solve1)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::externalnd(4, avb);

  auto x = cml::lu_solve(lup, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot_solve2)
{
  double avM[] = {
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
  };
  auto A = cml::external44d(avM);
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  double avb[] = { 5., 1., 8., 3. };
  auto b = cml::externalnd(4, avb);

  double avx[4];
  auto x = cml::externalnd(4, avx);

  cml::lu_solve(lup, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(lu1)
{
  auto M = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(M);
  double D = LU(0,0)*LU(1,1)*LU(2,2)*LU(3,3);
  BOOST_CHECK_CLOSE(D, -120., .001);

  auto expected = cml::matrix44d(
    2., 0., 2., .6,
    1.5, 3., 1., -2.9,
    2.5, (1.+2./3.), -(2.+2./3.), (5.+1./3.),
    -.5, (-2./3.), -1.9, 7.5
    );

  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(LU(i,j), expected(i,j), .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot1)
{
  auto M = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(M);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}

BOOST_AUTO_TEST_CASE(lu_pivot2)
{
  auto M = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );

  cml::lu_pivot_result<cml::matrixd> lup(M);
  cml::lu_pivot(lup);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto expected = cml::matrix44d(
     5.,  5., 4.,  2.,
     .4, -2., .4, -.2,
    -.2,  .5, 4., -.5,
     .6,  0., .4, -3.
    );
  for(int i = 0; i < 4; ++ i)
    for(int j = 0; j < 4; ++ j)
      BOOST_CHECK_CLOSE(lup.lu(i,j), expected(i,j), .001);

  std::array<int,4> order = { 2, 0, 3, 1 };
  for(int i = 0; i < 4; ++ i)
    BOOST_CHECK_EQUAL(lup.order[i], order[i]);
}


BOOST_AUTO_TEST_CASE(lu_solve1)
{
  auto A = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(A);
  auto b = cml::vectord(5., 1., 8., 3.);
  auto x = cml::lu_solve(LU, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_solve2)
{
  auto A = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto LU = cml::lu(A);
  auto b = cml::vectord(5., 1., 8., 3.);
  auto x = cml::vectord(4);
  cml::lu_solve(LU, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}


BOOST_AUTO_TEST_CASE(lu_pivot_solve1)
{
  auto A = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto b = cml::vectord(5., 1., 8., 3.);
  auto x = cml::lu_solve(lup, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_CASE(lu_pivot_solve2)
{
  auto A = cml::matrixd(
    4,4,
     2.,  0.,  2.,  .6,
     3.,  3.,  4.,  -2.,
     5.,  5.,  4.,   2.,
    -1., -2., 3.4,  -1.
    );
  auto lup = cml::lu_pivot(A);
  BOOST_CHECK_EQUAL(lup.sign, -1);

  auto b = cml::vectord(5., 1., 8., 3.);
  auto x = cml::vectord(4);
  cml::lu_solve(lup, x, b);
  auto Ax = A*x;
  for(int i = 0; i < 4; ++ i) BOOST_CHECK_CLOSE(Ax[i], b[i], .001);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
