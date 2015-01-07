/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/matrix/scalar_node.h>
#include <cml/matrix/scalar_ops.h>

#include <cml/matrix.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_scalar_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(scalar_types1)
{
  typedef cml::matrix22d matrix_type;
  {
    auto xpr = matrix_type()*int();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
  {
    auto xpr = int()*matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
  {
    auto xpr = matrix_type()/int();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
  {
    double v = 0.;
    auto xpr = matrix_type()*v;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
  {
    double v = 0.;
    auto xpr = v*matrix_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
  {
    double v = 0.;
    auto xpr = matrix_type()/v;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
    BOOST_CHECK(
      std::is_arithmetic<typename xpr_type::right_type>::value
      );
  }
}

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::matrix22d M1(
    1., 2.,
    3., 4.
    );
  cml::matrix22d M;
  M = 2.*M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::matrix22d M1(
    1., 2.,
    3., 4.
    );
  cml::matrix22d M = 2.*M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::matrix22d M1(
    2., 4.,
    6., 8.
    );
  cml::matrix22d M;
  M = M1/2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::matrix22d M1(
    2., 4.,
    6., 8.
    );
  cml::matrix22d M = M1/2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::matrix22d M(
    1., 2.,
    3., 4.
    );
  M *= 2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::matrix22d M;
  M = (cml::matrix22d(
      1., 2.,
      3., 4.
      ) *= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign1)
{
  cml::matrix22d M(
    2., 4.,
    6., 8.
    );
  M /= 2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign2)
{
  cml::matrix22d M;
  M = (cml::matrix22d(
    2., 4.,
    6., 8.
    ) /= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double aM[] = {
    1., 2.,
    3., 4.
  };
  cml::external22d M1(aM);

  double data[2][2];
  cml::external22d M(data);
  M = 2.*M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double aM[] = {
    2., 4.,
    6., 8.
  };
  cml::external22d M1(aM);

  double data[2][2];
  cml::external22d M(data);
  M = M1/2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::external22d M(data);
  M *= 2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double aM[] = {
    1., 2.,
    3., 4.
  };
  cml::external22d M;
  M = (cml::external22d(aM) *= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
#else
  BOOST_WARN_MESSAGE(
    BOOST_IS_DEFINED(CML_HAS_RVALUE_REFERENCE_FROM_THIS),
    "Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign1)
{
  double data[] = {
    2., 4.,
    6., 8.
  };
  cml::external22d M(data);
  M /= 2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double aM[] = {
    2., 4.,
    6., 8.
  };
  cml::external22d M;
  M = (cml::external22d(aM) /= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
#else
  BOOST_WARN_MESSAGE(
    BOOST_IS_DEFINED(CML_HAS_RVALUE_REFERENCE_FROM_THIS),
    "Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double aM[] = {
    1., 2.,
    3., 4.
  };
  cml::externalmnd M1(aM, 2,2);

  double data[2][2];
  cml::externalmnd M(data);
  M = 2.*M1;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double aM[] = {
    2., 4.,
    6., 8.
  };
  cml::externalmnd M1(aM, 2,2);

  double data[2][2];
  cml::externalmnd M(data);
  M = M1/2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double data[] = {
    1., 2.,
    3., 4.
  };
  cml::externalmnd M(data, 2,2);
  M *= 2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double aM[] = {
    1., 2.,
    3., 4.
  };
  cml::externalmnd M;
  M = (cml::externalmnd(aM, 2,2) *= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
#else
  BOOST_WARN_MESSAGE(
    BOOST_IS_DEFINED(CML_HAS_RVALUE_REFERENCE_FROM_THIS),
    "Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign1)
{
  double data[] = {
    2., 4.,
    6., 8.
  };
  cml::externalmnd M(2,2, data);
  M /= 2.;

  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double aM[] = {
    2., 4.,
    6., 8.
  };
  cml::externalmnd M;
  M = (cml::externalmnd(2,2, aM) /= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
#else
  BOOST_WARN_MESSAGE(
    BOOST_IS_DEFINED(CML_HAS_RVALUE_REFERENCE_FROM_THIS),
    "Assignment to temporary external vectors not supported");
#endif
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::matrixd M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrixd M;
  M = 2.*M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::matrixd M1(
    2,2,
    1., 2.,
    3., 4.
    );
  cml::matrixd M = 2.*M1;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::matrixd M1(
    2,2,
    2., 4.,
    6., 8.
    );
  cml::matrixd M;
  M = M1/2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::matrixd M1(
    2,2,
    2., 4.,
    6., 8.
    );
  cml::matrixd M = M1/2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::matrixd M(
    2,2,
    1., 2.,
    3., 4.
    );
  M *= 2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::matrixd M;
  M = (cml::matrixd(
      2,2,
      1., 2.,
      3., 4.
      ) *= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 2.);
  BOOST_CHECK_EQUAL(M(0,1), 4.);
  BOOST_CHECK_EQUAL(M(1,0), 6.);
  BOOST_CHECK_EQUAL(M(1,1), 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign1)
{
  cml::matrixd M(
    2,2,
    2., 4.,
    6., 8.
    );
  M /= 2.;
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide_assign2)
{
  cml::matrixd M;
  M = (cml::matrixd(
      2,2,
      2., 4.,
      6., 8.
      ) /= 2.);
  BOOST_REQUIRE_EQUAL(M.rows(), 2);
  BOOST_REQUIRE_EQUAL(M.cols(), 2);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(0,1), 2.);
  BOOST_CHECK_EQUAL(M(1,0), 3.);
  BOOST_CHECK_EQUAL(M(1,1), 4.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
