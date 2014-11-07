/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_promotion_h
#define	cml_vector_promotion_h

#include <cml/common/size_tags.h>
#include <cml/common/mpl/if_t.h>
#include <cml/vector/traits.h>

namespace cml {

/** Specializable class for deducing the vector size tag resulting from
 * combining the size_tag types from two vector expressions.
 */
template<class Sub1, class Sub2> struct vector_size_tag_promote
{
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;
  typedef typename vector_traits<left_type>::size_tag	left_size_tag;
  typedef typename vector_traits<right_type>::size_tag	right_size_tag;

  /* Fixed-size with any other tag promotes to fixed-size: */
  static const bool is_fixed
    = std::is_same<left_size_tag,fixed_size_tag>::value
    || std::is_same<right_size_tag,fixed_size_tag>::value;

  /* Both dynamic promotes to dynamic: */
  static const bool is_dynamic
    = std::is_same<left_size_tag,dynamic_size_tag>::value
    || std::is_same<right_size_tag,dynamic_size_tag>::value;

  typedef if_t<
    is_fixed, fixed_size_tag,
    if_t<is_dynamic, dynamic_size_tag, void>>		size_tag;
};

/** Convenience alias for vector_size_tag_promote. */
template<class Sub1, class Sub2> using vector_size_tag_promote_t
  = typename vector_size_tag_promote<Sub1,Sub2>::size_tag;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
