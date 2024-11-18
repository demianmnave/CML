/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/type_util.h>
#include <cml/scalar/traits.h>

namespace cml {
namespace op {

/** Unary minus (negation). */
template<class Scalar> struct unary_minus
{
  using value_type = value_type_trait_of_t<Scalar>;
  using result_type = decltype(-value_type());

  result_type apply(const value_type& v) const { return -v; }
};

/** Unary plus. */
template<class Scalar> struct unary_plus
{
  using value_type = value_type_trait_of_t<Scalar>;
  using result_type = decltype(+value_type());

  result_type apply(const value_type& v) const { return +v; }
};

}  // namespace op

/** Convenience alias to create unary_minus from the value_type trait of
 * @c Sub as an unqualified type.
 */
template<class Sub>
using unary_minus_t =
  op::unary_minus<value_type_trait_of_t<actual_type_of_t<Sub>>>;

/** Convenience alias to create unary_plus from the value_type trait of
 * @c Sub as an unqualified type.
 */
template<class Sub>
using unary_plus_t =
  op::unary_plus<value_type_trait_of_t<actual_type_of_t<Sub>>>;

}  // namespace cml
