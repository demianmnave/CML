/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_promotion_h
#define	cml_vector_promotion_h

#include <cml/common/mpl/if_t.h>
#include <cml/common/mpl/type_util.h>
#include <cml/common/size_tags.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>
#include <cml/vector/traits.h>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Deduce the vector size tag resulting from combining the size_tag types
 * from two vector expressions.
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


/** Deduce the common fixed<> or dynamic<> vector storage selector that can
 * be used to store both @c Sub1 or @c Sub2.
 *
 * @note This can be specialized for other types of selectors if needed.
 */
template<class Sub1, class Sub2> struct vector_selector_promote
{
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;
  typedef vector_traits<left_type>			left_traits;
  typedef vector_traits<right_type>			right_traits;
  typedef typename left_traits::size_tag		left_size_tag;
  typedef typename right_traits::size_tag		right_size_tag;

  /** True if either expression is dynamic. */
  static const bool is_dynamic
    = std::is_same<left_size_tag, dynamic_size_tag>::value
    || std::is_same<right_size_tag, dynamic_size_tag>::value;

  /** -1 if either expression is dynamic, or the larger of the non-negative
   * fixed sizes otherwise.
   */
  static const int array_size
    = (left_type::array_size > right_type::array_size
      ? left_type::array_size : right_type::array_size);

  /** The common fixed<> or dynamic<> selector. */
  typedef if_t<
    is_dynamic, dynamic<>, fixed<array_size>>		type;
};

/** Convenience alias for vector_selector_promote. */
template<class Sub1, class Sub2> using vector_selector_promote_t
  = typename vector_selector_promote<Sub1,Sub2>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
