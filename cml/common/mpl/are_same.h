/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {
/** Determine if a set of types, @c Froms, are the same as @c To via
 * std::is_same.
 */
template<class To, class... Froms> struct are_same
{
  static constexpr bool value = (... && std::is_same_v<Froms, To>);
};
}  // namespace cml
