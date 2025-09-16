/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <algorithm>
#include <random>
#include <cml/scalar/constants.h>
#include <cml/scalar/traits.h>

namespace cml {

/** Sign (-1, 0, 1) of @c value as type @c T. */
template<typename T>
constexpr T
sign(T value)
{
  return value < T(0) ? (-T(1)) : (value > T(0) ? T(1) : T(0));
}

/** Clamp input value to the range [min, max]. */
template<typename T>
constexpr T
clamp(T value, T min, T max)
{
  return std::max((std::min)(value, max), min);
}

/** Wrap input value to the range [min,max]. */
template<typename T>
T
wrap(T value, T min, T max)
{
  max -= min;
  value = scalar_traits<T>::fmod(value - min, max);
  if(value < T(0)) value += max;
  return min + value;
}

/** Test input value for inclusion in [min, max]. */
template<typename T>
constexpr bool
in_range(T value, T min, T max)
{
  return !(value < min) && !(value > max);
}

/** Map input value from [min1, max1] to [min2, max2]. */
template<typename T>
constexpr T
map_range(T value, T min1, T max1, T min2, T max2)
{
  return min2 + ((value - min1) / (max1 - min1)) * (max2 - min2);
}

/** Wrap scalar_traits<T>::acos() and clamp argument to [-1, 1]. */
template<typename T>
T
acos_safe(T theta)
{
  return T(scalar_traits<T>::acos(clamp(theta, T(-1), T(1))));
}

/** Wrap scalar_traits<T>::asin() and clamp argument to [-1, 1]. */
template<typename T>
T
asin_safe(T theta)
{
  return T(scalar_traits<T>::asin(clamp(theta, T(-1), T(1))));
}

/** Wrap scalar_traits<T>::sqrt() and clamp argument to [0, inf). */
template<typename T>
T
sqrt_safe(T value)
{
  return T(scalar_traits<T>::sqrt(std::max(value, T(0))));
}

/** Square a value. */
template<typename T>
constexpr T
sqr(T value)
{
  return value * value;
}

/** Cube a value. */
template<typename T>
constexpr T
cub(T value)
{
  return value * value * value;
}

/** Inverse square root. */
template<typename T>
T
inv_sqrt(T value)
{
  return T(1) / scalar_traits<T>::sqrt(value);
}

/** Convert radians to degrees. */
template<typename T>
constexpr T
deg(T theta)
{
  return theta * constants<T>::deg_per_rad();
}

/** Convert degrees to radians. */
template<typename T>
constexpr T
rad(T theta)
{
  return theta * constants<T>::rad_per_deg();
}

/** Uniformly random integer in the range [min, max]. */
template<typename T>
T
random_integer(T min, T max)
{
  static std::random_device rd;
  static std::default_random_engine gen(rd());
  static std::uniform_int_distribution<T> dis(min, max);
  return dis(gen);
}

/** Uniformly random binary (0,1) value. */
inline int
random_binary()
{
  return random_integer<int>(0, 1);
}

/** Uniformly random polar (-1,1) value. */
inline int
random_polar()
{
  return random_binary() ? 1 : -1;
}

/* Uniformly distributed random real number in the range [min, max] */
template<typename T>
T
random_real(T min, T max)
{
  static std::random_device rd;
  static std::default_random_engine gen(rd());
  static std::uniform_real_distribution<T> dis(min, max);
  return dis(gen);
}

/** Uniformly distributed random real in [0,1]. */
inline double
random_unit()
{
  return random_real<double>(0., 1.);
}

/** Squared length in R2. */
template<typename T>
constexpr T
length_squared(T x, T y)
{
  return x * x + y * y;
}

/** Squared length in R3. */
template<typename T>
constexpr T
length_squared(T x, T y, T z)
{
  return x * x + y * y + z * z;
}

/** Length in R2. */
template<typename T>
T
length(T x, T y)
{
  return scalar_traits<T>::sqrt(length_squared(x, y));
}

/** Length in R3. */
template<typename T>
T
length(T x, T y, T z)
{
  return scalar_traits<T>::sqrt(length_squared(x, y, z));
}

/** @defgroup cml_scalar_indexing Indexing Functions
 *
 * The next few functions deal with indexing. next() and prev() are useful
 * for operations involving the vertices of a polygon or other cyclic set,
 * and cyclic_permutation() is used by various functions that deal with
 * axes or basis vectors in a generic way. As these functions are only
 * relevant for unsigned integer types, I've just used int, but there
 * may be reasons I haven't thought of that they should be templated.
 */
/*@{*/

/** Return next, with cycling, in a series of N non-negative integers. */
constexpr int
next(int i, int N)
{
  return (i + 1) % N;
}

/** Return previous, with cycling, in a series of N non-negative integers. */
constexpr int
prev(int i, int N)
{
  return i ? (i - 1) : (N - 1);
}

/** Cyclic permutation of the set { 0, 1 }, starting with 'first'. */
inline void
cyclic_permutation(int first, int& i, int& j)
{
  i = first;
  j = next(i, 2);
}

/** Cyclic permutation of the set { 0, 1, 2 }, starting with 'first'. */
inline void
cyclic_permutation(int first, int& i, int& j, int& k)
{
  i = first;
  j = next(i, 3);
  k = next(j, 3);
}

/** Cyclic permutation of the set { 0, 1, 2, 3 }, starting with 'first'. */
inline void
cyclic_permutation(int first, int& i, int& j, int& k, int& l)
{
  i = first;
  j = next(i, 4);
  k = next(j, 4);
  l = next(k, 4);
}

/*@}*/


namespace detail {

/** Base case for index-of based on a binary classifier.
 *
 * @note @c Op must induce a partial ordering over @c T.
 */
template<typename Op, int I0, int I1, typename T>
constexpr auto
index_of_helper(Op f, std::integer_sequence<int, I0, I1>, T x0, T x1) -> int
{
  return f(x0, x1) ? I0 : I1;
}

/** Recursive index-of based on a binary classifier.
 *
 * @note @c Op must induce a partial ordering over @c T.
 */
template<typename Op, int I0, int I1, typename T, typename... Ts, int... Is>
constexpr auto
index_of_helper(Op f, std::integer_sequence<int, I0, I1, Is...>, T x0, T x1,
  Ts... x) -> int
{
  return f(x0, x1)
    // Proceed to the next element of Ts with (x0,I0) satisfying f(...):
    ? index_of_helper(f, std::integer_sequence<int, I0, Is...>{}, x0, x...)
    // Proceed to the next element of Ts with (x1,I1) satisfying f(...):
    : index_of_helper(f, std::integer_sequence<int, I1, Is...>{}, x1, x...);
}

}  // namespace detail

/** Index of the minimum of N values. */
template<typename... Ts>
constexpr auto
index_of_min(Ts... x) -> int
{
  return detail::index_of_helper(std::less<>(),
    std::make_integer_sequence<int, sizeof...(Ts)>{}, x...);
}

/** Index of the minimum magnitude of N values. */
template<typename... Ts>
constexpr auto
index_of_min_abs(Ts... x) -> int
{
  return detail::index_of_helper(std::less<>(),
    std::make_integer_sequence<int, sizeof...(Ts)>{},
    cml::traits_of_t<decltype(x)>::abs(x)...);
}

/** Index of the maximum of N values. */
template<typename... Ts>
constexpr auto
index_of_max(Ts... x) -> int
{
  return detail::index_of_helper(std::greater<>(),
    std::make_integer_sequence<int, sizeof...(Ts)>{}, x...);
}

/** Index of the maximum magnitude of N values. */
template<typename... Ts>
constexpr auto
index_of_max_abs(Ts... x) -> int
{
  return detail::index_of_helper(std::greater<>(),
    std::make_integer_sequence<int, sizeof...(Ts)>{},
    cml::traits_of_t<decltype(x)>::abs(x)...);
}

}  // namespace cml
