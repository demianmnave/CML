/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {

/** Determine if a set of types, @c Froms, are convertible to another type,
 * @c To via std::is_convertible.
 */
template<class To, class... Froms> struct are_convertible;

/** Determine if @c From is convertible to @c To. */
template<class To, class From>
struct are_convertible<To, From> : std::is_convertible<From, To>
{};

/** Recursively determine if @c From and @c Froms are convertible to @c To. */
template<class To, class From, class... Froms>
struct are_convertible<To, From, Froms...>
{
  static const bool value = std::is_convertible<From, To>::value
    && are_convertible<To, Froms...>::value;
};

}  // namespace cml
