/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_binary_ops_h
#define	cml_matrix_binary_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/matrix/binary_node.h>
#include <cml/matrix/type_util.h>

namespace cml {

/** Template helper for matrix binary minus. */
template<class Sub1, class Sub2>
  using matrix_binary_minus = op::binary_minus<
    matrix_element_type_of_t<Sub1>, matrix_element_type_of_t<Sub2>>;

/** Template helper for matrix binary plus. */
template<class Sub1, class Sub2>
  using matrix_binary_plus = op::binary_plus<
    matrix_element_type_of_t<Sub1>, matrix_element_type_of_t<Sub2>>;

} // namespace cml

#define __CML_MATRIX_BINARY_OPS_TPP
#include <cml/matrix/binary_ops.tpp>
#undef __CML_MATRIX_BINARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
