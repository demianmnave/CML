/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_vector_h
#define	cml_vector_vector_h

namespace cml {

/** Specializable class for building vector types.
 *
 * @note @c Element must have the following operators defined: +, -, *, /,
 * <, >, ==, = (assign).
 */
template<class Element, class StorageType> class vector;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
