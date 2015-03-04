/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/scalar_node.h>
#include <cml/quaternion/scalar_ops.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_scalar_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(scalar_types1)
{
  typedef cml::quaterniond quaternion_type;
  {
    auto xpr = quaternion_type()*int();
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
    auto xpr = int()*quaternion_type();
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
    auto xpr = quaternion_type()/int();
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
    auto xpr = quaternion_type()*v;
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
    auto xpr = v*quaternion_type();
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
    auto xpr = quaternion_type()/v;
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
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r;
  r = 2.*q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], 2.);
  BOOST_CHECK_EQUAL(r[1], 4.);
  BOOST_CHECK_EQUAL(r[2], 6.);
  BOOST_CHECK_EQUAL(r[3], 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = 2.*q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], 2.);
  BOOST_CHECK_EQUAL(r[1], 4.);
  BOOST_CHECK_EQUAL(r[2], 6.);
  BOOST_CHECK_EQUAL(r[3], 8.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::quaterniond q = { 2., 4., 6., 8. };
  cml::quaterniond r;
  r = q/2;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], 1.);
  BOOST_CHECK_EQUAL(r[1], 2.);
  BOOST_CHECK_EQUAL(r[2], 3.);
  BOOST_CHECK_EQUAL(r[3], 4.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  cml::quaterniond q = { 2., 4., 6., 8. };
  cml::quaterniond r = q/2;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], 1.);
  BOOST_CHECK_EQUAL(r[1], 2.);
  BOOST_CHECK_EQUAL(r[2], 3.);
  BOOST_CHECK_EQUAL(r[3], 4.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  q *= 2;
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_EQUAL(q[0], 2.);
  BOOST_CHECK_EQUAL(q[1], 4.);
  BOOST_CHECK_EQUAL(q[2], 6.);
  BOOST_CHECK_EQUAL(q[3], 8.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply_assign2)
{
  cml::quaterniond q;
  q = (cml::quaterniond(1., 2., 3., 4.) *= 2);
  BOOST_REQUIRE_EQUAL(q.size(), 4);
  BOOST_CHECK_EQUAL(q[0], 2.);
  BOOST_CHECK_EQUAL(q[1], 4.);
  BOOST_CHECK_EQUAL(q[2], 6.);
  BOOST_CHECK_EQUAL(q[3], 8.);
}

BOOST_AUTO_TEST_SUITE_END()


// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
