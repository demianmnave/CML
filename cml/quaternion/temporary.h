/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/temporary.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/quaternion/traits.h>
#include <cml/quaternion/quaternion.h>

namespace cml {

/** Deduce a temporary for a quaternion expression. */
template<class Quaternion>
struct temporary_of<Quaternion, cml::enable_if_quaternion_t<Quaternion>>
{
  using quaternion_type = cml::unqualified_type_t<Quaternion>;

  /* Propagate the element type of the original quaternion: */
  using traits_type = quaternion_traits<quaternion_type>;
  using value_type = typename traits_type::value_type;
  using storage_type = typename traits_type::storage_type;
  using order_type = typename traits_type::order_type;
  using cross_type = typename traits_type::cross_type;

  /* Need the proxy for the storage type: */
  using proxy_type = proxy_type_of_t<storage_type>;

  /* Build the temporary: */
  using type = quaternion<value_type, proxy_type, order_type, cross_type>;
};

}  // namespace cml
