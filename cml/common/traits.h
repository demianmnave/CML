/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {

/** Specializable struct to obtain the traits of a specified class,
 * possibly using SFINAE.  Specializations should typedef "type" as the
 * traits class for @c T.
 */
template<class T, class = void> struct traits_of;

/** Instantiated if T does not have a defined traits type. */
template<class T, class = void> struct has_traits : std::false_type
{};

/** Instantiated if T has a defined traits type. */
template<class T>
struct has_traits<T, std::void_t<typename traits_of<T>::type>> : std::true_type
{};

/** True if T has a defined traits type, false otherwise. */
template<class T> static constexpr bool has_traits_v = has_traits<T>::value;

/** Helper alias for traits_of. */
template<class T> using traits_of_t = typename traits_of<T>::type;

/** @addtogroup container_traits */
/*@{*/

/** Retrieve the value_type of @c T via an embedded typedef. */
template<class T> struct value_type_of
{
  using type = typename T::value_type;
};

/** Convenience alias for value_type_of. */
template<class T> using value_type_of_t = typename value_type_of<T>::type;

/** Retrieve the value_type of @c T via traits.
 *
 * @note This applies to CML expression types, including scalars.
 */
template<class T> struct value_type_trait_of
{
  using type = typename traits_of_t<T>::value_type;
};

/** Convenience alias for value_type_trait_of. */
template<class T>
using value_type_trait_of_t = typename value_type_trait_of<T>::type;

/*@}*/
}  // namespace cml
