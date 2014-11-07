/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_binary_ops_h
#define	cml_common_scalar_binary_ops_h

#include <cml/common/scalar_traits.h>

namespace cml {
namespace op {

#define __CML_BINARY_OP_PROMOTE(_S1_, _S2_, _sym_)			\
  decltype(typename scalar_traits<_S1_>::value_type()			\
    _sym_ typename scalar_traits<_S2_>::value_type())

/** Binary minus (subtraction). */
template<class Scalar1, class Scalar2> struct binary_minus {
  typedef __CML_BINARY_OP_PROMOTE(Scalar1, Scalar2, -) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a-b; }
};

/** Binary plus (addition). */
template<class Scalar1, class Scalar2> struct binary_plus {
  typedef __CML_BINARY_OP_PROMOTE(Scalar1, Scalar2, +) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a+b; }
};

/** Binary multiply. */
template<class Scalar1, class Scalar2> struct binary_multiply {
  typedef __CML_BINARY_OP_PROMOTE(Scalar1, Scalar2, *) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a*b; }
};

/** Binary divide. */
template<class Scalar1, class Scalar2> struct binary_divide {
  typedef __CML_BINARY_OP_PROMOTE(Scalar1, Scalar2, /) result_type;
  result_type apply(const Scalar1& a, const Scalar2& b) const { return a/b; }
};

#undef __CML_BINARY_OP_PROMOTE

} // namespace op
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
