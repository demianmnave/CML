/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_enable_if_convertible_h
#define	cml_common_mpl_enable_if_convertible_h

#include <cml/common/mpl/are_convertible.h>

namespace cml {

/** Alias for std::enable_if<T> using std::is_convertible<T> to determine the
 * boolean value.
 */
template<class To, class... Froms> using enable_if_convertible
  = std::enable_if<cml::are_convertible<To,Froms...>::value>;

/** Alias for std::enable_if<T>::type using std::is_convertible<T> to determine
 * the boolean value.
 */
template<class Array> using enable_if_convertible_t
  = typename cml::enable_if_convertible<Array>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
