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
#include <cml/vector/type_util.h>

namespace cml {

/** Template helper for vector unary minus. */
template<class Sub> using vector_unary_minus
  = op::unary_minus<vector_element_type_of_t<Sub>>;

/** Template helper for vector unary plus. */
template<class Sub> using vector_unary_plus
  = op::unary_plus<vector_element_type_of_t<Sub>>;

} // namespace cml

#define __CML_VECTOR_UNARY_OPS_TPP
#include <cml/vector/unary_ops.tpp>
#undef __CML_VECTOR_UNARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
