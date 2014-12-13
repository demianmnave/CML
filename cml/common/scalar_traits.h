/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_traits_h
#define	cml_common_scalar_traits_h

#include <cmath>
#include <cml/common/traits.h>
#include <cml/common/mpl/enable_if_arithmetic.h>

namespace cml {

/** Specializable class aggregating scalar properties.  The default is
 * valid for basic types (int, float, double, etc.).  If scalar_traits<> is
 * specialized for a particular type T, T must be default constructible and
 * assignable.
 */
template<typename Scalar> struct scalar_traits
{
  typedef Scalar					value_type;
  typedef value_type*					pointer;
  typedef value_type&					reference;
  typedef value_type const*				const_pointer;
  typedef value_type const&				const_reference;
  typedef value_type&					mutable_value;
  typedef value_type const				immutable_value;

  /** @name Basic Functions */
  /*@{*/

  static inline value_type fabs(const value_type& v) {
    return std::fabs(v);
  }

  static inline value_type fmod(const value_type& v, const value_type& w) {
    return std::fmod(v, w);
  }

  static inline value_type sqrt(const value_type& v) {
    return std::sqrt(v);
  }

  static inline value_type cos(const value_type& v) {
    return std::cos(v);
  }

  static inline value_type sin(const value_type& v) {
    return std::sin(v);
  }

  static inline value_type tan(const value_type& v) {
    return std::tan(v);
  }

  static inline value_type acos(const value_type& v) {
    return std::acos(v);
  }

  static inline value_type asin(const value_type& v) {
    return std::asin(v);
  }

  static inline value_type atan(const value_type& v) {
    return std::atan(v);
  }

  /*@}*/
};

/** traits_of for arithmetic scalars. */
template<class T> struct traits_of<T, cml::enable_if_arithmetic_t<T>> {
  typedef scalar_traits<T>				type;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
