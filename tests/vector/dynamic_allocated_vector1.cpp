/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/dynamic_allocated.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE dynamic_allocated_vector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(alloc1)
{
  cml::vectord v(3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
}

BOOST_AUTO_TEST_CASE(resize1)
{
  cml::vectord v(3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  v.resize(5);
  BOOST_REQUIRE_EQUAL(v.size(), 5);
}

BOOST_AUTO_TEST_CASE(array_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vectord v(data);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_temp_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vectord v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_assign)
{
  double data[] = { 1., 2., 3. };
  cml::vectord v;
  v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(element_construct1)
{
  cml::vectord v(1.);
  BOOST_REQUIRE_EQUAL(v.size(), 1);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(element_construct2)
{
  cml::vectord v(1., 2.);
  BOOST_REQUIRE_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
}

BOOST_AUTO_TEST_CASE(element_construct3)
{
  cml::vectord v(1., 2., 3.);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
  BOOST_CHECK_EQUAL(v[2], 3.);
}

BOOST_AUTO_TEST_CASE(element_construct4)
{
  cml::vectord v(1.,2.f,3,4U);
  BOOST_REQUIRE_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(combine_construct1)
{
  cml::vectord v(cml::vectord(1., 2., 3.), 4.);
  BOOST_REQUIRE_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
  BOOST_CHECK_EQUAL(v[2], 3.);
  BOOST_CHECK_EQUAL(v[3], 4.);
}

BOOST_AUTO_TEST_CASE(combine_construct2)
{
  cml::vectord v(cml::vectord(1., 2.), 3., 4.);
  BOOST_REQUIRE_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[0], 1.);
  BOOST_CHECK_EQUAL(v[1], 2.);
  BOOST_CHECK_EQUAL(v[2], 3.);
  BOOST_CHECK_EQUAL(v[3], 4.);
}

BOOST_AUTO_TEST_CASE(list_construct)
{
  cml::vectord v { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_temp_construct)
{
  cml::vectord v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(write1)
{
  cml::vectord v(3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  v[0] = 1.;
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vectord v;
  BOOST_REQUIRE_EQUAL(v.size(), 0);
  BOOST_CHECK_NO_THROW((v = { 1., 2., 3., 4. }));
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
