/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_SCALAR_OPS_TPP
#error "matrix/scalar_ops.tpp not included correctly"
#endif

namespace cml {

/* Boilerplate for scalar-matrix multiply: */
__CML_MAKE_RIGHT_MATRIX_SCALAR_OPERATORS( * , matrix_scalar_multiply)

/* Boilerplate for matrix-scalar multiply: */
__CML_MAKE_LEFT_MATRIX_SCALAR_OPERATORS( * , matrix_scalar_multiply)

/* Boilerplate for matrix-scalar divide: */
__CML_MAKE_LEFT_MATRIX_SCALAR_OPERATORS( / , matrix_scalar_divide)

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
