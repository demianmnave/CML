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

template<class Scalar1, class Scalar2> using scalar_value_promote
  = cml::value_type_promote<scalar_traits<Scalar1>, scalar_traits<Scalar2>>;

template<class Scalar1, class Scalar2> using scalar_value_promote_t
  = typename scalar_value_promote<Scalar1,Scalar2>::type;

/** Binary minus (subtraction). */
template<class Scalar1, class Scalar2> struct binary_minus {
  typedef scalar_value_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a-b; }
};

/** Binary plus (addition). */
template<class Scalar1, class Scalar2> struct binary_plus {
  typedef scalar_value_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a+b; }
};

/** Binary multiply. */
template<class Scalar1, class Scalar2> struct binary_multiply {
  typedef scalar_value_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a*b; }
};

/** Binary divide. */
template<class Scalar1, class Scalar2> struct binary_divide {
  typedef scalar_value_promote_t<Scalar1,Scalar2> result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a/b; }
};

} // namespace op
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
