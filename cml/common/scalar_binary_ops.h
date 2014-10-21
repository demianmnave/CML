/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_binary_ops_h
#define	cml_common_scalar_binary_ops_h

namespace cml {
namespace op {

/** Binary minus (subtraction).
 *
 * @note Type deduction for Scalar1-Scalar2 uses C++ rules for built-in
 * types, or user-defined rules via operator-().
 */
template<class Scalar1, class Scalar2> struct binary_minus {
  typedef decltype(Scalar1() - Scalar2()) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a-b; }
};

/** Binary plus (addition).
 *
 * @note Type deduction for Scalar1+Scalar2 uses C++ rules for built-in
 * types, or user-defined rules via operator+().
 */
template<class Scalar1, class Scalar2> struct binary_plus {
  typedef decltype(Scalar1() + Scalar2()) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a+b; }
};

/** Binary multiply.
 *
 * @note Type deduction for Scalar1*Scalar2 uses C++ rules for built-in
 * types, or user-defined rules via operator*().
 */
template<class Scalar1, class Scalar2> struct binary_multiply {
  typedef decltype(Scalar1() * Scalar2()) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a*b; }
};

/** Binary divide.
 *
 * @note Type deduction for Scalar1/Scalar2 uses C++ rules for built-in
 * types, or user-defined rules via operator/().
 */
template<class Scalar1, class Scalar2> struct binary_divide {
  typedef decltype(Scalar1() / Scalar2()) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a/b; }
};

} // namespace op
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
