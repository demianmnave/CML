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

namespace cml {

/** Template helper for matrix binary minus. */
template<class Sub1, class Sub2> using matrix_binary_minus = op::binary_minus<
  typename matrix_traits<cml::unqualified_type_t<Sub1>>::value_type,
  typename matrix_traits<cml::unqualified_type_t<Sub2>>::value_type
  >;

/** Template helper for matrix binary plus. */
template<class Sub1, class Sub2> using matrix_binary_plus = op::binary_plus<
  typename matrix_traits<cml::unqualified_type_t<Sub1>>::value_type,
  typename matrix_traits<cml::unqualified_type_t<Sub2>>::value_type
  >;

} // namespace cml

#define __CML_MATRIX_BINARY_OPS_TPP
#include <cml/matrix/binary_ops.tpp>
#undef __CML_MATRIX_BINARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
