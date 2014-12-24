/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/external.h>
#include <cml/vector/comparison.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_copy1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(copy_temp_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  cml::vector3d w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  cml::vector3d w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vector3d w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  cml::vector3d w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  cml::vector3d w;
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vector3d w;
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vector3d w;
  w = cml::vector3d(1., 2., 3.);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  double aw[3];
  cml::external3d w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  double aw[3];
  cml::external3d w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  double aw[3];
  cml::external3d w(aw);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  double aw[3];
  cml::external3d w(aw);
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector3d v = { 1., 2., 3. };
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  cml::external3d w;
#else
  cml::external3d w(nullptr);
  // Note: this allows the test to go through, but is not recommended for
  // user code on compilers that do not support rvalue references from
  // this.
#endif
  double at[3] = { 1., 2., 3. };
  w = cml::external3d(at);
  BOOST_REQUIRE(w.data() == &at[0]);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  double aw[3];
  cml::externald w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  double aw[3];
  cml::externald w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  double aw[3];
  cml::externald w(aw, 3);
  w = v;
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  double aw[3];
  cml::externald w(aw, 3);
  w = v; 
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector3d v = { 1., 2., 3. };
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  cml::externald w;
#else
  cml::externald w(nullptr, 0);
  // Note: this allows the test to go through, but is not recommended for
  // user code on compilers that do not support rvalue references from
  // this.
#endif
  double at[3] = { 1., 2., 3. };
  w = cml::externald(at, 3);
  BOOST_REQUIRE(w.data() == &at[0]);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(copy_temp_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vectord w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  cml::vectord w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  cml::vectord w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_temp_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w = v; 
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vectord w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_fixed_external)
{
  double av[3] = { 1., 2., 3. };
  cml::external3d v(av);
  cml::vectord w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic_external)
{
  double av[3] = { 1., 2., 3. };
  cml::externald v(av, 3);
  cml::vectord w;
  w = v;
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(copy_assign_dynamic)
{
  cml::vectord v = { 1., 2., 3. };
  cml::vectord w;
  w = v; 
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_CASE(move_assign)
{
  cml::vector3d v = { 1., 2., 3. };
  cml::vectord w;
  w = cml::vectord(1., 2., 3.);
  BOOST_REQUIRE_EQUAL(w.size(), 3);
  BOOST_CHECK(v == w);
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
