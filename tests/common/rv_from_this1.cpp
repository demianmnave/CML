/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <iostream>
#include <type_traits>

/* Testing headers: */
#include "catch_runner.h"

struct rv_from_this
{
  rv_from_this&& mover() &&;
  rv_from_this& refer() &;
};

CATCH_TEST_CASE("rv_from_this1")
{
  CATCH_CHECK(true
    == (std::is_same<decltype(rv_from_this().mover()), rv_from_this&&>::value));
  CATCH_REQUIRE(true
    == (std::is_same<decltype(std::declval<rv_from_this&>().refer()),
      rv_from_this&>::value));
}
