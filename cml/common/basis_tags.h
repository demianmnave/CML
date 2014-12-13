/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_basis_tags_h
#define	cml_common_basis_tags_h

#include <cml/common/traits.h>

namespace cml {

enum basis_kind {
  row_basis_c = 1,
  col_basis_c = 2,
  any_basis_c = 3,
  basis_count = 3
};

/** Row basis tag. */
struct row_basis { static const basis_kind value = row_basis_c; };

/** Column basis tag. */
struct col_basis { static const basis_kind value = col_basis_c; };

/** Any basis tag. */
struct any_basis { static const basis_kind value = any_basis_c; };

/** Detect valid basis tags. */
template<class Tag> struct is_basis_tag {
  static const bool value
    =  std::is_same<Tag, row_basis>::value
    || std::is_same<Tag, col_basis>::value
    || std::is_same<Tag, any_basis>::value;
};

/** Templated helper to determine the size tag of an expression that
 * defines the basis_tag type.
 */
template<class T> struct basis_tag_of {
  typedef typename T::basis_tag type;
  static_assert(cml::is_basis_tag<type>::value, "invalid basis tag");
};

/** Convenience alias for basis_tag_of. */
template<class T> using basis_tag_of_t = typename basis_tag_of<T>::type;

/** Retrieve the basis_tag of @c T via traits. */
template<class T> struct basis_tag_trait_of {
  typedef typename traits_of<T>::type::basis_tag type;
  static_assert(cml::is_basis_tag<type>::value, "invalid size tag");
};

/** Convenience alias for basis_tag_trait_of. */
template<class T>
  using basis_tag_trait_of_t = typename basis_tag_trait_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
