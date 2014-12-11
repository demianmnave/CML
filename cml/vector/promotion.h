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

/** Helper to deduce the vector temporary type that can be used to store
 * the result of pairwise combining @c Sub1 and @c Sub2, using elements of
 * type @c E.  By default, the temporary storage type will be either
 * fixed<> or dynamic<>, depending upon the types of @c Sub1 and @c Sub2.
 *
 * @note This can be specialized for user-defined vector types.
 */
template<class Sub1, class Sub2, class E> struct vector_temporary_promote {
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;

  /* Determine the storage type: */
  static const int left_array_size = array_size_of_c<left_type>::value;
  static const int right_array_size = array_size_of_c<right_type>::value;
  static const int array_size
    = left_array_size > right_array_size ? left_array_size : right_array_size;
  typedef cml::if_t<array_size == -1,
	  cml::dynamic<>, cml::fixed<array_size>> storage_type;

  /* Build the vector type: */
  typedef vector<E, storage_type> type;
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
