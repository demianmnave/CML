/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_dot_h
#define	cml_vector_dot_h

#include <cml/vector/readable_vector.h>
#include <cml/vector/promotion.h>

namespace cml {

/** Compute the dot-product of two vectors.
 *
 * @note Currently, the result is computed immediately, even if it appears
 * in an expression.
 *
 * @throws incompatible_vector_size_error at run-time if either left or
 * right is a dynamically-sized vector, and left.size() != right.size(). If
 * both are fixed-size expressions, then the sizes are checked at compile
 * time.
 *
 * @throws minimum_vector_size_error at run-time if either left or right is
 * a dynamically-sized vector, and left or right is empty. If both are
 * fixed-size expressions, then the sizes are checked at compile time.
 */
template<class Sub1, class Sub2> auto dot(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right)
  -> typename value_type_promote<Sub1, Sub2>::scalar_type;

} // namespace cml

#define __CML_VECTOR_DOT_TPP
#include <cml/vector/dot.tpp>
#undef __CML_VECTOR_DOT_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
