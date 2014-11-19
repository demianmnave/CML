/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_BINARY_OPS_TPP
#error "matrix/binary_ops.tpp not included correctly"
#endif

namespace cml {

/* Boilerplate for operator-: */
__CML_MAKE_MATRIX_BINARY_OPERATORS( - , matrix_binary_minus )

/* Boilerplate for operator+: */
__CML_MAKE_MATRIX_BINARY_OPERATORS( + , matrix_binary_plus )

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
