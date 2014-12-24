/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

// Make sure the main header compiles cleanly:
#include <cml/vector/cross.h>

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE cross1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(cross1)
{
  cml::vector3d v1 = { 1., 1., 1. };
  cml::vector3d v2 = { 2., 2., 2. };

  typedef decltype(cml::cross(v1,v2)) cross_type;
  static_assert(
    std::is_same<cross_type::size_tag,cml::fixed_size_tag>::value,
    "got wrong size_tag from cross()");

  auto v = cml::cross(v1,v2);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], 0.);
  BOOST_CHECK_EQUAL(v[1], 0.);
  BOOST_CHECK_EQUAL(v[2], 0.);
}

BOOST_AUTO_TEST_CASE(cross2)
{
  cml::vectord v1(1., 2., 3.);
  cml::vector3d v2 (3., 2., 1.);

  typedef decltype(cml::cross(v1,v2)) cross_type;
  static_assert(
    std::is_same<cross_type::size_tag,cml::fixed_size_tag>::value,
    "got wrong size_tag from cross()");

  auto v = cml::cross(v1,v2);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -4.);
  BOOST_CHECK_EQUAL(v[1],  8.);
  BOOST_CHECK_EQUAL(v[2], -4.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::vectord v1(2);
  BOOST_CHECK_THROW(cml::cross(v1,v1), cml::vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  cml::vectord v1(2,3);
  cml::vector3d v2(2,3,3);
  BOOST_CHECK_THROW(cml::cross(v1,v2), cml::vector_size_error);
}

BOOST_AUTO_TEST_CASE(size_check3)
{
  cml::vector3d v1(2,3,3);
  cml::vectord v2(2,3);
  BOOST_CHECK_THROW(cml::cross(v1,v2), cml::vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
