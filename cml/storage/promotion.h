/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/type_table.h>
#include <cml/storage/selectors.h>

namespace cml {
/** Build a storage type that best represents the combination of @c
 * Storage1 and @c Storage2 into a single type.
 *
 * @note This only supports built-in CML storage types, but can be
 * specialized for user-defined storage types.
 */
template<class Storage1, class Storage2, bool PreferDynamic = false>
struct storage_promote
{
  /* Map selector types to the preferred selector: */
  template<class S1, class S2, class S>
  using selector_map = type_table_item<S1, S2, S>;

  /* True if PreferDynamic is false, or if both Storage1 and Storage2 are
   * fixed-size types:
   */
  static constexpr bool is_fixed = !PreferDynamic
    || (is_fixed_size<Storage1>::value && is_fixed_size<Storage2>::value);

  /* Build the symmetric type table for the built-in types, giving
   * preference to dynamic-size types if PreferDynamic is true:
   */
  using selector_table = cml::type_table<
    /**/ selector_map<compiled<>, compiled<>, compiled<>>

    /* Override and select allocated<> if PreferDynamic is true and the
     * original storage types are not both fixed-size:
     */
    ,
    selector_map<compiled<>, allocated<>,
      cml::if_t<is_fixed, compiled<>, allocated<>>>

    /* Override and select external<> if PreferDynamic is true and the
     * original storage types are not both fixed-size:
     */
    ,
    selector_map<compiled<>, external<>,
      cml::if_t<is_fixed, compiled<>, external<>>>

    ,
    selector_map<compiled<>, any_storage<>, compiled<>>

    ,
    selector_map<allocated<>, allocated<>, allocated<>>

    ,
    selector_map<allocated<>, external<>, allocated<>>

    ,
    selector_map<allocated<>, any_storage<>, allocated<>>

    ,
    selector_map<external<>, external<>, external<>>

    ,
    selector_map<external<>, any_storage<>, external<>>

    ,
    selector_map<any_storage<>, any_storage<>, any_storage<>>>;

  /* Lookup the storage selector for the passed-in types: */
  using left_selector = typename Storage1::selector_type;
  using right_selector = typename Storage2::selector_type;
  using result =
    typename selector_table::template find<left_selector, right_selector>::type;
  using selector_type = typename result::type;
  static_assert(result::value, "no common storage selector found");

  /* True if the resulting selector matches the left and/or right
   * selectors:
   */
  static constexpr bool is_left = std::is_same_v<selector_type, left_selector>;
  static constexpr bool is_right =
    std::is_same_v<selector_type, right_selector>;
  static constexpr bool is_same = is_left && is_right;
  static_assert(is_left || is_right, "unexpected storage_promote result");

  /* Determine the final selector type: */
  using left_unbound = typename Storage1::unbound_type;
  using right_unbound = typename Storage2::unbound_type;
  using type = cml::if_t<is_same, storage_disambiguate_t<Storage1, Storage2>,
    cml::if_t<is_left, left_unbound,
      /*else is_right */ right_unbound>>;
};

/** Convenience alias for storage_selector_promote. */
template<class Storage1, class Storage2, bool PreferDynamic = false>
using storage_promote_t =
  typename storage_promote<Storage1, Storage2, PreferDynamic>::type;
}  // namespace cml
