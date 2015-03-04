/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/quaternion/unary_node.h>
#include <cml/quaternion/unary_ops.h>

#include <cml/quaternion/fixed.h>
#include <cml/quaternion/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE quaternion_unary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(unary_types1)
{
  typedef cml::quaterniond quaternion_type;
  {
    BOOST_CHECK(cml::is_statically_polymorphic<quaternion_type>::value);
  }
  {
    auto xpr = - quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    auto xpr = + quaternion_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = - M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    quaternion_type M;
    auto xpr = + M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
}

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r;
  r = - q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], - 1.);
  BOOST_CHECK_EQUAL(r[1], - 2.);
  BOOST_CHECK_EQUAL(r[2], - 3.);
  BOOST_CHECK_EQUAL(r[3], - 4.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = - q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], - 1.);
  BOOST_CHECK_EQUAL(r[1], - 2.);
  BOOST_CHECK_EQUAL(r[2], - 3.);
  BOOST_CHECK_EQUAL(r[3], - 4.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r;
  r = + q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], + 1.);
  BOOST_CHECK_EQUAL(r[1], + 2.);
  BOOST_CHECK_EQUAL(r[2], + 3.);
  BOOST_CHECK_EQUAL(r[3], + 4.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = + q;
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], + 1.);
  BOOST_CHECK_EQUAL(r[1], + 2.);
  BOOST_CHECK_EQUAL(r[2], + 3.);
  BOOST_CHECK_EQUAL(r[3], + 4.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::quaterniond q = { 1., 2., 3., 4. };
  cml::quaterniond r = - (- q);
  BOOST_REQUIRE_EQUAL(r.size(), 4);
  BOOST_CHECK_EQUAL(r[0], 1.);
  BOOST_CHECK_EQUAL(r[1], 2.);
  BOOST_CHECK_EQUAL(r[2], 3.);
  BOOST_CHECK_EQUAL(r[3], 4.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
