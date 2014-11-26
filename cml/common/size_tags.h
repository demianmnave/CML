/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_size_tags_h
#define	cml_common_size_tags_h

#include <cml/common/type_util.h>

namespace cml {

/** Indicates a fixed-sized operand. */
struct fixed_size_tag {};

/** Indicates a runtime-sized operand. */
struct dynamic_size_tag {};

/** Indicates that the operand can take any required size. */
struct any_size_tag {};

/** Detect valid size tags.
 *
 * @note This can be specialized for user-defined size tags.
 */
template<class Tag> struct is_size_tag {
  static const bool value
    =  std::is_same<Tag, fixed_size_tag>::value
    || std::is_same<Tag, dynamic_size_tag>::value
    || std::is_same<Tag, any_size_tag>::value;
};

/** Templated helper to determine the size tag of an expression that
 * defines the size_tag type.
 */
template<class T> struct size_tag_of {
  typedef typename cml::unqualified_type<T>::type::size_tag type;
  static_assert(cml::is_size_tag<type>::value, "invalid size tag");
};

/** Convenience alias for size_tag_of. */
template<class T> using size_tag_of_t = typename size_tag_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
