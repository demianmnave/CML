/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_fixed_selector_h
#define	cml_common_fixed_selector_h

namespace cml {

/** Specializable type for vector or matrix storage via a fixed-length
 * array.
 *
 * @tparam Size1 Fixed first dimension size.
 * @tparam Size2 Optional fixed second dimension size.
 */
template<int Size1, int Size2 = -1> struct fixed;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
