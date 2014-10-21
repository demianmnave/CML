/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_external_selector_h
#define	cml_common_external_selector_h

namespace cml {

/** Specializable type for vector or matrix storage via an external
 * (wrapped) pointer.
 *
 * @tparam Size1 Fixed first dimension size, optional if Size2 is not needed.
 * @tparam Size2 Optional fixed second dimension size.
 *
 * @note If neither Size1 nor Size2 are set, then the size is determined at
 * run-time.
 */
template<int Size1 = -1, int Size2 = -1> struct external;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
