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
  using std::numeric_limits<Scalar>::epsilon;

  /** @name Basic Functions */
  /*@{*/

  static value_type abs(const value_type& v) { return std::abs(v); }

  static value_type mod(const value_type& v, const value_type& w)
  {
    return v % w;
  }

  static value_type fabs(const value_type& v)
  {
    return static_cast<value_type>(std::fabs(static_cast<double>(v)));
  }

  static value_type fmod(const value_type& v, const value_type& w)
  {
    return static_cast<value_type>(std::fmod(static_cast<double>(v),
      static_cast<double>(w)));
  }

  static constexpr value_type sqrt(const value_type& v)
  {
    return static_cast<value_type>(std::sqrt(static_cast<double>(v)));
  }

  static value_type cos(const value_type& v)
  {
    return static_cast<value_type>(std::cos(static_cast<double>(v)));
  }

  static value_type sin(const value_type& v)
  {
    return static_cast<value_type>(std::sin(static_cast<double>(v)));
  }

  static value_type tan(const value_type& v)
  {
    return static_cast<value_type>(std::tan(static_cast<double>(v)));
  }

  static value_type acos(const value_type& v)
  {
    return static_cast<value_type>(std::acos(static_cast<double>(v)));
  }

  static value_type asin(const value_type& v)
  {
    return static_cast<value_type>(std::asin(static_cast<double>(v)));
  }

  static value_type atan(const value_type& v)
  {
    return static_cast<value_type>(std::atan(static_cast<double>(v)));
  }

  static value_type atan2(const value_type& x, const value_type& y)
  {
    return static_cast<value_type>(std::atan2(static_cast<double>(x),
      static_cast<double>(y)));
  }

  static value_type log(const value_type& v)
  {
    return static_cast<value_type>(std::log(static_cast<double>(v)));
  }

  static value_type exp(const value_type& v)
  {
    return static_cast<value_type>(std::exp(static_cast<double>(v)));
  }

  /** Returns 0. */
  static constexpr Scalar sqrt_epsilon() { return 0; }

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
  using std::numeric_limits<Scalar>::epsilon;

  /** @name Basic Functions */
  /*@{*/

  static value_type abs(const value_type& v) { return std::abs(v); }

  static value_type mod(const value_type& v, const value_type& w)
  {
    return std::fmod(v, w);
  }

  static value_type fabs(const value_type& v) { return std::fabs(v); }

  static value_type fmod(const value_type& v, const value_type& w)
  {
    return std::fmod(v, w);
  }

  static constexpr value_type sqrt(const value_type& v) { return std::sqrt(v); }

  static value_type cos(const value_type& v) { return std::cos(v); }

  static value_type sin(const value_type& v) { return std::sin(v); }

  static value_type tan(const value_type& v) { return std::tan(v); }

  static value_type acos(const value_type& v) { return std::acos(v); }

  static value_type asin(const value_type& v) { return std::asin(v); }

  static value_type atan(const value_type& v) { return std::atan(v); }

  static value_type atan2(const value_type& x, const value_type& y)
  {
    return std::atan2(x, y);
  }

  static value_type log(const value_type& v) { return std::log(v); }

  static value_type exp(const value_type& v) { return std::exp(v); }

  /*@}*/
};

}  // namespace detail


/** Specializable class aggregating scalar properties. */
template<typename Scalar, class Enable = void> struct scalar_traits;

/** Specialization of scalar_traits<> for integral types. */
template<typename Scalar>
struct scalar_traits<Scalar, std::enable_if_t<std::is_integral_v<Scalar>>>
: detail::default_integral_traits<Scalar>
{};

/** Specialization of scalar_traits<>::sqrt_epsilon() for generic floating-point types. */
template<typename Scalar>
struct scalar_traits<Scalar, std::enable_if_t<std::is_floating_point_v<Scalar>>>
: detail::default_floating_point_traits<Scalar>
{
  using detail::default_floating_point_traits<Scalar>::sqrt;
  using detail::default_floating_point_traits<Scalar>::epsilon;

  /** Returns sqrt(numeric_limits<Scalar>::epsilon()). */
  static Scalar sqrt_epsilon() { return sqrt(epsilon()); }
};

/** Specialization of scalar_traits<>::sqrt_epsilon() for float. */
template<>
struct scalar_traits<float> : detail::default_floating_point_traits<float>
{
  static constexpr float sqrt_epsilon()
  {
    return 3.452669831e-4f;  // 10 digits
  }
};

/** Specialization of scalar_traits<>::sqrt_epsilon() for double. */
template<>
struct scalar_traits<double> : detail::default_floating_point_traits<double>
{
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
