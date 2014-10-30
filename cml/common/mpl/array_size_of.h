/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_array_size_of_h
#define	cml_common_mpl_array_size_of_h

#include <type_traits>

namespace cml {

/** Specializable compile-time array size, with SFINAE via enable_if. */
template<class Array, class Enable = void> struct array_size_of_c;

/** Compile-time size of an array. */
template<class Array> struct array_size_of_c<
  Array, typename std::enable_if<std::is_array<Array>::value>::type>
{
  static const int value = int(std::extent<Array>::value);
};

/** Compile-time size of an object implementing an array_size static
 * integral member.
 */
template<class Array> struct array_size_of_c<
  Array, typename std::enable_if<(Array::array_size>0)>::type>
{
  static const int value = Array::array_size;
};

/** Return the size of @c v if it implements the size() method. */
template<class Array> inline auto array_size_of(const Array& array)
  -> decltype(array.size(), int())
{
  return int(array.size());
}

/** Return the size of a fixed-length array. */
template<class Array> inline int array_size_of(const Array&,
  typename std::enable_if<std::is_array<Array>::value>::type* = 0)
{
  return cml::array_size_of_c<Array>::value;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
