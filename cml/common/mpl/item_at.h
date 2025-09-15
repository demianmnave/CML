/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <tuple>

namespace cml {
/** Return item @c N of argument pack @c Args. */
template<int N, class... Args>
auto
item_at(Args&&... args)
  -> decltype(std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...)))
{
  return std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
}
} // namespace cml
