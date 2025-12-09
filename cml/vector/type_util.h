/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/type_util.h>
#include <cml/vector/fwd.h>

namespace cml {
/** Defines typedef @c type as std::true_type if @c T is statically
 * polymorphic and derived from @c readable_vector, or std::false_type
 * otherwise.  The static bool @c value is set to true or false to match @c
 * type.
 */
template<class T> struct is_vector
{
  private:
  /* Strip const, volatile, and reference from T to get the type to test: */
  using naked_type = cml::unqualified_type_t<T>;

  /* Deduce the derived type (fails if T is not statically polymorphic): */
  using derived_type = actual_type_of_t<naked_type>;

  public:
  /* std::true_type if T is derived from readable_vector<>, std::false_type
   * otherwise:
   */
  using type = std::is_base_of<readable_vector<derived_type>, naked_type>;

  /* True or false, depending upon 'type': */
  static const bool value = type::value;
};

template<class T> constexpr auto is_vector_v = is_vector<T>::value;

/** Wrapper for enable_if to detect vector types (derived from
 * readable_vector).
 */
template<class Sub>
struct enable_if_vector : std::enable_if<is_vector<Sub>::value>
{
};

/** Convenience alias for enable_if_vector. */
template<class Sub>
using enable_if_vector_t = typename enable_if_vector<Sub>::type;
} // namespace cml
