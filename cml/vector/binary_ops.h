/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_binary_ops_h
#define	cml_vector_binary_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/vector/binary_node.h>
#include <cml/vector/type_util.h>

namespace cml {

/** Template helper for vector binary minus. */
template<class Sub1, class Sub2>
  using vector_binary_minus = op::binary_minus<
    vector_element_type_of_t<Sub1>, vector_element_type_of_t<Sub2>>;

/** Template helper for vector binary plus. */
template<class Sub1, class Sub2>
  using vector_binary_plus = op::binary_plus<
    vector_element_type_of_t<Sub1>, vector_element_type_of_t<Sub2>>;

} // namespace cml

#define __CML_VECTOR_BINARY_OPS_TPP
#include <cml/vector/binary_ops.tpp>
#undef __CML_VECTOR_BINARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
