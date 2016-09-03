/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/basis.h>

#include <cml/matrix/row_col.h>
#include <cml/vector.h>
#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE basis1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(basis1)
{
  // col basis:
  auto M = cml::matrix44d(
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto basis = cml::basis(M, 1);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(1,i));
}

BOOST_AUTO_TEST_CASE(basis2)
{
  auto M = cml::matrix44d_r(
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto basis = cml::basis(M, 2);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(2,i));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(basis1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::external44d(avM);

  auto basis = cml::basis(M, 1);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(1,i));
}

BOOST_AUTO_TEST_CASE(basis2)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::external44d(avM);

  auto basis = cml::basis(M, 2);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(2,i));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(basis1)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::externalmnd(4,4, avM);

  auto basis = cml::basis(M, 1);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(1,i));
}

BOOST_AUTO_TEST_CASE(basis2)
{
  double avM[16] = {
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
  };
  auto M = cml::externalmnd(4,4, avM);

  auto basis = cml::basis(M, 2);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(2,i));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(basis1)
{
  auto M = cml::matrixd(
    4,4,
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto basis = cml::basis(M, 1);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(1,i));
}

BOOST_AUTO_TEST_CASE(basis2)
{
  auto M = cml::matrixd(
    4,4,
    1.,  2.,  3., 4.,
    1.,  4.,  9., 16.,
    1., 16., 25., 36.,
    1., 36., 81., 100.
    );

  auto basis = cml::basis(M, 2);
  BOOST_CHECK_EQUAL(basis.size(), 4);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(2,i));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed)

#if 0
BOOST_AUTO_TEST_CASE(basis1)
{
  auto v = cml::vector3d(1., 2., 3.);
  auto C = cml::as<col_basis>(cml::outer(v,v));
  // cml::as<> not implemented yet.
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto basis = cml::basis(C,1);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], C.basis_element(1,i));
}

BOOST_AUTO_TEST_CASE(basis2)
{
  auto v = cml::vector3d(1., 2., 3.);
  auto C = cml::as<row_basis>(cml::outer(v,v));
  // cml::as<> not implemented yet.
  BOOST_REQUIRE_EQUAL(C.rows(), 3);
  BOOST_REQUIRE_EQUAL(C.cols(), 3);

  auto basis = cml::basis(C,2);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], C.basis_element(2,i));
}
#endif

BOOST_AUTO_TEST_CASE(basis3)
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
  auto basis = cml::basis(M,1);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(i,1));
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
  auto basis = cml::basis(M,1);
  for(int i = 0; i < basis.size(); ++ i)
    BOOST_CHECK_EQUAL(basis[i], M.basis_element(1,i));
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
