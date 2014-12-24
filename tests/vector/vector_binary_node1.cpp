/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/binary_node.h>
#include <cml/vector/binary_ops.h>

#include <cml/vector/fixed.h>
#include <cml/vector/external.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_binary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(binary_types1)
{
  typedef cml::vector3d vector_type;
  {
    BOOST_CHECK(cml::is_statically_polymorphic<vector_type>::value);
  }
  {
    auto xpr = vector_type() + vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    auto xpr = vector_type() - vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    vector_type M;
    auto xpr = vector_type() + M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    vector_type M;
    auto xpr = M + vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    vector_type M;
    auto xpr = vector_type() - M;
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    vector_type M;
    auto xpr = M - vector_type();
    typedef decltype(xpr) xpr_type;
    BOOST_CHECK(
      std::is_lvalue_reference<typename xpr_type::left_arg_type>::value
      );
    BOOST_CHECK(
      std::is_rvalue_reference<typename xpr_type::right_arg_type>::value
      );
  }
  {
    vector_type M1, M2;
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
    vector_type M1, M2;
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
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w;
  w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w;
  w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w;
  w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w;
  w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::vector3d v1 = { 1., 2., 3. };
  cml::vector3d v2 = { 4., 5., 6. };
  cml::vector3d v3 = { 7., 8., 9. };
  cml::vector3d w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::vector3d w = { 1., 2., 3. };
  cml::vector3d v = { 4., 5., 6. };
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  w -= v;
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::vector3d w = { 1., 2., 3. };
  cml::vector3d v = { 4., 5., 6. };
  w += v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d w(aw);
  w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d w(aw);
  w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d v3(av3);
  cml::external3d w(aw);
  w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::external3d v1(av1);
  cml::external3d v2(av2);
  cml::external3d v3(av3);
  cml::external3d w(aw);
  w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald v2(av2,3);
  cml::externald w(aw,3);
  w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald v2(av2,3);
  cml::externald w(aw,3);
  w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald v2(av2,3);
  cml::externald v3(av3,3);
  cml::externald w(aw,3);
  w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double av3[] = { 7., 8., 9. };
  double aw[3];
  cml::externald v1(av1,3);
  cml::externald v2(av2,3);
  cml::externald v3(av3,3);
  cml::externald w(aw,3);
  w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w;
  w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w = v1 - v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w;
  w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord w = v1 + v2;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w;
  w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w = v1 + (v2 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w;
  w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::vectord v1 = { 1., 2., 3. };
  cml::vectord v2 = { 4., 5., 6. };
  cml::vectord v3 = { 7., 8., 9. };
  cml::vectord w = v2 - (v1 + v3);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::vectord w = { 1., 2., 3. };
  cml::vectord v = { 4., 5., 6. };
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  w -= v;
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::vectord w = { 1., 2., 3. };
  cml::vectord v = { 4., 5., 6. };
  w += v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_fixed_storage)

BOOST_AUTO_TEST_CASE(construct_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vector3d v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::external3d v4(av4);

  cml::vector3d w = v1 + v2 - v3 + v4;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vector3d v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::external3d v4(av4);

  cml::vector3d w;
  w = v1 + v2 - v3 + v4;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_temp_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vector3d v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::external3d v4(av4);

  auto xpr = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(sizeof(xpr), 32U);

  cml::vector3d w;
  w = xpr;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_storage)

BOOST_AUTO_TEST_CASE(construct_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vectord v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::externald v4(av4, 3);

  cml::vector3d w = v1 + v2 - v3 + v4;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vectord v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::externald v4(av4, 3);

  cml::vectord w;
  w = v1 + v2 - v3 + v4;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_temp_xpr)
{
  cml::vector3d v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::external3d v2(av2);

  cml::vectord v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::externald v4(av4, 3);

  auto xpr = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(sizeof(xpr), 32U);

  double aw[3];
  cml::externald w(aw, 3);
  w = xpr;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
