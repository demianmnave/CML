/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {
/** Determine if a set of types, @c Froms, are convertible to another type,
 * @c To via std::is_convertible.
 */
template<class To, class... Froms> struct are_convertible
{
  static constexpr bool value = (... && std::is_convertible_v<Froms, To>);
};
}  // namespace cml
