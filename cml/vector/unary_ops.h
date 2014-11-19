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

/** Template helper for unary minus. */
template<class Sub> using vector_unary_minus
= op::unary_minus<typename vector_traits<Sub>::value_type>;

/** Template helper for unary plus. */
template<class Sub> using vector_unary_plus
= op::unary_plus<typename vector_traits<Sub>::value_type>;

/** Return an expression node for unary minus over the elements of the
 * sub-expression @c sub, stored as a const reference in the node.
 */
template<class Sub> auto operator-(const readable_vector<Sub>& sub)
-> vector_unary_node<const Sub&, vector_unary_minus<Sub>>;

/** Return an expression node for unary minus over the elements of the
 * temporary sub-expression @c sub.  @c sub is stored by value in the node
 * (via std::move).
 */
template<class Sub> auto operator-(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, vector_unary_minus<Sub>>;

/** Return an expression node for unary plus over the elements of the
 * sub-expression @c sub, stored as a const reference in the node.
 */
template<class Sub> auto operator+(const readable_vector<Sub>& sub)
-> vector_unary_node<const Sub&, vector_unary_plus<Sub>>;

/** Return an expression node for unary plus over the elements of the
 * temporary sub-expression @c sub.  @c sub is stored by value in the node
 * (via std::move).
 */
template<class Sub> auto operator+(readable_vector<Sub>&& sub)
-> vector_unary_node<Sub&&, vector_unary_plus<Sub>>;

} // namespace cml

#define __CML_VECTOR_UNARY_OPS_TPP
#include <cml/vector/unary_ops.tpp>
#undef __CML_VECTOR_UNARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
