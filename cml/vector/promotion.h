/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_promotion_h
#define	cml_vector_promotion_h

#include <cml/common/mpl/type_util.h>
#include <cml/common/mpl/if_t.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>
#include <cml/common/size_tags.h>
#include <cml/vector/traits.h>
#include <cml/vector/vector.h>

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

  typedef cml::if_t<
    is_fixed, fixed_size_tag,
    cml::if_t<is_dynamic, dynamic_size_tag, void>>	size_tag;
};

/** Convenience alias for vector_size_tag_promote. */
template<class Sub1, class Sub2> using vector_size_tag_promote_t
  = typename vector_size_tag_promote<Sub1,Sub2>::size_tag;


/** Deduce the common fixed<> or dynamic<> vector storage type that can
 * be used to store both @c Sub1 or @c Sub2.
 *
 * @note This can be specialized for other types of selectors if needed.
 */
template<class Sub1, class Sub2> struct vector_storage_from_size_tag
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
  typedef cml::if_t<
    is_dynamic, dynamic<>, fixed<array_size>>		type;
};

/** Convenience alias for vector_storage_from_size_tag<>::type. */
template<class Sub1, class Sub2> using vector_storage_from_size_tag_t
  = typename vector_storage_from_size_tag<Sub1,Sub2>::type;

/** Convenience alias to create a fixed<> or dynamic<> vector temporary
 * type that can hold values from either of two vector expression types.
 */
template<class Sub1, class Sub2, class Element>
  using vector_temporary_promote_t
    = vector<Element, vector_storage_from_size_tag_t<Sub1,Sub2>>;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
