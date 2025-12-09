/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <type_traits>

namespace cml {
namespace detail {
/** Helper defining a typedef @c type that is int if @c T is an integral
 * type, or @c T otherwise.
 */
template<class T> struct int_if_integral
{
  using type =
  std::conditional_t<std::is_integral_v<T>, int, T>;
};
}  // namespace detail


/** Specializable compile-time array size. */
template<class Array, class Enable = void> struct array_size_of_c;

/** Specializable compile-time array row count. */
template<class Array, class Enable = void> struct array_rows_of_c;

/** Specializable compile-time array row count. */
template<class Array, class Enable = void> struct array_cols_of_c;

/** Compile-time size of an array. */
template<class Array>
struct array_size_of_c<Array,
    std::enable_if_t<std::is_array_v<Array>>>
{
  static const int value = int(std::extent_v<Array>);
};

/** Compile-time size of an object implementing an array_size integral or
 * enum member.
 */
template<class Array>
struct array_size_of_c<Array,
    std::enable_if_t<Array::array_size == Array::array_size>>
{
  static const int value = Array::array_size;
};

/** Return the size of @c array if it implements the size() method. */
template<class Array>
auto
array_size_of(const Array& array) ->
  typename detail::int_if_integral<decltype(array.size())>::type
{
  using result_type =
    typename detail::int_if_integral<decltype(array.size())>::type;
  return result_type(array.size());
}

/** Return the size of a fixed-length array. */
template<class Array>
int
array_size_of(const Array&,
  std::enable_if_t<std::is_array_v<Array>>* = 0)
{
  return int(array_size_of_c<Array>::value);
}

/** Compile-time size of an object implementing an array_rows integral or
 * enum member.
 */
template<class Array>
struct array_rows_of_c<Array,
    std::enable_if_t<Array::array_rows == Array::array_rows>>
{
  static const int value = int(Array::array_rows);
};

template<class Array>
constexpr auto array_rows_of_v = array_rows_of_c<Array>::value;

/** Compile-time size of an object implementing an array_cols integral or
 * enum member.
 */
template<class Array>
struct array_cols_of_c<Array,
    std::enable_if_t<Array::array_cols == Array::array_cols>>
{
  static const int value = int(Array::array_cols);
};

template<class Array>
constexpr auto array_cols_of_v = array_cols_of_c<Array>::value;

/** Return the number of rows of @c array if it implements the rows()
 * method.
 */
template<class Array>
auto
array_rows_of(const Array& array) -> decltype(array.rows())
{
  return array.rows();
}

/** Return the number of columns @c array if it implements the cols()
 * method.
 */
template<class Array>
auto
array_cols_of(const Array& array) -> decltype(array.cols())
{
  return array.cols();
}
}  // namespace cml
