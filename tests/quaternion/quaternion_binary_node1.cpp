/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/binary_node.h>
#include <cml/quaternion/binary_ops.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_binary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(binary_types1)
{
  typedef cml::quaterniond quaternion_type;
  {
    BOOST_CHECK(cml::is_statically_polymorphic<quaternion_type>::value);
  }
  {
    auto xpr = quaternion_type() + quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    auto xpr = quaternion_type() - quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = quaternion_type() + M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = M + quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = quaternion_type() - M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = M - quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    quaternion_type M1, M2;
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
    quaternion_type M1, M2;
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
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = { 4., 5., 6., 7. };
  cml::quaterniond w;
  w = q - r;
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
  BOOST_CHECK_EQUAL(w[3], -3.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = { 4., 5., 6., 7. };
  cml::quaterniond w = q - r;
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
  BOOST_CHECK_EQUAL(w[3], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = { 4., 5., 6., 7. };
  cml::quaterniond w;
  w = q + r;
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
  BOOST_CHECK_EQUAL(w[3], 11.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = { 4., 5., 6., 7. };
  cml::quaterniond w = q + r;
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
  BOOST_CHECK_EQUAL(w[3], 11.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::quaterniond q = { 1., 2., 3., 1. };
  cml::quaterniond r = { 4., 5., 6., 2. };
  cml::quaterniond s = { 7., 8., 9., 3. };
  cml::quaterniond w;
  w = q + (r + s);
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
  BOOST_CHECK_EQUAL(w[3], 6.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::quaterniond q = { 1., 2., 3., 1. };
  cml::quaterniond r = { 4., 5., 6., 2. };
  cml::quaterniond s = { 7., 8., 9., 3. };
  cml::quaterniond w = q + (r + s);
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
  BOOST_CHECK_EQUAL(w[3], 6.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::quaterniond q = { 1., 2., 3., 1. };
  cml::quaterniond r = { 4., 5., 6., 2. };
  cml::quaterniond s = { 7., 8., 9., 3. };
  cml::quaterniond w;
  w = r - (q + s);
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
  BOOST_CHECK_EQUAL(w[3], -2.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::quaterniond q = { 1., 2., 3., 1. };
  cml::quaterniond r = { 4., 5., 6., 2. };
  cml::quaterniond s = { 7., 8., 9., 3. };
  cml::quaterniond w = r - (q + s);
  BOOST_REQUIRE_EQUAL(w.size(), 4);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
  BOOST_CHECK_EQUAL(w[3], -2.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::quaterniond w = { 1., 2., 3., 4. };
  cml::quaterniond v = { 4., 5., 6., 7. };
  w -= v;
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
  BOOST_CHECK_EQUAL(w[3], -3.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::quaterniond w = { 1., 2., 3., 4. };
  cml::quaterniond v = { 4., 5., 6., 7. };
  w += v;
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
  BOOST_CHECK_EQUAL(w[3], 11.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
