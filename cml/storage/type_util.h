/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_storage_type_util_h
#define	cml_storage_type_util_h

#include <cml/common/mpl/rebind.h>

namespace cml {

/** Specializable class to detect storage selectors. */
template<class T> struct is_storage_selector {
  static const bool value = false;
};

/** Templated helper to determine the storage selector of @c T. @c T must
 * implement a selector_type typedef.
 */
template<class T> struct storage_selector_of {
  typedef typename T::selector_type type;
  static_assert(is_storage_selector<type>::value, "invalid storage selector");
};

/** Convenience alias for storage_selector_of. */
template<class T> using storage_selector_of_t
  = typename storage_selector_of<T>::type;

/** Templated helper to determine the storage type of @c T. @c T must
 * implement a storage_type typedef.
 */
template<class T> struct storage_type_of {
  typedef typename T::storage_type type;
};

/** Convenience alias for storage_type_of. */
template<class T> using storage_type_of_t
  = typename storage_type_of<T>::type;

/** Specializable class used to disambiguate configurable storage types @c
 * Storage1 and @c Storage2 that have matching storage selectors.
 *
 * @note This should be specialized for user-defined storage types.
 */
template<class Storage1, class Storage2> struct storage_disambiguate {
  typedef void						type;
};

/** Convenience alias for storage_disambiguate. */
template<class Storage1, class Storage2> using storage_disambiguate_t
  = typename storage_disambiguate<Storage1, Storage2>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
