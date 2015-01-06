/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <typeinfo>
#include <iostream>

// Make sure the main header compiles cleanly:
#include <cml/matrix/promotion.h>

#include <cml/matrix/fixed.h>
#include <cml/matrix/external.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE matrix_promotion1
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(fixed)

BOOST_AUTO_TEST_CASE(fixed1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrix22d, cml::matrix22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrix22d>::value));
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrix22d, cml::matrixd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrix22d, cml::external22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrix22d>::value));
}

BOOST_AUTO_TEST_CASE(external2)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrix22d, cml::externalmnd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic)

BOOST_AUTO_TEST_CASE(fixed1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrixd, cml::matrix22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrixd, cml::matrixd>				promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external1)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrixd, cml::external22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external2)
{
  typedef cml::matrix_inner_product_promote<
    cml::matrixd, cml::externalmnd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fixed_external)

BOOST_AUTO_TEST_CASE(fixed1)
{
  typedef cml::matrix_inner_product_promote<
    cml::external22d, cml::matrix22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrix22d>::value));
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  typedef cml::matrix_inner_product_promote<
    cml::external22d, cml::matrixd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external1)
{
  typedef cml::matrix_inner_product_promote<
    cml::external22d, cml::external22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrix22d>::value));
}

BOOST_AUTO_TEST_CASE(external2)
{
  typedef cml::matrix_inner_product_promote<
    cml::external22d, cml::externalmnd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(dynamic_external)

BOOST_AUTO_TEST_CASE(fixed1)
{
  typedef cml::matrix_inner_product_promote<
    cml::externalmnd, cml::matrix22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(dynamic1)
{
  typedef cml::matrix_inner_product_promote<
    cml::externalmnd, cml::matrixd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external1)
{
  typedef cml::matrix_inner_product_promote<
    cml::externalmnd, cml::external22d>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_CASE(external2)
{
  typedef cml::matrix_inner_product_promote<
    cml::externalmnd, cml::externalmnd>			promoter_type;
  typedef promoter_type::type				type;
  BOOST_CHECK((std::is_same<type, cml::matrixd>::value));
}

BOOST_AUTO_TEST_SUITE_END()

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
