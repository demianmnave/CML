/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_unary_ops_h
#define	cml_vector_unary_ops_h

#include <cml/common/scalar_unary_ops.h>
#include <cml/vector/unary_node.h>

namespace cml {

/** Return an expression node for unary minus over the elements of the
 * sub-expression @c sub.
 */
template<class Sub> auto operator-(const readable_vector<Sub>& sub)
-> vector_unary_node<Sub, op::unary_minus<typename Sub::value_type>>;

/** Return an expression node for unary plus over the elements of the
 * sub-expression @c sub.
 */
template<class Sub> auto operator+(const readable_vector<Sub>& sub)
-> vector_unary_node<Sub, op::unary_plus<typename Sub::value_type>>;

} // namespace cml

#define __CML_VECTOR_UNARY_OPS_TPP
#include <cml/vector/unary_ops.tpp>
#undef __CML_VECTOR_UNARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
