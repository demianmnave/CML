/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <memory>

namespace cml {
/** Helper to rebind @c T via template rebind<Args...>.
 *
 * @note Only typed parameters are supported.
 */
template<class T, class... Args> struct rebind
{
  using other = typename T::template rebind<Args...>::other;
};

/** Convenience alias for rebind. */
template<class T, class... Args>
using rebind_t = typename rebind<T, Args...>::other;

/** Helper to rebind allocator @c T.
 *
 * @note Only typed parameters are supported.
 */
template<class T, class... Args> struct rebind_alloc
{
  using traits = std::allocator_traits<T>;
  using other = typename traits::template rebind_alloc<Args...>;
};

/** Convenience alias for rebind_alloc. */
template<class T, class... Args>
using rebind_alloc_t = typename rebind_alloc<T, Args...>::other;
} // namespace cml
