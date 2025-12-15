/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <utility>

namespace cml {
/** Wrapper for enable_if to detect arithmetic types.  @c T is tested after
 * removing const, volatile, and reference qualifiers.
 */
template<class T>
struct enable_if_arithmetic : std::enable_if<std::is_arithmetic_v<T>>
{
};

/** Convenience alias for enable_if_arithmetic. */
template<class T>
using enable_if_arithmetic_t = typename enable_if_arithmetic<T>::type;
} // namespace cml
