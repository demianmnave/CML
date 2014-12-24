/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE fixed_compiled_vector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(array_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vector3d v(data);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_temp_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vector3d v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(element_construct1)
{
  cml::vector3d v(1., 0., 0.);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 0.);
  BOOST_CHECK_EQUAL(v[2], 0.);
}

BOOST_AUTO_TEST_CASE(element_construct2)
{
  cml::vector3d v(1., 2., 0.);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
  BOOST_CHECK_EQUAL(v[2], 0.);
}

BOOST_AUTO_TEST_CASE(element_construct3)
{
  cml::vector3d v(1., 2., 3.);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
  BOOST_CHECK_EQUAL(v[2], 3.);
}

BOOST_AUTO_TEST_CASE(element_construct4)
{
  cml::vector<double, cml::fixed<1>> v(1.);
  BOOST_REQUIRE_EQUAL(v.size(), 1);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(element_construct5)
{
  cml::vector4d v(1.,2.f,3,4U);
  BOOST_REQUIRE_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_assign)
{
  double data[] = { 1., 2., 3. };
  cml::vector3d v;
  v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_construct)
{
  cml::vector3d v { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_temp_construct)
{
  cml::vector3d v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_assign)
{
  cml::vector3d v;
  v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(write1)
{
  cml::vector3d v;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  v[0] = 1.;
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vector3d v;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_REQUIRE_THROW(
    (v = { 1., 2., 3., 4. }), cml::incompatible_vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
