/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>
#include <cml/vector/writable_vector.h>

namespace cml::detail {
/** Helper to return the passed-in value in response to a vector index @c
 * i.
 */
template<class Other,
  typename = std::enable_if_t<!cml::is_vector<Other>::value>>
auto
get(const Other& v, int) -> const Other&
{
  return v;
}

/** Helper to return element @c j of @c array. */
template<class Other, int N>
auto
get(Other const (&array)[N], int i) -> const Other&
{
  return array[i];
}

/** Helper to return element @c i of @c array. */
template<class Other, int N>
auto
get(Other (&array)[N], int i) -> Other&
{
  return array[i];
}

/** Helper to return element @c i of @c sub. */
template<class Sub>
auto
get(const readable_vector<Sub>& sub, int i) ->
  typename vector_traits<Sub>::immutable_value
{
  return sub.get(i);
}

template<class Sub>
auto
get(writable_vector<Sub>& sub, int i) ->
  typename vector_traits<Sub>::mutable_value
{
  return sub.get(i);
}

}  // namespace cml::detail
