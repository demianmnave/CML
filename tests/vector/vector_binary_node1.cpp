/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/fixed_external.h>
#include <cml/vector/dynamic_external.h>
#include <cml/vector/dynamic.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_binary_node1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> w;
  w = v1 - v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> w = v1 - v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> w;
  w = v1 + v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> w = v1 + v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 5.);
  BOOST_CHECK_EQUAL(w[1], 7.);
  BOOST_CHECK_EQUAL(w[2], 9.);
}

BOOST_AUTO_TEST_CASE(multiple_plus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> v3 = { 7., 8., 9. };
  cml::vector<double, cml::fixed<3>> w;
  w = v1 + (v2 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(multiple_plus2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> v3 = { 7., 8., 9. };
  cml::vector<double, cml::fixed<3>> w = v1 + (v2 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 12.);
  BOOST_CHECK_EQUAL(w[1], 15.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(mixed_op1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> v3 = { 7., 8., 9. };
  cml::vector<double, cml::fixed<3>> w;
  w = v2 - (v1 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(mixed_op2)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  cml::vector<double, cml::fixed<3>> v3 = { 7., 8., 9. };
  cml::vector<double, cml::fixed<3>> w = v2 - (v1 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_CASE(assign_minus1)
{
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v = { 4., 5., 6. };
  BOOST_CHECK_EQUAL(w.size(), 3);
  w -= v;
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(assign_plus1)
{
  cml::vector<double, cml::fixed<3>> w = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v = { 4., 5., 6. };
  w += v;
  BOOST_CHECK_EQUAL(w.size(), 3);
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
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> v2(av2);
  cml::vector<double, cml::external<3>> w(aw);
  w = v1 - v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -3.);
  BOOST_CHECK_EQUAL(w[1], -3.);
  BOOST_CHECK_EQUAL(w[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  double av1[] = { 1., 2., 3. };
  double av2[] = { 4., 5., 6. };
  double aw[3];
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> v2(av2);
  cml::vector<double, cml::external<3>> w(aw);
  w = v1 + v2;
  BOOST_CHECK_EQUAL(w.size(), 3);
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
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> v2(av2);
  cml::vector<double, cml::external<3>> v3(av3);
  cml::vector<double, cml::external<3>> w(aw);
  w = v1 + (v2 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
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
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::external<3>> v2(av2);
  cml::vector<double, cml::external<3>> v3(av3);
  cml::vector<double, cml::external<3>> w(aw);
  w = v2 - (v1 + v3);
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], -4.);
  BOOST_CHECK_EQUAL(w[1], -5.);
  BOOST_CHECK_EQUAL(w[2], -6.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_fixed_storage)

BOOST_AUTO_TEST_CASE(construct_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::fixed<3>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<3>> v4(av4);

  cml::vector<double, cml::fixed<3>> w = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::fixed<3>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<3>> v4(av4);

  cml::vector<double, cml::fixed<3>> w;
  w = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_temp_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::fixed<3>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<3>> v4(av4);

  auto xpr = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(sizeof(xpr), 32U);

  cml::vector<double, cml::fixed<3>> w;
  w = xpr;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(mixed_storage)

BOOST_AUTO_TEST_CASE(construct_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::dynamic<>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<>> v4(av4, 3);

  cml::vector<double, cml::fixed<3>> w = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::dynamic<>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<>> v4(av4, 3);

  cml::vector<double, cml::dynamic<>> w;
  w = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_CASE(assign_temp_xpr)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  double av2[] = {  7.,  8.,  9. };
  cml::vector<double, cml::external<3>> v2(av2);

  cml::vector<double, cml::dynamic<>> v3 = { 4., 5., 6. };
  double av4[] = { 10., 11., 12. };
  cml::vector<double, cml::external<>> v4(av4, 3);

  auto xpr = v1 + v2 - v3 + v4;
  BOOST_CHECK_EQUAL(sizeof(xpr), 32U);

  double aw[3];
  cml::vector<double, cml::external<>> w(aw, 3);
  w = xpr;
  BOOST_CHECK_EQUAL(w.size(), 3);
  BOOST_CHECK_EQUAL(w[0], 14.);
  BOOST_CHECK_EQUAL(w[1], 16.);
  BOOST_CHECK_EQUAL(w[2], 18.);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
