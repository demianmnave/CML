/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/matrix_product.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_matrix_product1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrix22d M1(
    1., 2.,
    3., 4.
    );
  cml::matrix22d M2(
    5., 6.,
    7., 8.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix22d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 19.);
  BOOST_CHECK_EQUAL(M(0,1), 22.);
  BOOST_CHECK_EQUAL(M(1,0), 43.);
  BOOST_CHECK_EQUAL(M(1,1), 50.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrix<double, cml::fixed<3,2>> M1(
    1., 1.,
    2., 2.,
    3., 3.
    );
  cml::matrix23d M2(
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::external22d M1(aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::external22d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix22d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 19.);
  BOOST_CHECK_EQUAL(M(0,1), 22.);
  BOOST_CHECK_EQUAL(M(1,0), 43.);
  BOOST_CHECK_EQUAL(M(1,1), 50.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<3,2>> M1(aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::external23d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(product1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::externalmnd M1(2,2, aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::externalmnd M2(2,2, aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 19.);
  BOOST_CHECK_EQUAL(M(0,1), 22.);
  BOOST_CHECK_EQUAL(M(1,0), 43.);
  BOOST_CHECK_EQUAL(M(1,1), 50.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::externalmnd M1(3,2, aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::externalmnd M2(2,3, aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  double aM1[4], aM2[6];
  BOOST_REQUIRE_THROW(
    (cml::externalmnd(2,2, aM1) * cml::externalmnd(3,2, aM2)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(product1)
{
  cml::matrixd M1(2,2,
    1., 2.,
    3., 4.
    );
  cml::matrixd M2(2,2,
    5., 6.,
    7., 8.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 19.);
  BOOST_CHECK_EQUAL(M(0,1), 22.);
  BOOST_CHECK_EQUAL(M(1,0), 43.);
  BOOST_CHECK_EQUAL(M(1,1), 50.);
}

BOOST_AUTO_TEST_CASE(product2)
{
  cml::matrixd M1(3,2,
    1., 1.,
    2., 2.,
    3., 3.
    );
  cml::matrixd M2(2,3,
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(size_checking1)
{
  BOOST_REQUIRE_THROW(
    (cml::matrixd(2,2) * cml::matrixd(3,2)),
    cml::incompatible_matrix_inner_size_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_fixed)

BOOST_AUTO_TEST_CASE(dynamic1)
{
  cml::matrix<double, cml::fixed<3,2>> M1(
    1., 1.,
    2., 2.,
    3., 3.
    );
  cml::matrixd M2(2,3,
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external1)
{
  cml::matrix<double, cml::fixed<3,2>> M1(
    1., 1.,
    2., 2.,
    3., 3.
    );

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::external23d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external2)
{
  cml::matrix<double, cml::fixed<3,2>> M1(
    1., 1.,
    2., 2.,
    3., 3.
    );

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::externalmnd M2(2,3, aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_dynamic)

BOOST_AUTO_TEST_CASE(fixed1)
{
  cml::matrixd M1(3,2,
    1., 1.,
    2., 2.,
    3., 3.
    );
  cml::matrix23d M2(
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external1)
{
  cml::matrixd M1(3,2,
    1., 1.,
    2., 2.,
    3., 3.
    );

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::external23d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external2)
{
  cml::matrixd M1(3,2,
    1., 1.,
    2., 2.,
    3., 3.
    );

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::externalmnd M2(2,3, aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_fixed_external)

BOOST_AUTO_TEST_CASE(fixed1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<3,2>> M1(aM1);

  cml::matrix23d M2(
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<3,2>> M1(aM1);

  cml::matrixd M2(2,3,
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<3,2>> M1(aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::external23d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external2)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<3,2>> M1(aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::externalmnd M2(2,3, aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_dynamic_external)

BOOST_AUTO_TEST_CASE(fixed1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<>> M1(3,2, aM1);

  cml::matrix23d M2(
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<>> M1(3,2, aM1);

  cml::matrixd M2(2,3,
    1., 2., 3.,
    1., 2., 3.
    );

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external1)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<>> M1(3,2, aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::external23d M2(aM2);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_CASE(external2)
{
  double aM1[] = {
    1., 1.,
    2., 2.,
    3., 3.
  };
  cml::matrix<double, cml::external<>> M1(3,2, aM1);

  double aM2[] = {
    1., 2., 3.,
    1., 2., 3.
  };
  cml::externalmnd M2(aM2, 2,3);

  auto M = M1*M2;
  BOOST_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 3);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(0,2), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 4.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
  BOOST_CHECK_EQUAL(M(1,2), 12.);
  BOOST_CHECK_EQUAL(M(2,0), 6.);
  BOOST_CHECK_EQUAL(M(2,1), 12.);
  BOOST_CHECK_EQUAL(M(2,2), 18.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
