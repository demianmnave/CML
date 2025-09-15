/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

namespace cml {
/** Specializable class for building vector types.
 *
 * This class encapsulates the notion of a vector.
 *
 * @tparam Element The scalar type for vector elements, with the following
 * operators defined: +, -, *, /, <, >, ==, = (assign).
 *
 * @tparam StorageType Storage type to use for holding the array of vector
 * elements.
 *
 * @sa scalar_traits
 */
template<class Element, class StorageType> class vector;
} // namespace cml
