/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_functions_h
#define	cml_vector_functions_h

#include <cml/vector/writable_vector.h>

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
-> cml::vector<value_type_trait_of_t<DerivedT>,
  typename vector_traits<DerivedT>::storage_traits::solid_type>;

/** Normalize a writable temporary and return it. */
template<class DerivedT> inline auto
normalize(writable_vector<DerivedT>&& v) -> DerivedT&&;

} // namespace cml

#define __CML_VECTOR_FUNCTIONS_TPP
#include <cml/vector/functions.tpp>
#undef __CML_VECTOR_FUNCTIONS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
