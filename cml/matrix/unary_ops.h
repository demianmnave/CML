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
#include <cml/matrix/type_util.h>

namespace cml {

/** Template helper for matrix unary minus. */
template<class Sub> using matrix_unary_minus
  = op::unary_minus<matrix_element_type_of_t<Sub>>;

/** Template helper for matrix unary plus. */
template<class Sub> using matrix_unary_plus
  = op::unary_plus<matrix_element_type_of_t<Sub>>;

} // namespace cml

#define __CML_MATRIX_UNARY_OPS_TPP
#include <cml/matrix/unary_ops.tpp>
#undef __CML_MATRIX_UNARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
