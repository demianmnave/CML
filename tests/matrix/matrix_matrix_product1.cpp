/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/matrix/matrix_product.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/types.h>
#include <cml/matrix/comparison.h>

#include <cml/util/matrix_print.h>

/* Testing headers: */
#include "catch_runner.h"

CATCH_TEST_CASE("fixed-product1")
{
  cml::matrix22d M1(1., 2., 3., 4.);
  cml::matrix22d M2(5., 6., 7., 8.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix22d>::value));
  CATCH_REQUIRE(M.rows() == 2);
  CATCH_REQUIRE(M.cols() == 2);
  CATCH_CHECK(M(0, 0) == 19.);
  CATCH_CHECK(M(0, 1) == 22.);
  CATCH_CHECK(M(1, 0) == 43.);
  CATCH_CHECK(M(1, 1) == 50.);
}

CATCH_TEST_CASE("fixed-product2")
{
  cml::matrix<double, cml::fixed<3, 2>> M1(1., 1., 2., 2., 3., 3.);
  cml::matrix23d M2(1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("fixed-product3")
{
  // clang-format off
  cml::matrix44d M1(
    1., 1., 1., 1.,
    2., 1., 1., 1.,
    3., 3., 1., 1.,
    4., 4., 4., 1.
  );

  cml::matrix44d M2(
    1., 4., 4., 4.,
    1., 1., 3., 3.,
    1., 1., 1., 2.,
    1., 1., 1., 1.
  );

  cml::matrix44d X(
    4., 7., 9., 10.,
    5., 11., 13., 14.,
    8., 17., 23., 24.,
    13., 25., 33., 37.
  );
  // clang-format on

  const auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), const cml::matrix44d>::value));
  CATCH_CHECK(M == X);
}

CATCH_TEST_CASE("fixed-product4")
{
  // clang-format off
  cml::matrix44d_c M1(
    1., 1., 1., 1.,
    2., 1., 1., 1.,
    3., 3., 1., 1.,
    4., 4., 4., 1.
  );

  cml::matrix44d_c M2(
    1., 4., 4., 4.,
    1., 1., 3., 3.,
    1., 1., 1., 2.,
    1., 1., 1., 1.
  );

  cml::matrix44d_c X(
    4., 7., 9., 10.,
    5., 11., 13., 14.,
    8., 17., 23., 24.,
    13., 25., 33., 37.
  );
  // clang-format on

  const auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), const cml::matrix44d_c>::value));
  CATCH_CHECK(M == X);
}

CATCH_TEST_CASE("fixed-product5")
{
  // clang-format off
  cml::matrix44f M1(
    1.f, 1.f, 1.f, 1.f,
    2.f, 1.f, 1.f, 1.f,
    3.f, 3.f, 1.f, 1.f,
    4.f, 4.f, 4.f, 1.f
  );

  cml::matrix44f M2(
    1.f, 4.f, 4.f, 4.f,
    1.f, 1.f, 3.f, 3.f,
    1.f, 1.f, 1.f, 2.f,
    1.f, 1.f, 1.f, 1.f
  );

  cml::matrix44f X(
    4.f, 7.f, 9.f, 10.f,
    5.f, 11.f, 13.f, 14.f,
    8.f, 17.f, 23.f, 24.f,
    13.f, 25.f, 33.f, 37.f
  );
  // clang-format on

  const auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), const cml::matrix44f>::value));
  CATCH_CHECK(M == X);
}

CATCH_TEST_CASE("fixed-product6")
{
  // clang-format off
  cml::matrix44f_c M1(
    1.f, 1.f, 1.f, 1.f,
    2.f, 1.f, 1.f, 1.f,
    3.f, 3.f, 1.f, 1.f,
    4.f, 4.f, 4.f, 1.f
  );

  cml::matrix44f_c M2(
    1.f, 4.f, 4.f, 4.f,
    1.f, 1.f, 3.f, 3.f,
    1.f, 1.f, 1.f, 2.f,
    1.f, 1.f, 1.f, 1.f
  );

  cml::matrix44f_c X(
    4.f, 7.f, 9.f, 10.f,
    5.f, 11.f, 13.f, 14.f,
    8.f, 17.f, 23.f, 24.f,
    13.f, 25.f, 33.f, 37.f
  );
  // clang-format on

  const auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), const cml::matrix44f_c>::value));
  CATCH_CHECK(M == X);
}

CATCH_TEST_CASE("fixed external-product1")
{
  double aM1[] = {1., 2., 3., 4.};
  cml::external22d M1(aM1);

  double aM2[] = {5., 6., 7., 8.};
  cml::external22d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix22d>::value));
  CATCH_REQUIRE(M.rows() == 2);
  CATCH_REQUIRE(M.cols() == 2);
  CATCH_CHECK(M(0, 0) == 19.);
  CATCH_CHECK(M(0, 1) == 22.);
  CATCH_CHECK(M(1, 0) == 43.);
  CATCH_CHECK(M(1, 1) == 50.);
}

