/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/matrix/binary_node.h>
#include <cml/matrix/binary_ops.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_binary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(binary_types1)
{
  typedef cml::matrix<double, cml::fixed<2,2>> matrix_type;
  {
    BOOST_CHECK(!cml::is_statically_polymorphic<int>::value);
    BOOST_CHECK(cml::is_statically_polymorphic<matrix_type>::value);
  }
  {
    auto xpr = matrix_type() + matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    auto xpr = matrix_type() - matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M;
    auto xpr = matrix_type() + M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M;
    auto xpr = M + matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M;
    auto xpr = matrix_type() - M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M;
    auto xpr = M - matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M1, M2;
    auto xpr = M1 + M2;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    matrix_type M1, M2;
    auto xpr = M1 - M2;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
}

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::fixed<2,2>> M;
  M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::fixed<2,2>> M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::fixed<2,2>> M;
  M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::fixed<2,2>> M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M3(
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::fixed<2,2>> M;
  M = M1 + M2 + M3;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M3(
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::fixed<2,2>> M = M1 + M2 + M3;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M3(
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::fixed<2,2>> M;
  M = M1 + (M3 - M2);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::fixed<2,2>> M2(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M3(
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::fixed<2,2>> M = M1 + (M3 - M2);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M(
    1., 2.,
    3., 4.
    );
  M -= M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::matrix<double, cml::fixed<2,2>> M1(
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::fixed<2,2>> M(
    1., 2.,
    3., 4.
    );

  M += M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M2(aM2);

  double data[4];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M2(aM2);

  double data[4];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M2(aM2);

  double aM3[] = {
     9., 10.,
    11., 12.
  };
  cml::matrix<double, cml::external<2,2>> M3(aM3);

  double data[4];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = M1 + M2 + M3;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M2(aM2);

  double aM3[] = {
     9., 10.,
    11., 12.
  };
  cml::matrix<double, cml::external<2,2>> M3(aM3);

  double data[4];
  cml::matrix<double, cml::external<2,2>> M(data);
  M = M1 + (M3 - M2);

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  double aM1[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M(data);
  M -= M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  double aM1[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<2,2>> M1(aM1);

  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<2,2>> M(data);
  M += M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M2(aM2, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M2(aM2, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M2(aM2, 2,2);

  double aM3[] = {
     9., 10.,
    11., 12.
  };
  cml::matrix<double, cml::external<>> M3(aM3, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = M1 + M2 + M3;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double aM1[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double aM2[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M2(aM2, 2,2);

  double aM3[] = {
     9., 10.,
    11., 12.
  };
  cml::matrix<double, cml::external<>> M3(aM3, 2,2);

  double data[2][2];
  cml::matrix<double, cml::external<>> M(data);
  M = M1 + (M3 - M2);

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  double aM1[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M(data, 2,2);
  M -= M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  double aM1[] = {
    5., 6.,
    7., 8.
  };
  cml::matrix<double, cml::external<>> M1(aM1, 2,2);

  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::matrix<double, cml::external<>> M(data, 2,2);
  M += M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::dynamic<>> M;
  M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::dynamic<>> M = M1 - M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::dynamic<>> M;
  M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );

  cml::matrix<double, cml::dynamic<>> M = M1 + M2;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M3(
    2,2,
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::dynamic<>> M;
  M = M1 + M2 + M3;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M3(
    2,2,
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::dynamic<>> M = M1 + M2 + M3;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 15.);
  BOOST_CHECK_EQUAL(M(0,1), 18.);
  BOOST_CHECK_EQUAL(M(1,0), 21.);
  BOOST_CHECK_EQUAL(M(1,1), 24.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M3(
    2,2,
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::dynamic<>> M;
  M = M1 + (M3 - M2);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrix<double, cml::dynamic<>> M2(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M3(
    2,2,
     9., 10.,
    11., 12.
    );
  cml::matrix<double, cml::dynamic<>> M = M1 + (M3 - M2);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 5.);
  BOOST_CHECK_EQUAL(M(0,1), 6.);
  BOOST_CHECK_EQUAL(M(1,0), 7.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M(
    2,2,
    1., 2.,
    3., 4.
    );
  M -= M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), -4.);
  BOOST_CHECK_EQUAL(M(0,1), -4.);
  BOOST_CHECK_EQUAL(M(1,0), -4.);
  BOOST_CHECK_EQUAL(M(1,1), -4.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::matrix<double, cml::dynamic<>> M1(
    2,2,
    5., 6.,
    7., 8.
    );
  cml::matrix<double, cml::dynamic<>> M(
    2,2,
    1., 2.,
    3., 4.
    );

  M += M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 6.);
  BOOST_CHECK_EQUAL(M(0,1), 8.);
  BOOST_CHECK_EQUAL(M(1,0), 10.);
  BOOST_CHECK_EQUAL(M(1,1), 12.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
