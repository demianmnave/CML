/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_promotion_h
#define	cml_common_promotion_h

#include <cml/common/mpl/if_t.h>
#include <cml/common/size_tags.h>

namespace cml {

/** Deduce the size tag needed to compare the size of two expressions
 * having size tags @c Tag1 and @c Tag2.  By default:
 *
 * - any_size_tag with any other tag: any_size_tag
 * - fixed_size_tag with fixed_size_tag: fixed_size_tag
 * - otherwise: dynamic_size_tag
 *
 * @note This can be specialized for user-defined size tags.
 */
template<class Tag1, class Tag2> struct size_check_promote
{
  static_assert(cml::is_size_tag<Tag1>::value, "invalid size tag");
  static_assert(cml::is_size_tag<Tag2>::value, "invalid size tag");

  /* Promote to any_size_tag when combined with any other tag: */
  static const bool is_any
    = std::is_same<Tag1, any_size_tag>::value
    || std::is_same<Tag2, any_size_tag>::value;

  /* Promote to fixed_size_tag when combining two fixed-size expressions: */
  static const bool is_fixed
    = std::is_same<Tag1,fixed_size_tag>::value
    && std::is_same<Tag2,fixed_size_tag>::value;

  /* Promote to dynamic_size_tag by default if not promoting to
   * any_size_tag or fixed_size_tag:
   */
  typedef cml::if_t<
    is_any, any_size_tag, cml::if_t<
    is_fixed, fixed_size_tag, dynamic_size_tag>>	type;
};

/** Convenience alias for size_check_promote. */
template<class Tag1, class Tag2> using size_check_promote_t
= typename size_check_promote<Tag1,Tag2>::type;


/** Deduce the default size tag needed to promote the result of combining
 * two expressions having size tags @c Tag1 and @c Tag2.  By default:
 *
 * - fixed_size_tag with any other tag: fixed_size_tag
 * - dynamic_size_tag with any other tag: dynamic_size_tag
 * - any_size_tag with any_size_tag: any_size_tag
 *
 * @note This can be specialized for user-defined size tags.
 */
template<class Tag1, class Tag2> struct size_tag_promote
{
  static_assert(cml::is_size_tag<Tag1>::value, "invalid size tag");
  static_assert(cml::is_size_tag<Tag2>::value, "invalid size tag");

  /* Fixed-size with any other tag promotes to fixed-size: */
  static const bool is_fixed
    = std::is_same<Tag1,fixed_size_tag>::value
    || std::is_same<Tag2,fixed_size_tag>::value;

  /* Promote to dynamic if not promoting to fixed, and if at least one of
   * the size tags is dynamic_size_tag:
   */
  static const bool is_dynamic = !is_fixed &&
    (std::is_same<Tag1,dynamic_size_tag>::value
     || std::is_same<Tag2,dynamic_size_tag>::value);

  /* Promote to any_size_tag when both are any_size_tag: */
  static const bool is_any
    = std::is_same<Tag1, any_size_tag>::value
    && std::is_same<Tag2, any_size_tag>::value;

  /* Has to be one of the deduced categories: */
  static_assert(is_fixed || is_dynamic || is_any, "unexpected size tag type");

  /* Promote to the selected tag: */
  typedef cml::if_t<is_fixed, fixed_size_tag,
	  cml::if_t<is_dynamic, dynamic_size_tag, any_size_tag>> type;
};

/** Convenience alias for size_tag_promote. */
template<class Tag1, class Tag2>
  using size_tag_promote_t = typename size_tag_promote<Tag1,Tag2>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
