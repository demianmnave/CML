/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_rebind_h
#define	cml_common_mpl_rebind_h

namespace cml {

/** Helper to rebind @c T via template rebind<Args...>.
 *
 * @note Only typed parameters are supported.
 */
template<class T, class... Args> struct rebind {
  typedef typename T::template rebind<Args...>::other other;
};

/** Convenience alias for rebind. */
template<class T, class... Args>
  using rebind_t = typename rebind<T,Args...>::other;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
