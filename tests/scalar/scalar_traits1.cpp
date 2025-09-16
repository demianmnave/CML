/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

// Make sure the main header compiles cleanly:
#include <cml/scalar/traits.h>

/* Testing headers: */
#include "catch_runner.h"

using cml::scalar_traits;

CATCH_TEST_CASE("integral1")
{
  CATCH_CHECK(scalar_traits<int>::abs(1) == 1);
  CATCH_CHECK(scalar_traits<int>::abs(-1) == 1);
  CATCH_CHECK(scalar_traits<int>::fabs(1) == 1);
  CATCH_CHECK(scalar_traits<int>::fabs(-1) == 1);

  constexpr auto eps = scalar_traits<int>::epsilon();
  CATCH_CHECK(eps == 0);
}

CATCH_TEST_CASE("float1")
{
  CATCH_CHECK(scalar_traits<float>::abs(1.f) == 1.f);
  CATCH_CHECK(scalar_traits<float>::abs(-1.f) == 1.f);
  CATCH_CHECK(scalar_traits<float>::fabs(1.f) == 1.f);
  CATCH_CHECK(scalar_traits<float>::fabs(-1.f) == 1.f);

  constexpr auto eps = scalar_traits<float>::epsilon();
  CATCH_CHECK(eps == std::numeric_limits<float>::epsilon());

  constexpr auto sqrt_eps = scalar_traits<float>::sqrt_epsilon();
  CATCH_CHECK(sqrt_eps == 3.452669831e-4f);
}

CATCH_TEST_CASE("double1")
{
  CATCH_CHECK(scalar_traits<double>::abs(1.) == 1.);
  CATCH_CHECK(scalar_traits<double>::abs(-1.) == 1.);
  CATCH_CHECK(scalar_traits<double>::fabs(1.) == 1.);
  CATCH_CHECK(scalar_traits<double>::fabs(-1.) == 1.);

  constexpr auto eps = scalar_traits<double>::epsilon();
  CATCH_CHECK(eps == std::numeric_limits<double>::epsilon());

  constexpr auto sqrt_eps = scalar_traits<double>::sqrt_epsilon();
  CATCH_CHECK(sqrt_eps == 1.49011611938476563e-8);
}
