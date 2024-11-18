/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#define CATCH_CONFIG_PREFIX_ALL
#define CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp> // Note: Approx() is deprecated in Catch2 v3
using Catch::Approx;
