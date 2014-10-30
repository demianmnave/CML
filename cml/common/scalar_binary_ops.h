/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_binary_ops_h
#define	cml_common_scalar_binary_ops_h

#include <cml/common/scalar_promotion.h>

namespace cml {
namespace op {

/** Binary minus (subtraction). */
template<class Scalar1, class Scalar2> struct binary_minus {
  typedef typename scalar_promote<Scalar1, Scalar2>::scalar_type result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a-b; }
};

/** Binary plus (addition). */
template<class Scalar1, class Scalar2> struct binary_plus {
  typedef typename scalar_promote<Scalar1, Scalar2>::scalar_type result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a+b; }
};

/** Binary multiply. */
template<class Scalar1, class Scalar2> struct binary_multiply {
  typedef typename scalar_promote<Scalar1, Scalar2>::scalar_type result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a*b; }
};

/** Binary divide. */
template<class Scalar1, class Scalar2> struct binary_divide {
  typedef typename scalar_promote<Scalar1, Scalar2>::scalar_type result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a/b; }
};

} // namespace op
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
