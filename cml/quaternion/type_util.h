/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/type_util.h>
#include <cml/quaternion/fwd.h>

namespace cml {
/** Defines typedef @c type as std::true_type if @c T is statically
 * polymorphic and derived from @c readable_quaternion, or std::false_type
 * otherwise.  The static bool @c value is set to true or false to match @c
 * type.
 */
template<class T> struct is_quaternion
{
  private:
  /* Strip const, volatile, and reference from T to get the type to test: */
  using naked_type = cml::unqualified_type_t<T>;

  /* Deduce the derived type (fails if T is not statically polymorphic): */
  using derived_type = actual_type_of_t<naked_type>;

  public:
  /* std::true_type if T is derived from readable_quaternion<>, std::false_type
   * otherwise:
   */
  using type = std::is_base_of<readable_quaternion<derived_type>, naked_type>;

  /* True or false, depending upon 'type': */
  static const bool value = type::value;
};

/** Wrapper for enable_if to detect quaternion types (derived from
 * readable_quaternion).
 */
template<class Sub>
struct enable_if_quaternion : std::enable_if<is_quaternion<Sub>::value>
{
};

/** Convenience alias for enable_if_quaternion. */
template<class Sub>
using enable_if_quaternion_t = typename enable_if_quaternion<Sub>::type;
} // namespace cml
