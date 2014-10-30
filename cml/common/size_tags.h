/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_size_tags_h
#define	cml_common_size_tags_h

#include <cml/common/mpl/type_util.h>

namespace cml {

/** Indicates a fixed-sized operand. */
struct fixed_size_tag {};

/** Indicates a runtime-sized operand. */
struct dynamic_size_tag {};

/** Templated helper to determine the size tag of an expression. */
#ifdef _MSC_VER
template<class T> using size_tag_of
  = typename cml::unqualified_type<T>::type::size_tag;
#else
template<class T> using size_tag_of
  = typename cml::unqualified_type_t<T>::size_tag;
#endif

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
