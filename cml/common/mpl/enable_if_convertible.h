/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/are_convertible.h>

namespace cml {
/** Convenience alias for enable_if to detect if a set of types, @c Froms,
 * are convertible to @c To.
 */
template<class To, class... Froms>
using enable_if_convertible =
std::enable_if<are_convertible<To, Froms...>::value>;

/** Convenience alias for enable_if_convertible. */
template<class To, class... Froms>
using enable_if_convertible_t =
typename std::enable_if<are_convertible<To, Froms...>::value>::type;
} // namespace cml
