/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_scalar_ops_h
#define	cml_matrix_scalar_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/matrix/scalar_node.h>
#include <cml/matrix/type_util.h>

namespace cml {

/** Template helper for scalar multiplication. */
template<class Sub, class Scalar>
  using matrix_scalar_multiply = op::binary_multiply<
    matrix_element_type_of_t<Sub>, cml::unqualified_type_t<Scalar>>;

/** Template helper for scalar division. */
template<class Sub, class Scalar>
  using matrix_scalar_divide = op::binary_divide<
    matrix_element_type_of_t<Sub>, cml::unqualified_type_t<Scalar>>;

} // namespace cml

#define __CML_MATRIX_SCALAR_OPS_TPP
#include <cml/matrix/scalar_ops.tpp>
#undef __CML_MATRIX_SCALAR_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
