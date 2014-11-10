/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>
#include <type_traits>
#include <cml/common/compiler.h>

/* Testing headers: */
#define BOOST_TEST_MODULE rv_from_this1
#include <boost/test/unit_test.hpp>

struct rv_from_this {
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  rv_from_this&& mover() &&;
#endif
  rv_from_this& refer() __CML_REF;
};

BOOST_AUTO_TEST_CASE(rv_from_this1)
{
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  BOOST_CHECK_EQUAL(true,
    (std::is_same<decltype(rv_from_this().mover()), rv_from_this&&>::value));
  BOOST_REQUIRE_EQUAL(true, (std::is_same<
      decltype(std::declval<rv_from_this&>().refer()), rv_from_this&>::value));
#else
  BOOST_REQUIRE_EQUAL(true, (std::is_same<
      decltype(std::declval<rv_from_this&>().refer()), rv_from_this&>::value));
#endif
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