CATCH_TEST_CASE("fixed external-product2")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<3, 2>> M1(aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::external23d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("dynamic external-product1")
{
  double aM1[] = {1., 2., 3., 4.};
  cml::externalmnd M1(2, 2, aM1);

  double aM2[] = {5., 6., 7., 8.};
  cml::externalmnd M2(2, 2, aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 2);
  CATCH_REQUIRE(M.cols() == 2);
  CATCH_CHECK(M(0, 0) == 19.);
  CATCH_CHECK(M(0, 1) == 22.);
  CATCH_CHECK(M(1, 0) == 43.);
  CATCH_CHECK(M(1, 1) == 50.);
}

CATCH_TEST_CASE("dynamic external-product2")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::externalmnd M1(3, 2, aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::externalmnd M2(2, 3, aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("dynamic external-size_checking1")
{
  double aM1[4], aM2[6];
  CATCH_REQUIRE_THROWS_AS(
    (cml::externalmnd(2, 2, aM1) * cml::externalmnd(3, 2, aM2)),
    cml::incompatible_matrix_inner_size_error);
}

CATCH_TEST_CASE("dynamic-product1")
{
  cml::matrixd M1(2, 2, 1., 2., 3., 4.);
  cml::matrixd M2(2, 2, 5., 6., 7., 8.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 2);
  CATCH_REQUIRE(M.cols() == 2);
  CATCH_CHECK(M(0, 0) == 19.);
  CATCH_CHECK(M(0, 1) == 22.);
  CATCH_CHECK(M(1, 0) == 43.);
  CATCH_CHECK(M(1, 1) == 50.);
}

CATCH_TEST_CASE("dynamic-product2")
{
  cml::matrixd M1(3, 2, 1., 1., 2., 2., 3., 3.);
  cml::matrixd M2(2, 3, 1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("dynamic-size_checking1")
{
  CATCH_REQUIRE_THROWS_AS((cml::matrixd(2, 2) * cml::matrixd(3, 2)),
    cml::incompatible_matrix_inner_size_error);
}

CATCH_TEST_CASE("mixed fixed-dynamic1")
{
  cml::matrix<double, cml::fixed<3, 2>> M1(1., 1., 2., 2., 3., 3.);
  cml::matrixd M2(2, 3, 1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed-external1")
{
  cml::matrix<double, cml::fixed<3, 2>> M1(1., 1., 2., 2., 3., 3.);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::external23d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed-external2")
{
  cml::matrix<double, cml::fixed<3, 2>> M1(1., 1., 2., 2., 3., 3.);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::externalmnd M2(2, 3, aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic-fixed1")
{
  cml::matrixd M1(3, 2, 1., 1., 2., 2., 3., 3.);
  cml::matrix23d M2(1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic-external1")
{
  cml::matrixd M1(3, 2, 1., 1., 2., 2., 3., 3.);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::external23d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic-external2")
{
  cml::matrixd M1(3, 2, 1., 1., 2., 2., 3., 3.);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::externalmnd M2(2, 3, aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed external-fixed1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<3, 2>> M1(aM1);

  cml::matrix23d M2(1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed external-dynamic1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<3, 2>> M1(aM1);

  cml::matrixd M2(2, 3, 1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed external-external1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<3, 2>> M1(aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::external23d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrix33d>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed fixed external-external2")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<3, 2>> M1(aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::externalmnd M2(2, 3, aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic external-fixed1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<>> M1(3, 2, aM1);

  cml::matrix23d M2(1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic external-dynamic1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<>> M1(3, 2, aM1);

  cml::matrixd M2(2, 3, 1., 2., 3., 1., 2., 3.);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic external-external1")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<>> M1(3, 2, aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::external23d M2(aM2);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}

CATCH_TEST_CASE("mixed dynamic external-external2")
{
  double aM1[] = {1., 1., 2., 2., 3., 3.};
  cml::matrix<double, cml::external<>> M1(3, 2, aM1);

  double aM2[] = {1., 2., 3., 1., 2., 3.};
  cml::externalmnd M2(aM2, 2, 3);

  auto M = M1 * M2;
  CATCH_REQUIRE((std::is_same<decltype(M), cml::matrixd>::value));
  CATCH_REQUIRE(M.rows() == 3);
  CATCH_REQUIRE(M.cols() == 3);
  CATCH_CHECK(M(0, 0) == 2.);
  CATCH_CHECK(M(0, 1) == 4.);
  CATCH_CHECK(M(0, 2) == 6.);
  CATCH_CHECK(M(1, 0) == 4.);
  CATCH_CHECK(M(1, 1) == 8.);
  CATCH_CHECK(M(1, 2) == 12.);
  CATCH_CHECK(M(2, 0) == 6.);
  CATCH_CHECK(M(2, 1) == 12.);
  CATCH_CHECK(M(2, 2) == 18.);
}
