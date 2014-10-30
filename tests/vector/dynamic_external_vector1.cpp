/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/dynamic_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE dynamic_external_vector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(array_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(data, 3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data(), &data[0]);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_assign)
{
  double av[3];
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(av, 3);
  v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_assign)
{
  double av[3];
  cml::vector<double, cml::external<>> v(av, 3);
  v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(write1)
{
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<>> v(data, 3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  v[0] = 1.;
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  double av[3];
  cml::vector<double, cml::external<>> v(av, 3);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_REQUIRE_THROW(
    (v = { 1., 2., 3., 4. }), cml::incompatible_vector_sizes);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
