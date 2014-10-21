/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_unary_ops_h
#define	cml_common_scalar_unary_ops_h

namespace cml {
namespace op {

/** Unary minus (negation). */
template<class Scalar> struct unary_minus {
  typedef Scalar value_type;
  typedef decltype(- Scalar()) result_type;
  result_type apply(const value_type& v) const { return - v; }
};

/** Unary plus. */
template<class Scalar> struct unary_plus {
  typedef Scalar value_type;
  typedef decltype(+ Scalar()) result_type;
  result_type apply(const value_type& v) const { return + v; }
};

} // namespace op
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
