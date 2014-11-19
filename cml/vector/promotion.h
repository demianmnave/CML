/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_promotion_h
#define	cml_vector_promotion_h

#include <cml/common/mpl/array_size_of.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>
#include <cml/common/promotion.h>
#include <cml/vector/traits.h>
#include <cml/vector/vector.h>

namespace cml {

/** Templated helper to return the size_tag of a vector expression using
 * vector_traits.
 *
 * @note This can be specialized for user-defined vector types.
 */
template<class Sub> struct vector_size_tag_of {
  typedef size_tag_of_t<vector_traits<cml::unqualified_type_t<Sub>>> type;
};

/** Return the size_tag of a vector expression using vector_traits. */
template<class Sub> using vector_size_tag_of_t
  = typename vector_size_tag_of<Sub>::type;


/** Deduce the vector size tag resulting from combining the size_tag types
 * from two vector expressions.
 *
 * @note This can be specialized for user-defined vector types.
 */
template<class Sub1, class Sub2> struct vector_size_tag_promote {
  typedef size_tag_promote_t<
    vector_size_tag_of_t<Sub1>, vector_size_tag_of_t<Sub2>> type;
};

/** Convenience alias for vector_size_tag_promote. */
template<class Sub1, class Sub2> using vector_size_tag_promote_t
  = typename vector_size_tag_promote<Sub1,Sub2>::type;


/** Deduce the fixed<> or dynamic<> storage type that can be used to create
 * a temporary to store the result of combining @c Sub1 and @c Sub2.  By
 * default:
 *
 * - fixed_size_tag with any other tag: fixed<>
 * - otherwise (including any_size_tag): dynamic<>
 *
 * @note This can be specialized for user-defined vector types.
 */
template<class Sub1, class Sub2> struct vector_storage_promote
{
  /* The promoted size tag: */
  typedef vector_size_tag_promote_t<Sub1,Sub2>		size_tag;

  /* True if the promoted size is fixed_size_tag: */
  static const bool is_fixed
    = std::is_same<size_tag,fixed_size_tag>::value;

  /* The left array size (-1 if dynamic_size_tag or any_size_tag): */
  static const int left_array_size
    = cml::array_size_of_c<cml::unqualified_type_t<Sub1>>::value;

  /* The right array size (-1 if dynamic_size_tag or any_size_tag): */
  static const int right_array_size
    = cml::array_size_of_c<cml::unqualified_type_t<Sub2>>::value;

  /* The fixed array size, or -1 if Sub1 and Sub2 are dynamic or any size
   * expressions:
   */
  static const int array_size
    = left_array_size > right_array_size
    ? left_array_size : right_array_size;

  /* Check: */
  static_assert((array_size > 0) || !is_fixed, "invalid array size");

  /* Use fixed<> storage if possible, otherwise use dynamic<>: */
  typedef cml::if_t<
    std::is_same<size_tag, fixed_size_tag>::value,
    fixed<array_size>, dynamic<>>			type;
};

/** Convenience alias for vector_storage_promote_t<>::type. */
template<class Sub1, class Sub2> using vector_storage_promote_t
  = typename vector_storage_promote<Sub1,Sub2>::type;


/** Helper to deduce the vector temporary type that can be used to store
 * the result of combining @c Sub1 and @c Sub2, using elements of type @c
 * E.
 *
 * @note This can be specialized for user-defined vector types.
 */
template<class Sub1, class Sub2, class E> struct vector_temporary_promote {
  typedef vector<E, vector_storage_promote_t<Sub1,Sub2>> type;
};

/** Convenience alias to create a fixed<> or dynamic<> vector temporary
 * type that can hold values from either of two vector expression types.
 */
template<class Sub1, class Sub2, class E> using vector_temporary_promote_t
  = typename vector_temporary_promote<Sub1,Sub2,E>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
