/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_unary_ops_h
#define	cml_matrix_unary_ops_h

#include <cml/common/scalar_unary_ops.h>
#include <cml/matrix/unary_node.h>

namespace cml {

/** Template helper for unary minus. */
template<class Sub> using matrix_unary_minus
= op::unary_minus<typename matrix_traits<Sub>::value_type>;

/** Template helper for unary plus. */
template<class Sub> using matrix_unary_plus
= op::unary_plus<typename matrix_traits<Sub>::value_type>;

/** Return an expression node for unary minus over the elements of the
 * sub-expression @c sub, stored as a const reference in the node.
 */
template<class Sub> auto operator-(const readable_matrix<Sub>& sub)
-> matrix_unary_node<const Sub&, matrix_unary_minus<Sub>>;

/** Return an expression node for unary minus over the elements of the
 * temporary sub-expression @c sub.  @c sub is stored by value in the node
 * (via std::move).
 */
template<class Sub> auto operator-(readable_matrix<Sub>&& sub)
-> matrix_unary_node<Sub&&, matrix_unary_minus<Sub>>;

/** Return an expression node for unary plus over the elements of the
 * sub-expression @c sub, stored as a const reference in the node.
 */
template<class Sub> auto operator+(const readable_matrix<Sub>& sub)
-> matrix_unary_node<const Sub&, matrix_unary_plus<Sub>>;

/** Return an expression node for unary plus over the elements of the
 * temporary sub-expression @c sub.  @c sub is stored by value in the node
 * (via std::move).
 */
template<class Sub> auto operator+(readable_matrix<Sub>&& sub)
-> matrix_unary_node<Sub&&, matrix_unary_plus<Sub>>;

} // namespace cml

#define __CML_MATRIX_UNARY_OPS_TPP
#include <cml/matrix/unary_ops.tpp>
#undef __CML_MATRIX_UNARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
