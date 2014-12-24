/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_storage_promotion_h
#define	cml_storage_promotion_h

#include <cml/common/mpl/type_table.h>
#include <cml/storage/selectors.h>

namespace cml {

/** Build a storage type that best represents the combination of @c
 * Storage1 and @c Storage2 into a single type.
 *
 * @note This only supports built-in CML storage types, but can be
 * specialized for user-defined storage types.
 */
template<class Storage1, class Storage2>
struct storage_promote
{
  /* Map selector types to the preferred selector: */
  template<class S1, class S2, class S>
    using selector_map = type_table_item<S1, S2, S>;

  /* Build the symmetric type table for the built-in types: */
  typedef cml::type_table<
    /**/  selector_map< compiled<>,	compiled<>,	compiled<>	>
    ,     selector_map< compiled<>,	allocated<>,	compiled<>	>
    ,     selector_map< compiled<>,	external<>,	compiled<>	>
    ,     selector_map< compiled<>,	any_storage<>,	compiled<>	>
    ,     selector_map< allocated<>,	allocated<>,	allocated<>	>
    ,     selector_map< allocated<>,	external<>,	allocated<>	>
    ,     selector_map< allocated<>,	any_storage<>,	allocated<>	>
    ,     selector_map< external<>,	external<>,	external<>	>
    ,     selector_map< external<>,	any_storage<>,	external<>	>
    ,     selector_map< any_storage<>,	any_storage<>,	any_storage<>	>
    >							selector_table;

  /* Lookup the storage selector for the passed-in types: */
  typedef typename Storage1::selector_type		left_selector;
  typedef typename Storage2::selector_type		right_selector;
  typedef typename selector_table::find<
    left_selector, right_selector>::type		result;
  typedef typename result::type				selector_type;
  static_assert(result::value, "no common storage selector found");

  /* True if the resulting selector matches the left and/or right
   * selectors:
   */
  static const bool is_left
    = std::is_same<selector_type, left_selector>::value;
  static const bool is_right
    = std::is_same<selector_type, right_selector>::value;
  static const bool is_same = is_left && is_right;
  static_assert(is_left || is_right, "unexpected storage_promote result");

  /* Determine the final selector type: */
  typedef typename Storage1::unbound_type		left_unbound;
  typedef typename Storage2::unbound_type		right_unbound;
  typedef
    cml::if_t<is_same,		storage_disambiguate_t<Storage1, Storage2>,
    cml::if_t<is_left,		left_unbound,
    /*else is_right */		right_unbound>>	type;
};

/** Convenience alias for storage_selector_promote. */
template<class Storage1, class Storage2>
  using storage_promote_t = typename storage_promote<Storage1, Storage2>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
