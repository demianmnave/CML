/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/vector/scalar_node.h>
#include <cml/vector/scalar_ops.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_scalar_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(scalar_types1)
{
  typedef cml::vector3d vector_type;
  {
    auto xpr = vector_type()*int();
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
    auto xpr = int()*vector_type();
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
    auto xpr = vector_type()/int();
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
    auto xpr = vector_type()*v;
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
    auto xpr = v*vector_type();
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
    auto xpr = vector_type()/v;
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
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d w;
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector3d v1 = { 2., 4., 6. };
  cml::vector3d w;
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::vector3d v1 = { 2., 4., 6. };
  cml::vector3d w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::vector3d w;
  w = (cml::vector3d(1.,2.,3.) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  double av1[] = { 1., 2., 3. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d w(aw);
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double av1[] = { 2., 4., 6. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d w(aw);
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double av1[] = { 1., 2., 3. };
  cml::external3d v1(av1);
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double av1[] = { 1., 2., 3. };
  cml::external3d w;
  w = (cml::external3d(av1) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w.data(), &av1[0]);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
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
  double av1[] = { 1., 2., 3. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald w(aw,3);
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  double av1[] = { 2., 4., 6. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald w(aw,3);
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  double av1[] = { 1., 2., 3. };
  cml::externald v1(av1,3);
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  double av1[] = { 1., 2., 3. };
  cml::externald w;
  w = (cml::externald(av1,3) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w.data(), &av1[0]);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
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
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord w;
  w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord w = 2.*v1;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vectord v1 = { 2., 4., 6. };
  cml::vectord w;
  w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::vectord v1 = { 2., 4., 6. };
  cml::vectord w = v1/2.;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
  BOOST_CHECK_EQUAL(w[1], 2.);
  BOOST_CHECK_EQUAL(w[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::vectord v1 = { 1., 2., 3. };
  v1 *= 2;
  BOOST_REQUIRE_EQUAL(v1.size(), 3);
  BOOST_CHECK_EQUAL(v1[0], 2.);
  BOOST_CHECK_EQUAL(v1[1], 4.);
  BOOST_CHECK_EQUAL(v1[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::vectord w;
  w = (cml::vector<double, cml::dynamic<>>(1.,2.,3.) *= 2);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 2.);
  BOOST_CHECK_EQUAL(w[1], 4.);
  BOOST_CHECK_EQUAL(w[2], 6.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
