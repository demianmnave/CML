/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_BINARY_OPS_TPP
#error "vector/binary_ops.tpp not included correctly"
#endif

namespace cml {

/* Boilerplate for operator-: */
__CML_MAKE_VECTOR_BINARY_OPERATORS( - , vector_binary_minus )

/* Boilerplate for operator+: */
__CML_MAKE_VECTOR_BINARY_OPERATORS( + , vector_binary_plus )

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
