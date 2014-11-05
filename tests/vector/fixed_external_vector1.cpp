/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE fixed_external_vector1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(array_construct)
{
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(data);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data(), &data[0]);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(array_assign)
{
  double av[3];
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(av);
  v = data;
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(list_assign)
{
  double av[3];
  cml::vector<double, cml::external<3>> v(av);
  v = { 1., 2., 3. };
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(write1)
{
  double data[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v(data);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  v[0] = 1.;
  BOOST_CHECK_EQUAL(v.data()[0], 1.);
  BOOST_CHECK_EQUAL(v[0], 1.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  double av[3];
  cml::vector<double, cml::external<3>> v(av);
  BOOST_REQUIRE_EQUAL(v.size(), 3);
  BOOST_CHECK_THROW(
    (v = { 1., 2., 3., 4. }), cml::incompatible_vector_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
