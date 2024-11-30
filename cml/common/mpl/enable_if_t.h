/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {

/** Helper for enable_if.
 *
 * @todo use C++14 enable_if_t if available.
 */
template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

}  // namespace cml
