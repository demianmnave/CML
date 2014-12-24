/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_layout_tags_h
#define	cml_common_layout_tags_h

#include <cml/common/traits.h>

namespace cml {

enum layout_kind {
  row_major_c = 1,
  col_major_c = 2,
  any_major_c = 3,
  layout_count = 3
};

/** Row major tag. */
struct row_major { static const layout_kind value = row_major_c; };

/** Column major tag. */
struct col_major { static const layout_kind value = col_major_c; };

/** Arbitrary layout tag. */
struct any_major { static const layout_kind value = any_major_c; };

/** Detect valid layout tags.
 *
 * @note This can be specialized for user-defined layout tags.
 */
template<class Tag> struct is_layout_tag {
  static const bool value
    =  std::is_same<Tag, row_major>::value
    || std::is_same<Tag, col_major>::value
    || std::is_same<Tag, any_major>::value;
};

/** Templated helper to determine the layout tag of an expression that
 * defines the layout_tag type.
 */
template<class T> struct layout_tag_of {
  typedef typename T::layout_tag type;
  static_assert(is_layout_tag<type>::value, "invalid layout tag");
};

/** Convenience alias for layout_tag_of. */
template<class T> using layout_tag_of_t = typename layout_tag_of<T>::type;

/** Retrieve the layout_tag of @c T via traits. */
template<class T> struct layout_tag_trait_of {
  typedef typename traits_of<T>::type::layout_tag type;
  static_assert(is_layout_tag<type>::value, "invalid layout tag");
};

/** Convenience alias for layout_tag_trait_of. */
template<class T>
  using layout_tag_trait_of_t = typename layout_tag_trait_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
