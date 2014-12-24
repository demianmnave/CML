/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/unary_node.h>
#include <cml/vector/unary_ops.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_unary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(unary_types1)
{
  typedef cml::vector3d vector_type;
  {
    BOOST_CHECK(cml::is_statically_polymorphic<vector_type>::value);
  }
  {
    auto xpr = - vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    auto xpr = + vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    vector_type M;
    auto xpr = - M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::sub_arg_type>::value
      );
  }
  {
    vector_type M;
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
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w;
  w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w;
  w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::vector3d v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);

  cml::vector3d w;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);

  double aw[3];
  cml::external3d w(aw);

  w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);

  double aw[3];
  cml::external3d w(aw);

  w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  BOOST_REQUIRE_EQUAL(v.size(), 3);

  double aw[3];
  cml::external3d w(aw);
  BOOST_REQUIRE_EQUAL(w.size(), 3);

  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av,3);

  double aw[3];
  cml::externald w(aw,3);

  w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av,3);

  double aw[3];
  cml::externald w(aw,3);

  w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av,3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);

  double aw[3];
  cml::externald w(aw,3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);

  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(unary_minus1)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w;
  w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_minus2)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w = - v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], - 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus1)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w;
  w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(unary_plus2)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w = + v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_CASE(double_negate1)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  auto xpr = - (-v);
  w = xpr;
  BOOST_CHECK_EQUAL(w[0], 1.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
