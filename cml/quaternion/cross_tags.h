/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_quaternion_cross_tags_h
#define	cml_quaternion_cross_tags_h

namespace cml {

/** Helper to specify v1^v2 multiplication cross. */
struct positive_cross {};

/** Helper to specify v2^v1 multiplication cross. */
struct negative_cross {};

/** Detect valid cross types. */
template<class Tag> struct is_cross_type {
  static const bool value
    =  std::is_same<Tag, positive_cross>::value
    || std::is_same<Tag, negative_cross>::value
    ;
};

/** Templated helper to determine the cross type of an expression that
 * defines the cross_type type.
 */
template<class T> struct cross_type_of {
  typedef typename T::cross_type type;
  static_assert(is_cross_type<type>::value, "invalid cross type");
};

/** Convenience alias for cross_type_of. */
template<class T> using cross_type_of_t = typename cross_type_of<T>::type;

/** Retrieve the cross_type of @c T via traits. */
template<class T> struct cross_type_trait_of {
  typedef typename traits_of<T>::type::cross_type type;
  static_assert(is_cross_type<type>::value, "invalid cross type");
};

/** Convenience alias for cross_type_trait_of. */
template<class T>
  using cross_type_trait_of_t = typename cross_type_trait_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
