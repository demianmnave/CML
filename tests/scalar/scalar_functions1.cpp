/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

// Make sure the main header compiles cleanly:
#include <cml/scalar/functions.h>

/* Testing headers: */
#include "catch_runner.h"

CATCH_TEST_CASE("length_squared1")
{
  constexpr auto l2 = cml::length_squared(1., 1.);
  CATCH_CHECK(l2 == Approx(2.).margin(cml::epsilon<double>()));
}

CATCH_TEST_CASE("index_of_min1")
{
  CATCH_SECTION("index_of_min")
  {
    constexpr auto i1 = cml::index_of_min(1, 2);
    CATCH_CHECK(i1 == 0);

    constexpr auto i2 = cml::index_of_min(2, 1);
    CATCH_CHECK(i2 == 1);
  }

  CATCH_SECTION("index_of_min_abs")
  {
    const auto i1 = cml::index_of_min_abs(1, -2);
    CATCH_CHECK(i1 == 0);

    const auto i2 = cml::index_of_min_abs(2, -1);
    CATCH_CHECK(i2 == 1);
  }
}

CATCH_TEST_CASE("index_of_min2")
{
  CATCH_SECTION("index_of_min")
  {
    constexpr auto i1 = cml::index_of_min(1, 2, 3);
    CATCH_CHECK(i1 == 0);

    constexpr auto i2 = cml::index_of_min(2, 3, 1);
    CATCH_CHECK(i2 == 2);
  }

  CATCH_SECTION("index_of_min_abs")
  {
    const auto i1 = cml::index_of_min_abs(1, -2, 0);
    CATCH_CHECK(i1 == 2);

    const auto i2 = cml::index_of_min_abs(2, -1, 3);
    CATCH_CHECK(i2 == 1);
  }
}

CATCH_TEST_CASE("index_of_min3")
{
  CATCH_SECTION("index_of_min")
  {
    // clang-format off
    const double v[] = {
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit()
    };
    // clang-format on
    const auto i = cml::index_of_min(v[0], v[1], v[2], v[3], v[4]);

    int index[] = {0, 1, 2, 3, 4};
    std::sort(std::begin(index), std::end(index), [v](auto a, auto b) {
      return v[a] < v[b];
    });
    CATCH_CHECK(i == index[0]);
  }

  CATCH_SECTION("index_of_min_abs")
  {
    // clang-format off
    const double v[] = {
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.)
    };
    // clang-format on
    const auto i = cml::index_of_min_abs(v[0], v[1], v[2], v[3], v[4]);

    int index[] = {0, 1, 2, 3, 4};
    std::sort(std::begin(index), std::end(index), [v](auto a, auto b) {
      return v[a] < v[b];
    });
    CATCH_CHECK(i == index[0]);
  }
}

CATCH_TEST_CASE("index_of_max1")
{
  CATCH_SECTION("index_of_max")
  {
    constexpr auto i1 = cml::index_of_max(1, 2);
    CATCH_CHECK(i1 == 1);

    constexpr auto i2 = cml::index_of_max(2, 1);
    CATCH_CHECK(i2 == 0);
  }

  CATCH_SECTION("index_of_max_abs")
  {
    const auto i1 = cml::index_of_max_abs(1, -2);
    CATCH_CHECK(i1 == 1);

    const auto i2 = cml::index_of_max_abs(2, -1);
    CATCH_CHECK(i2 == 0);
  }
}

CATCH_TEST_CASE("index_of_max2")
{
  CATCH_SECTION("index_of_max")
  {
    constexpr auto i1 = cml::index_of_max(1, 2, 3);
    CATCH_CHECK(i1 == 2);

    constexpr auto i2 = cml::index_of_max(2, 3, 1);
    CATCH_CHECK(i2 == 1);
  }

  CATCH_SECTION("index_of_max_abs")
  {
    const auto i1 = cml::index_of_max_abs(1, -2, 0);
    CATCH_CHECK(i1 == 1);

    const auto i2 = cml::index_of_max_abs(2, -1, 3);
    CATCH_CHECK(i2 == 2);
  }
}

CATCH_TEST_CASE("index_of_max3")
{
  CATCH_SECTION("index_of_max")
  {
    // clang-format off
    const double v[] = {
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit(),
      cml::random_unit()
    };
    // clang-format on
    const auto i = cml::index_of_max(v[0], v[1], v[2], v[3], v[4]);

    int index[] = {0, 1, 2, 3, 4};
    std::sort(std::begin(index), std::end(index), [v](auto a, auto b) {
      return v[a] > v[b];
    });
    CATCH_CHECK(i == index[0]);
  }

  CATCH_SECTION("index_of_max_abs")
  {
    // clang-format off
    const double v[] = {
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.),
      cml::random_real(-1.,1.)
    };
    // clang-format on
    const auto i = cml::index_of_max_abs(v[0], v[1], v[2], v[3], v[4]);

    int index[] = {0, 1, 2, 3, 4};
    std::sort(std::begin(index), std::end(index), [v](auto a, auto b) {
      return v[a] > v[b];
    });
    CATCH_CHECK(i == index[0]);
  }
}
