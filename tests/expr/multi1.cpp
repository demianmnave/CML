/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <iostream>
#include <cml/vector.h>
#include <cml/matrix.h>

#include "catch_runner.h"

CATCH_TEST_CASE("aliasing-effects1")
{
  cml::vector<double,cml::fixed<1>> m = {2.};
  cml::vector<double,cml::fixed<1>> p = {3.};

  CATCH_SECTION("Expression affected by aliasing")
  {
    const auto x = m + p;
    CATCH_CHECK(x[0] == Approx(5.).margin(cml::epsilon<double>()));

    /* x is changed because m is changed: */
    m = p;
    CATCH_CHECK(x[0] == Approx(6.).margin(cml::epsilon<double>()));
  }

  CATCH_SECTION("Expression protected from aliasing")
  {
    const auto x = cml::vector{m} + p;
    CATCH_CHECK(x[0] == Approx(5.).margin(cml::epsilon<double>()));

    /* x is changed because m is changed: */
    m = p;
    CATCH_CHECK(x[0] == Approx(5.).margin(cml::epsilon<double>()));
  }
}