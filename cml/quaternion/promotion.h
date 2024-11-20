/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/promotion.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/scalar/promotion.h>
#include <cml/quaternion/order_tags.h>
#include <cml/quaternion/cross_tags.h>
#include <cml/quaternion/type_util.h>
#include <cml/quaternion/traits.h>
#include <cml/quaternion/quaternion.h>

namespace cml {

/** Determine an appropriate storage type to use when combining quaternion
 * expressions via a pairwise binary operator.
 *
 * @note This can be specialized to accomodate user-defined storage types.
 */
template<class Storage1, class Storage2>
struct quaternion_binary_storage_promote
{
  static_assert(is_quaternion_storage<Storage1>::value
      && is_quaternion_storage<Storage2>::value,
    "expected quaternion storage types for binary promotion");

  /* Determine the common unbound storage type: */
  using unbound_type = storage_promote_t<Storage1, Storage2>;

  /* Resize: */
  using resized_type = resize_storage_t<unbound_type, 4>;

  /* Rebind to a quaternion storage type: */
  using type = rebind_quaternion_storage_t<resized_type>;
};

/** Convenience alias for quaternion_binary_storage_promote. */
template<class Storage1, class Storage2>
using quaternion_binary_storage_promote_t =
  typename quaternion_binary_storage_promote<Storage1, Storage2>::type;


/** Helper to deduce a reasonable quaternion type from two quaternion
 * subexpression types.  This can be specialized for non-default behavior.
 */
template<class Sub1, class Sub2, class Enable = void> struct quaternion_promote;

template<class Sub1, class Sub2>
struct quaternion_promote<Sub1, Sub2,
  typename std::enable_if<is_quaternion<Sub1>::value
    && is_quaternion<Sub2>::value>::type>
{
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = quaternion_traits<left_type>;
  using right_traits = quaternion_traits<right_type>;

  /* Deduce the new quaternion element type: */
  using value_type = value_type_promote_t<left_traits, right_traits>;

  /* Determine the new storage type: */
  using storage_type = quaternion_binary_storage_promote_t<storage_type_of_t<left_traits>,
    storage_type_of_t<right_traits>>;

  /* Use the proxy type for the temporary: */
  using proxy_type = proxy_type_of_t<storage_type>;

  /* Determine the common order type: */
  using order_type = order_type_promote_t<order_type_of_t<left_traits>,
    order_type_of_t<right_traits>>;

  /* Determine the common cross type: */
  using cross_type = cross_type_promote_t<cross_type_of_t<left_traits>,
    cross_type_of_t<right_traits>>;

  /* Build the quaternion type: */
  using type = quaternion<value_type, proxy_type, order_type, cross_type>;
};

/** Convenience alias for quaternion_promote<>. */
template<class Sub1, class Sub2>
using quaternion_promote_t = typename quaternion_promote<Sub1, Sub2>::type;

}  // namespace cml
