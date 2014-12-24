/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_cross_h
#define	cml_vector_cross_h

#include <cml/common/scalar_promotion.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/vector/traits.h>
#include <cml/vector/vector.h>

namespace cml {

/* Forward declarations: */
template<class DerivedT> class readable_vector;

/** Determine the vector type to return from cml::cross. */
template<class Sub1, class Sub2> struct cross_promote
{
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;
  typedef vector_traits<left_type>			left_traits;
  typedef vector_traits<right_type>			right_traits;

  /* Deduce the new vector element type: */
  typedef value_type_promote_t<left_traits, right_traits> value_type;

  /* Determine the new unbound storage type: */
  typedef storage_promote_t<
    storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>			unbound_type;

  /* Determine the resized proxy type: */
  typedef resize_storage_t<unbound_type, 3>		resized_type;
  typedef rebind_t<resized_type, vector_storage_tag>	storage_type;
  typedef typename storage_type::proxy_type		proxy_type;

  /* Build the vector type from the new storage type: */
  typedef vector<value_type, proxy_type>		type;
};

/** Convenience alias for cross_promote. */
template<class Sub1, class Sub2>
  using cross_promote_t = typename cross_promote<Sub1,Sub2>::type;

/** Compute the cross-product of two 3D vectors, and return the result as a
 * fixed-length vector (fixed<3>).
 *
 * @note Currently, the result is computed immediately, even if it appears
 * as a term in an expression.
 *
 * @throws vector_size_error at run-time if left or right is
 * dynamically-sized and is not a 3D vector.  The size is checked at
 * compile time for fixed-sized expressions.
 */
template<class Sub1, class Sub2> auto
cross(const readable_vector<Sub1>& left, const readable_vector<Sub2>& right)
-> cross_promote_t<Sub1,Sub2>;

} // namespace cml

#define __CML_VECTOR_CROSS_TPP
#include <cml/vector/cross.tpp>
#undef __CML_VECTOR_CROSS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
