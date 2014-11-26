/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/common/type_util.h>

/* Testing headers: */
#define BOOST_TEST_MODULE type_util1
#include <boost/test/unit_test.hpp>

struct scoop1 { const scoop1& actual() const; };
struct scoop2 { scoop2& actual() const; };
struct scoop3 { scoop3& actual(); };
struct scoop4 { const scoop4& actual(); };

template<class T> struct scoop_base { T& actual(); };
struct scoop5 : scoop_base<scoop5> {};

BOOST_AUTO_TEST_CASE(is_statically_polymorphic1)
{
  BOOST_CHECK(!cml::is_statically_polymorphic<int>::value);
}

BOOST_AUTO_TEST_CASE(is_statically_polymorphic2)
{
  BOOST_CHECK(cml::is_statically_polymorphic<scoop1>::value);
  BOOST_CHECK(cml::is_statically_polymorphic<scoop2>::value);
  BOOST_CHECK(cml::is_statically_polymorphic<scoop3>::value);
  BOOST_CHECK(cml::is_statically_polymorphic<scoop4>::value);
}

BOOST_AUTO_TEST_CASE(actual_type_of1)
{
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<int>, int>::value));
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<int&>, int>::value));
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<const int&>, int>::value));
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<int&&>, int>::value));
}

BOOST_AUTO_TEST_CASE(actual_type_of2)
{
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<scoop5>, scoop5>::value));
  BOOST_CHECK((std::is_same<
      cml::actual_type_of_t<scoop_base<scoop5>>, scoop5>::value));
}

BOOST_AUTO_TEST_CASE(actual_operand_type_of1)
{
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      int&>, int&>::value));
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      int const&>, int const&>::value));
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      int&&>, int&&>::value));
}

BOOST_AUTO_TEST_CASE(actual_operand_type_of2)
{
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      scoop_base<scoop5>&>, scoop5&>::value));
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      scoop_base<scoop5> const&>, scoop5 const&>::value));
  BOOST_CHECK((std::is_same<cml::actual_operand_type_of_t<
      scoop_base<scoop5>&&>, scoop5&&>::value));
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
