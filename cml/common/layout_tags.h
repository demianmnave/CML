/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/traits.h>

namespace cml {
/* Forward declarations: */
struct row_major;
struct col_major;
struct any_major;

enum layout_kind
{
  row_major_c = 1,
  col_major_c = 2,
  any_major_c = 3,
  layout_count = 3
};

/** Row major tag. */
struct row_major
{
  /** row_major transposes to col_major. */
  using transposed_tag = col_major;

  /** Integral identifier. */
  static const layout_kind value = row_major_c;
};

/** Column major tag. */
struct col_major
{
  /** col_major transposes to row_major. */
  using transposed_tag = row_major;

  /** Integral identifier. */
  static const layout_kind value = col_major_c;
};

/** Arbitrary or unspecified major tag. */
struct any_major
{
  /** any_major transposes to itself. */
  using transposed_tag = any_major;

  /** Integral identifier. */
  static const layout_kind value = any_major_c;
};

/** Detect valid layout tags.
 *
 * @note This can be specialized for user-defined layout tags.
 */
template<class Tag> struct is_layout_tag
{
  static const bool value = std::is_same_v<Tag, row_major>
    || std::is_same_v<Tag, col_major>
    || std::is_same_v<Tag, any_major>;
};

/** Templated helper to determine the layout tag of an expression that
 * defines the layout_tag type.
 */
template<class T> struct layout_tag_of
{
  using type = typename T::layout_tag;
  static_assert(is_layout_tag<type>::value, "invalid layout tag");
};

/** Convenience alias for layout_tag_of. */
template<class T> using layout_tag_of_t = typename layout_tag_of<T>::type;

/** Retrieve the layout_tag of @c T via traits. */
template<class T> struct layout_tag_trait_of
{
  using type = typename traits_of<T>::type::layout_tag;
  static_assert(is_layout_tag<type>::value, "invalid layout tag");
};

/** Convenience alias for layout_tag_trait_of. */
template<class T>
using layout_tag_trait_of_t = typename layout_tag_trait_of<T>::type;
} // namespace cml
