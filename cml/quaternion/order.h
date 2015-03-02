/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_quaternion_order_h
#define	cml_quaternion_order_h

namespace cml {

/** Helper to specify real-first quaternion element ordering. */
struct real_first {
    enum { W = 0, X = 1, Y = 2, Z = 3 };
};

/** Helper to specify imaginary-first quaternion element ordering. */
struct imaginary_first {
    enum { X = 0, Y = 1, Z = 2, W = 3 };
};

/** For CML1 compatibility. */
using scalar_first = real_first;

/** For CML1 compatibility. */
using vector_first = imaginary_first;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
