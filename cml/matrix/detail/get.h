/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/writable_matrix.h>

namespace cml::detail {

/** Helper to return the passed-in value in response to a matrix index @c
 * (i,j).
 */
template<class Other,
  typename = std::enable_if_t<!cml::is_matrix<Other>::value>>
auto
get(const Other& v, int, int) -> const Other&
{
  return v;
}

/** Helper to return element @c (i,j) of @c array. */
template<class Other, int Rows, int Cols>
auto
get(Other const (&array)[Rows][Cols], int i, int j) -> const Other&
{
  using array_type = cml::unqualified_type_t<decltype(array)>;
  if constexpr(has_traits_v<array_type>) {
    if constexpr(std::is_same_v<layout_tag_trait_of_t<array_type>, col_major>) {
      return array[j][i];
    } else {
      return array[i][j];
    }
  } else {
    return array[i][j];
  }
}

/** Helper to return element @c (i,j) of @c array. */
template<class Other, int Rows, int Cols>
auto
get(Other (&array)[Rows][Cols], int i, int j) -> Other&
{
  using array_type = cml::unqualified_type_t<decltype(array)>;
  if constexpr(has_traits_v<array_type>) {
    if constexpr(std::is_same_v<layout_tag_trait_of_t<array_type>, col_major>) {
      return array[j][i];
    } else {
      return array[i][j];
    }
  } else {
    return array[i][j];
  }
}

/** Helper to return element @c (i,j) of @c sub. */
template<class Sub>
auto
get(const readable_matrix<Sub>& sub, int i, int j) ->
  typename matrix_traits<Sub>::immutable_value
{
  return sub.get(i, j);
}

template<class Sub>
auto
get(writable_matrix<Sub>& sub, int i, int j) ->
  typename matrix_traits<Sub>::mutable_value
{
  return sub.get(i, j);
}

}  // namespace cml::detail
