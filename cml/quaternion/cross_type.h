/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_quaternion_cross_type_h
#define	cml_quaternion_cross_type_h

namespace cml {

/** Helper to specify v1^v2 multiplication order. */
struct positive_cross {};

/** Helper to specify v2^v1 multiplication order. */
struct negative_cross {};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
