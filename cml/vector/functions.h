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
-> typename vector_traits<DerivedT>::value_type;

/** Return the length of a vector. */
template<class DerivedT> inline auto
length(const readable_vector<DerivedT>& v)
-> typename vector_traits<DerivedT>::value_type;

/** Return a normalized copy of a vector. */
template<class DerivedT> inline auto
normalize(const readable_vector<DerivedT>& v)
-> typename vector_traits<DerivedT>::temporary_type;

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
