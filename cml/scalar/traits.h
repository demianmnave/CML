/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cmath>
#include <limits>
#include <cml/common/mpl/enable_if_arithmetic.h>
#include <cml/common/temporary.h>
#include <cml/common/traits.h>

namespace cml {
namespace detail {

/** Inheritable default scalar traits for integral types.  If
 * scalar_traits<> is specialized for a particular type T, T must be
 * default constructible and assignable.
 *
 * @note For the std:: numeric functions, @c Scalar is promoted to double
 * by default.
 *
 * @note default_integral_traits inherits from std::numeric_limits by default.
 */
template<typename Scalar>
struct default_integral_traits : std::numeric_limits<Scalar>
{
  using value_type = Scalar;
  using pointer = value_type*;
  using reference = value_type&;
  using const_pointer = value_type const*;
  using const_reference = value_type const&;
  using mutable_value = reference&;
  using immutable_value = const_reference;

  /** @name Basic Functions */
  /*@{*/

  static inline value_type fabs(const value_type& v)
  {
    return (value_type) std::fabs(double(v));
  }

  static inline value_type fmod(const value_type& v, const value_type& w)
  {
    return (value_type) std::fmod(double(v), double(w));
  }

  static constexpr value_type sqrt(const value_type& v)
  {
    return (value_type) std::sqrt(double(v));
  }

  static inline value_type cos(const value_type& v)
  {
    return (value_type) std::cos(double(v));
  }

  static inline value_type sin(const value_type& v)
  {
    return (value_type) std::sin(double(v));
  }

  static inline value_type tan(const value_type& v)
  {
    return (value_type) std::tan(double(v));
  }

  static inline value_type acos(const value_type& v)
  {
    return (value_type) std::acos(double(v));
  }

  static inline value_type asin(const value_type& v)
  {
    return (value_type) std::asin(double(v));
  }

  static inline value_type atan(const value_type& v)
  {
    return (value_type) std::atan(double(v));
  }

  static inline value_type atan2(const value_type& x, const value_type& y)
  {
    return (value_type) std::atan2(double(x), double(y));
  }

  static inline value_type log(const value_type& v)
  {
    return (value_type) std::log(double(v));
  }

  static inline value_type exp(const value_type& v)
  {
    return (value_type) std::exp(double(v));
  }

  /*@}*/
};

/** Inheritable default scalar traits for floating point types.  If
 * scalar_traits<> is specialized for a particular type T, T must be
 * default constructible and assignable.
 *
 * @note default_scalar_traits inherits from std::numeric_limits by default.
 */
template<typename Scalar>
struct default_floating_point_traits : std::numeric_limits<Scalar>
{
  using value_type = Scalar;
  using pointer = value_type*;
  using reference = value_type&;
  using const_pointer = value_type const*;
  using const_reference = value_type const&;
  using mutable_value = reference&;
  using immutable_value = const_reference;

  /** @name Basic Functions */
  /*@{*/

  static inline value_type fabs(const value_type& v) { return std::fabs(v); }

  static inline value_type fmod(const value_type& v, const value_type& w)
  {
    return std::fmod(v, w);
  }

  static constexpr value_type sqrt(const value_type& v) { return std::sqrt(v); }

  static inline value_type cos(const value_type& v) { return std::cos(v); }

  static inline value_type sin(const value_type& v) { return std::sin(v); }

  static inline value_type tan(const value_type& v) { return std::tan(v); }

  static inline value_type acos(const value_type& v) { return std::acos(v); }

  static inline value_type asin(const value_type& v) { return std::asin(v); }

  static inline value_type atan(const value_type& v) { return std::atan(v); }

  static inline value_type atan2(const value_type& x, const value_type& y)
  {
    return std::atan2(x, y);
  }

  static inline value_type log(const value_type& v) { return std::log(v); }

  static inline value_type exp(const value_type& v) { return std::exp(v); }

  /*@}*/
};

}  // namespace detail


/** Specializable class aggregating scalar properties. */
template<typename Scalar, class Enable = void> struct scalar_traits;

/** Specialization of scalar traits for integral types. */
template<typename Scalar>
struct scalar_traits<Scalar,
  typename std::enable_if<std::is_integral<Scalar>::value>::type>
: detail::default_integral_traits<Scalar>
{
  /** Returns 0. */
  static constexpr Scalar sqrt_epsilon() { return 0; }
};

/** Specialization of scalar_traits for floating-point types. */
template<typename Scalar>
struct scalar_traits<Scalar,
  typename std::enable_if<std::is_floating_point<Scalar>::value>::type>
: detail::default_floating_point_traits<Scalar>
{
  /** Returns sqrt(numeric_limits<float>::epsilon()). */
  static constexpr double sqrt_epsilon()
  {
    return detail::default_floating_point_traits<Scalar>::sqrt(
      std::numeric_limits<Scalar>::epsilon());
  }
};

/** Specialization of scalar_traits for float. */
template<>
struct scalar_traits<float> : detail::default_floating_point_traits<float>
{
  /** Returns a constant for sqrt(numeric_limits<float>::epsilon()). */
  static constexpr float sqrt_epsilon()
  {
    return 3.452669831e-4f;  // 10 digits
  }
};

/** Specialization of scalar_traits for double. */
template<>
struct scalar_traits<double> : detail::default_floating_point_traits<double>
{
  /** Returns a constant for sqrt(numeric_limits<double>::epsilon()). */
  static constexpr double sqrt_epsilon()
  {
    return 1.49011611938476563e-8;  // 18 digits
  }
};

/** Returns eps for type S. */
template<typename S>
constexpr S
epsilon()
{
  return scalar_traits<S>::epsilon();
}

/** Returns sqrt(eps) for type S. */
template<typename S>
constexpr S
sqrt_epsilon()
{
  return scalar_traits<S>::sqrt_epsilon();
}

/** traits_of for arithmetic scalars. */
template<class T> struct traits_of<T, enable_if_arithmetic_t<T>>
{
  using type = scalar_traits<T>;
};

/** temporary_of for arithmetic scalars. */
template<class Scalar>
struct temporary_of<Scalar, cml::enable_if_arithmetic_t<Scalar>>
{
  using type = cml::value_type_trait_of_t<Scalar>;
};

}  // namespace cml
