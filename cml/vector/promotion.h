/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_util_vector_promotion_h
#define	cml_util_vector_promotion_h

#include <cml/common/scalar_promotion.h>
#include <cml/common/promotion.h>
#include <cml/common/temporary.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/vector/type_util.h>
#include <cml/vector/traits.h>
#include <cml/vector/vector.h>

namespace cml {

/** Determine an appropriate storage type to use when combining vector
 * expressions via a non-product binary operator.
 *
 * @note This can be specialized to accomodate user-defined storage types.
 */
template<class Element, class Storage1, class Storage2>
struct vector_binary_storage_promote
{
  static_assert(
    is_vector_storage<Storage1>::value &&
    is_vector_storage<Storage2>::value,
    "expected vector storage types for binary promotion");

  /* Determine the promoted unbound storage type: */
  typedef storage_promote_t<Storage1, Storage2>		unbound_type;

  /* Determine the new vector size: */
  static const int array_size
    = Storage1::array_size > Storage2::array_size
    ?  Storage1::array_size : Storage2::array_size;

  /* Resize: */
  typedef resize_storage_t<unbound_type, array_size>	resized_type;

  /* Rebind to a vector storage type: */
  typedef rebind_t<resized_type, vector_storage_tag>	type;
};

/** Convenience alias for vector_binary_storage_promote. */
template<class Element, class Storage1, class Storage2>
  using vector_binary_storage_promote_t =
    typename vector_binary_storage_promote<Element, Storage1, Storage2>::type;


/** Deduce a temporary for a vector expression. */
template<class Vector>
struct temporary_of<Vector, enable_if_vector_t<Vector>>
{
  typedef cml::unqualified_type_t<Vector>		vector_type;

  /* Propagate the element type of the original vector: */
  typedef vector_traits<vector_type>			traits_type;
  typedef typename traits_type::storage_type		storage_type;
  typedef typename traits_type::value_type		value_type;

  /* Need the proxy for the storage type: */
  typedef typename storage_type::proxy_type		proxy_type;

  /* Build the temporary: */
  typedef vector<value_type, proxy_type>		type;
};

/** Deduce a subvector temporary type for a vector expression. */
template<class Vector, enable_if_vector_t<Vector>* = nullptr>
struct subvector_of
{
  typedef cml::unqualified_type_t<Vector>		vector_type;

  /* Propagate the element type of the original vector: */
  typedef vector_traits<vector_type>			traits_type;
  typedef typename traits_type::storage_type		storage_type;
  typedef typename traits_type::value_type		value_type;
  typedef typename traits_type::size_tag		size_tag;

  /* Compute the new storage size: */
  private:
  static const int old_array_size = traits_type::array_size;
  static const int new_array_size = old_array_size - 1;
  static const int N = new_array_size > 0 ? new_array_size : -1;
  public:

  /* Determine the new storage type: */
  typedef resize_storage_t<storage_type, N>		resized_type;
  typedef rebind_t<resized_type, vector_storage_tag>	rebound_type;
  typedef typename rebound_type::proxy_type		proxy_type;

  /* Build the subvector from the new storage type: */
  typedef vector<value_type, proxy_type>		type;
};

/** Convenience alias for subvector_of. */
template<class T> using subvector_of_t = typename subvector_of<T>::type;


/** Helper to deduce a reasonable vector type from two vector subexpression
 * types.  This can be specialized for non-default behavior.
 */
template<class Sub1, class Sub2, class Enable = void> struct vector_promote;

template<class Sub1, class Sub2> struct vector_promote<
  Sub1, Sub2, typename std::enable_if<
    is_vector<Sub1>::value && is_vector<Sub2>::value>::type>
{
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;
  typedef vector_traits<left_type>			left_traits;
  typedef vector_traits<right_type>			right_traits;

  /* Deduce the new vector element type: */
  typedef value_type_promote_t<left_traits, right_traits> value_type;

  /* Determine the new storage type: */
  typedef vector_binary_storage_promote_t<
    value_type,
    storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>			storage_type;

  /* Build the vector type: */
  typedef vector<value_type, storage_type>		type;
};

/** Convenience alias for vector_promote<>. */
template<class Sub1, class Sub2>
  using vector_promote_t = typename vector_promote<Sub1,Sub2>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
