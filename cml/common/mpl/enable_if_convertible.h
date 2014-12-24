/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_enable_if_convertible_h
#define	cml_common_mpl_enable_if_convertible_h

#include <cml/common/type_util.h>

namespace cml {

/** Wrapper for enable_if to detect if a set of types, @c Froms, are
 * convertible to @c To.
 */
template<class To, class... Froms> struct enable_if_convertible
  : std::enable_if<are_convertible<To, Froms...>::value> {};

/** Convenience alias for enable_if_convertible. */
template<class To, class... Froms> using enable_if_convertible_t
  = typename enable_if_convertible<To, Froms...>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
