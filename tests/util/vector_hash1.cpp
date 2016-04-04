/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>
#include <unordered_set>

// Make sure the main header compiles cleanly:
#include <cml/util/vector_hash.h>

#include <cml/vector/fixed.h>
#include <cml/vector/dynamic.h>
#include <cml/vector/external.h>
#include <cml/vector/types.h>
#include <cml/vector/comparison.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_hash1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixed)

typedef std::unordered_set<cml::vector3d>		vector3d_table;

BOOST_AUTO_TEST_CASE(table1)
{
  cml::vector3d p0(1.,2.,3.);
  vector3d_table table;
  BOOST_REQUIRE(table.insert(p0).second);
  BOOST_REQUIRE_EQUAL(table.size(), 1);
  BOOST_REQUIRE(table.find(p0) != table.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(fixed_external)

typedef std::unordered_set<cml::external3d>		external3d_table;

BOOST_AUTO_TEST_CASE(table1)
{
  double av0[] = { 1., 2., 3. };
  cml::external3d p0(av0);
  external3d_table table;
  BOOST_REQUIRE(table.insert(p0).second);
  BOOST_REQUIRE_EQUAL(table.size(), 1);
  BOOST_REQUIRE(table.find(p0) != table.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(dynamic)

typedef std::unordered_set<cml::vectord>		vectord_table;

BOOST_AUTO_TEST_CASE(table1)
{
  cml::vectord p0(1.,2.,3.);
  vectord_table table;
  BOOST_REQUIRE(table.insert(p0).second);
  BOOST_REQUIRE_EQUAL(table.size(), 1);
  BOOST_REQUIRE(table.find(p0) != table.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(dynamic_external)

typedef std::unordered_set<cml::externalnd>		externalnd_table;

BOOST_AUTO_TEST_CASE(table1)
{
  double av0[] = { 1., 2., 3. };
  cml::externalnd p0(av0, 3);
  externalnd_table table;
  BOOST_REQUIRE(table.insert(p0).second);
  BOOST_REQUIRE_EQUAL(table.size(), 1);
  BOOST_REQUIRE(table.find(p0) != table.end());
}

BOOST_AUTO_TEST_SUITE_END()


// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
