/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_enable_if_arithmetic_h
#define	cml_common_mpl_enable_if_arithmetic_h

#include <cml/common/type_util.h>

namespace cml {

/** Wrapper for enable_if to detect arithmetic types.  @c T is tested after
 * removing const, volatile, and reference qualifiers.
 */
template<class T> struct enable_if_arithmetic
  : std::enable_if<std::is_arithmetic<cml::unqualified_type_t<T>>::value> {};

/** Convenience alias for enable_if_arithmetic. */
template<class T> using enable_if_arithmetic_t
  = typename enable_if_arithmetic<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
