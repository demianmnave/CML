/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_binary_ops_h
#define	cml_common_scalar_binary_ops_h

#include <cml/common/scalar_traits.h>
#include <cml/common/scalar_promotion.h>

namespace cml {
namespace op {

/** Binary minus (subtraction). */
template<class Scalar1, class Scalar2> struct binary_minus {
  typedef value_type_trait_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a-b; }
};

/** Binary plus (addition). */
template<class Scalar1, class Scalar2> struct binary_plus {
  typedef value_type_trait_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a+b; }
};

/** Binary multiply. */
template<class Scalar1, class Scalar2> struct binary_multiply {
  typedef value_type_trait_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a*b; }
};

/** Binary divide. */
template<class Scalar1, class Scalar2> struct binary_divide {
  typedef value_type_trait_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a/b; }
};

} // namespace op

/** Convenience alias to create binary_minus from the value_type traits of
 * @c Sub1 and @c Sub2 as unqualified types.
 */
template<class Sub1, class Sub2>
  using binary_minus_t = op::binary_minus<
    value_type_trait_of_t<actual_type_of_t<Sub1>>,
    value_type_trait_of_t<actual_type_of_t<Sub2>>>;

/** Convenience alias to create binary_plus from the value_type traits of
 * @c Sub1 and @c Sub2 as unqualified types.
 */
template<class Sub1, class Sub2>
  using binary_plus_t = op::binary_plus<
    value_type_trait_of_t<actual_type_of_t<Sub1>>,
    value_type_trait_of_t<actual_type_of_t<Sub2>>>;

/** Convenience alias to create binary_multiply from the value_type traits
 * of @c Sub1 and @c Sub2 as unqualified types.
 */
template<class Sub1, class Sub2>
  using binary_multiply_t = op::binary_multiply<
    value_type_trait_of_t<actual_type_of_t<Sub1>>,
    value_type_trait_of_t<actual_type_of_t<Sub2>>>;

/** Convenience alias to create binary_divide from the value_type traits
 * of @c Sub1 and @c Sub2 as unqualified types.
 */
template<class Sub1, class Sub2>
  using binary_divide_t = op::binary_divide<
    value_type_trait_of_t<actual_type_of_t<Sub1>>,
    value_type_trait_of_t<actual_type_of_t<Sub2>>>;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
