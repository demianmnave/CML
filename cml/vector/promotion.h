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

namespace cml {

/** Specializable class for deducing the vector size tag resulting from
 * combining two tags.
 */
template<class SizeTag1, class SizeTag2> struct vector_size_tag_promote
{
  /* Fixed-size with any other tag promotes to fixed-size: */
  static const bool is_fixed
    = std::is_same<SizeTag1,fixed_size_tag>::value
    || std::is_same<SizeTag2,fixed_size_tag>::value;

  /* Both dynamic promotes to dynamic: */
  static const bool is_dynamic
    = std::is_same<SizeTag1,dynamic_size_tag>::value
    || std::is_same<SizeTag2,dynamic_size_tag>::value;

  typedef if_t<
    is_fixed, fixed_size_tag,
    if_t<is_dynamic, dynamic_size_tag, void>>		size_tag;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
