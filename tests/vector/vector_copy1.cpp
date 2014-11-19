/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/external.h>
#include <cml/vector/comparison.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_copy1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(copy_temp_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  cml::vector<double, cml::fixed<3>> w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  cml::vector<double, cml::fixed<3>> w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  cml::vector<double, cml::fixed<3>> w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  cml::vector<double, cml::fixed<3>> w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> w;
  w = cml::vector<double, cml::fixed<3>>(1., 2., 3.);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<3>> w(aw);
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  cml::vector<double, cml::external<3>> w;
#else
  cml::vector<double, cml::external<3>> w(nullptr);
  // Note: this allows the test to go through, but is not recommended for
  // user code on compilers that do not support rvalue references from
  // this.
#endif
  double at[3] = { 1., 2., 3. };
  w = cml::vector<double, cml::external<3>>(at);
  BOOST_REQUIRE(w.data() == &at[0]);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<>> w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  double aw[3];
  cml::vector<double, cml::external<>> w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  double aw[3];
  cml::vector<double, cml::external<>> w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  double aw[3];
  cml::vector<double, cml::external<>> w(aw, 3);
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  cml::vector<double, cml::external<>> w;
#else
  cml::vector<double, cml::external<>> w(nullptr, 0);
  // Note: this allows the test to go through, but is not recommended for
  // user code on compilers that do not support rvalue references from
  // this.
#endif
  double at[3] = { 1., 2., 3. };
  w = cml::vector<double, cml::external<>>(at, 3);
  BOOST_REQUIRE(w.data() == &at[0]);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(copy_temp_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  cml::vector<double, cml::dynamic<>> w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  cml::vector<double, cml::dynamic<>> w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w = v; 
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  cml::vector<double, cml::dynamic<>> w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  cml::vector<double, cml::dynamic<>> w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vector<double, cml::dynamic<>> v = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w;
  w = v; 
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector<double, cml::fixed<3>> v = { 1., 2., 3. };
  cml::vector<double, cml::dynamic<>> w;
  w = cml::vector<double, cml::dynamic<>>(1., 2., 3.);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
