/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_scalar_ops_h
#define	cml_vector_scalar_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/vector/scalar_node.h>

namespace cml {

/** Return an expression node for scalar multiplication of
 * the elements of the sub-expressions @c sub by @c v.
 */
template<class Sub, class Scalar> auto
operator*(const readable_vector<Sub>& sub, const Scalar& v)
-> vector_scalar_node<Sub, Scalar,
  op::binary_multiply<typename Sub::value_type, Scalar>>;

/** Return an expression node for scalar multiplication @c v by the
 * elements of the sub-expressions @c sub.
 */
template<class Scalar, class Sub> auto
operator*(const Scalar& v, const readable_vector<Sub>& sub)
-> vector_scalar_node<Sub, Scalar,
  op::binary_multiply<typename Sub::value_type, Scalar>>;

/** Return an expression node for scalar division of
 * the elements of the sub-expressions @c sub by @c v.
 */
template<class Sub, class Scalar> auto
operator/(const readable_vector<Sub>& sub, const Scalar& v)
-> vector_scalar_node<Sub, Scalar,
  op::binary_divide<typename Sub::value_type, Scalar>>;

} // namespace cml

#define __CML_VECTOR_SCALAR_OPS_TPP
#include <cml/vector/scalar_ops.tpp>
#undef __CML_VECTOR_SCALAR_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
