/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {

/** Convenience "alias" for std::integral_constant<int,N>. */
template<int N> struct int_c : std::integral_constant<int, N>
{};

// Note: As of now, Visual C++ (18.00) apparently can't handle the obvious
// alias when deducing function template arguments:
// template<int N> using int_c = std::integral_constant<int,N>;

}  // namespace cml
