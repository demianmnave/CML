/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_basis_tags_h
#define	cml_matrix_basis_tags_h

#include <cml/common/mpl/type_util.h>

namespace cml {

enum basis_kind {
  row_basis_c = 1,
  col_basis_c = 2,
  basis_count = 2
};

/** Row basis tag. */
struct row_basis { static const basis_kind value = row_basis_c; };

/** Column basis tag. */
struct col_basis { static const basis_kind value = col_basis_c; };

/** Detect valid basis tags. */
template<class Tag> struct is_basis_tag {
  static const bool value
    =  std::is_same<Tag, row_basis>::value
    || std::is_same<Tag, col_basis>::value;
};

/** Templated helper to determine the size tag of an expression that
 * defines the basis_tag type.
 */
template<class T> struct basis_tag_of {
  typedef typename cml::unqualified_type<T>::type::basis_tag type;
  static_assert(cml::is_basis_tag<type>::value, "invalid basis tag");
};

/** Convenience alias for basis_tag_of. */
template<class T> using basis_tag_of_t = typename basis_tag_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
