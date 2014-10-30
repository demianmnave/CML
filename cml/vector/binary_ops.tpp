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
__CML_MAKE_VECTOR_BINARY_OPERATORS( - , binary_minus_type )

/* Boilerplate for operator+: */
__CML_MAKE_VECTOR_BINARY_OPERATORS( + , binary_plus_type )

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
