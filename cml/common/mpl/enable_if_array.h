/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {
/** Alias for std::enable_if<T> using std::is_array<T> to determine the
 * boolean value.
 */
template<class Array>
using enable_if_array = typename std::enable_if<std::is_array_v<Array>
  && !std::is_pointer_v<Array>>;

/** Alias for std::enable_if<T>::type using std::is_array<T> to determine
 * the boolean value.
 */
template<class Array>
using enable_if_array_t = typename enable_if_array<Array>::type;
} // namespace cml
