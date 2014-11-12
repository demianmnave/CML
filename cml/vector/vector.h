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
 * This class encapsulates the notion of a vector.
 *
 * @tparam Element The scalar type for vector elements, with the following
 * operators defined: +, -, *, /, <, >, ==, = (assign).
 *
 * @tparam StorageType Used to select the type of array to be used as
 * internal storage for an array of type Element.
 *
 * @sa scalar_traits
 */
template<class Element, class StorageType> class vector;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
