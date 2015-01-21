/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_scalar_traits_h
#define	cml_scalar_traits_h

#include <cmath>
#include <limits>
#include <cml/common/mpl/enable_if_arithmetic.h>
#include <cml/common/traits.h>

namespace cml {
namespace detail {

/** Inheritable default scalar traits.  The default is valid for basic
 * types (int, float, double, etc.).  If scalar_traits<> is specialized for
 * a particular type T, T must be default constructible and assignable.
 *
 * @note default_scalar_traits inherits from std::numeric_limits by default.
 */
template<typename Scalar> struct default_scalar_traits
: std::numeric_limits<Scalar>
{
  typedef Scalar					value_type;
  typedef value_type*					pointer;
  typedef value_type&					reference;
  typedef value_type const*				const_pointer;
  typedef value_type const&				const_reference;
  typedef reference&					mutable_value;
  typedef const_reference				immutable_value;

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

  static inline value_type atan2(const value_type& x, const value_type& y) {
    return std::atan2(x,y);
  }

  /*@}*/
};

} // namespace detail


/** Specializable class aggregating scalar properties. */
template<typename Scalar, class Enable = void> struct scalar_traits;

/** Specialization of scalar traits for integral types. */
template<typename Scalar> struct scalar_traits<
Scalar, typename std::enable_if<std::is_integral<Scalar>::value>::type>
: detail::default_scalar_traits<Scalar>
{
  /** Returns 0. */
  static inline Scalar sqrt_epsilon() { return 0; }
};

/** Specialization of scalar_traits for floating-point types. */
template<typename Scalar> struct scalar_traits<
Scalar, typename std::enable_if<std::is_floating_point<Scalar>::value>::type>
: detail::default_scalar_traits<Scalar>
{
  /** Returns sqrt(numeric_limits<float>::epsilon()). */
  static inline double sqrt_epsilon() {
    static double _s = detail::default_scalar_traits<Scalar>::sqrt(
      std::numeric_limits<Scalar>::epsilon());
    return _s;
  }
};


/** traits_of for arithmetic scalars. */
template<class T> struct traits_of<T, enable_if_arithmetic_t<T>> {
  typedef scalar_traits<T>				type;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
