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
#include <cml/vector/type_util.h>

namespace cml {

/** Template helper for scalar multiplication. */
template<class Sub, class Scalar>
  using vector_scalar_multiply = op::binary_multiply<
    vector_element_type_of_t<Sub>, cml::unqualified_type_t<Scalar>>;

/** Template helper for scalar division. */
template<class Sub, class Scalar>
  using vector_scalar_divide = op::binary_divide<
    vector_element_type_of_t<Sub>, cml::unqualified_type_t<Scalar>>;

} // namespace cml

#define __CML_VECTOR_SCALAR_OPS_TPP
#include <cml/vector/scalar_ops.tpp>
#undef __CML_VECTOR_SCALAR_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
