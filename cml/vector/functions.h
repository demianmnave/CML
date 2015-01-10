/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_functions_h
#define	cml_vector_functions_h

#include <cml/scalar/promotion.h>
#include <cml/vector/temporary.h>

namespace cml {

/** Return the squared length of a vector. */
template<class DerivedT> inline auto
length_squared(const readable_vector<DerivedT>& v)
-> value_type_trait_of_t<DerivedT>;

/** Return the length of a vector. */
template<class DerivedT> inline auto
length(const readable_vector<DerivedT>& v)
-> value_type_trait_of_t<DerivedT>;

/** Return a normalized copy of a vector. */
template<class DerivedT> inline auto
normalize(const readable_vector<DerivedT>& v)
-> typename temporary_of<DerivedT>::type;

} // namespace cml

#define __CML_VECTOR_FUNCTIONS_TPP
#include <cml/vector/functions.tpp>
#undef __CML_VECTOR_FUNCTIONS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
