/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_are_convertible_h
#define	cml_common_mpl_are_convertible_h

#include <cml/common/scalar_promotion.h>

namespace cml {

/** Helper to determine if a sequence of types (@c From) are convertible to
 * another type (@c To).
 */
template<class To, class... Froms> struct are_convertible {
  static const int value
    = std::is_convertible<cml::scalar_promote_t<Froms...>, To>::value;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
