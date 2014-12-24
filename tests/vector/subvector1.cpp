/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/subvector_node.h>

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/external.h>
#include <cml/vector/subvector.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE subvector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(sub1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(sub1)
{
  double av1[] = { 1., 2., 3. };
  cml::vector3d v1(av1);
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector3d v1(av1);
  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(sub1)
{
  cml::vectord v1 = { 1., 2., 3. };
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, -1);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  cml::vectord v1 = { 1., 2., 3. };
  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, -1);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(sub1)
{
  double av1[] = { 1., 2., 3. };
  cml::externald v1(av1, 3);
  auto xpr = cml::subvector(v1,0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, -1);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  double av1[] = { 1., 2., 3. };
  cml::externald v1(av1, 3);
  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, -1);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()


#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
BOOST_AUTO_TEST_SUITE(rv_from_this1)

BOOST_AUTO_TEST_CASE(sub1)
{
  typedef decltype(cml::vector3d().subvector(0)) node_type;
  BOOST_CHECK_EQUAL((std::is_rvalue_reference<
      typename node_type::sub_arg_type>::value), true);
  auto xpr = cml::vector3d(1., 2., 3.).subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  typedef decltype(v1.subvector(0)) node_type;
  BOOST_CHECK_EQUAL((std::is_lvalue_reference<
      typename node_type::sub_arg_type>::value), true);
  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()
#else
BOOST_AUTO_TEST_SUITE(rv_from_this1)

BOOST_AUTO_TEST_CASE(sub1)
{
  typedef cml::vector3d vector3_t;
  typedef decltype(vector3_t().subvector(0)) node_type;

  BOOST_CHECK_EQUAL((std::is_rvalue_reference<
      typename node_type::sub_arg_type>::value), true);
  BOOST_CHECK_EQUAL((std::is_same<
      typename node_type::sub_type, vector3_t>::value), true);

  auto xpr = vector3_t(1., 2., 3.).subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_CASE(sub2)
{
  typedef cml::vector3d vector3_t;
  vector3_t v1 = { 1., 2., 3. };
  typedef decltype(v1.subvector(0)) node_type;

  BOOST_CHECK_EQUAL((std::is_rvalue_reference<
      typename node_type::sub_arg_type>::value), true);
  BOOST_CHECK_EQUAL((std::is_same<
      typename node_type::sub_type, vector3_t>::value), true);

  auto xpr = v1.subvector(0);
  BOOST_REQUIRE_EQUAL(cml::int_c<decltype(xpr)::array_size>::value, 2);
  BOOST_REQUIRE_EQUAL(xpr.size(), 2);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 3.);
}

BOOST_AUTO_TEST_SUITE_END()
#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
