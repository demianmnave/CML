/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_dot_h
#define	cml_vector_dot_h

#include <cml/scalar/promotion.h>
#include <cml/vector/traits.h>

namespace cml {

/** Convenience alias to determine the scalar type to return from cml::dot. */
template<class Sub1, class Sub2>
  using dot_promote_t = value_type_trait_promote_t<Sub1, Sub2>;

/** Compute the dot-product of two vectors.
 *
 * @note Currently, the result is computed immediately, even if it appears
 * as a term in an expression.
 *
 * @throws incompatible_vector_size_error at run-time if either left or
 * right is a dynamically-sized vector, and left.size() != right.size(). If
 * both are fixed-size expressions, then the sizes are checked at compile
 * time.
 */
template<class Sub1, class Sub2> auto
dot(const readable_vector<Sub1>& left, const readable_vector<Sub2>& right)
-> dot_promote_t<Sub1,Sub2>;

} // namespace cml

#define __CML_VECTOR_DOT_TPP
#include <cml/vector/dot.tpp>
#undef __CML_VECTOR_DOT_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
