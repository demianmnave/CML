/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_traits_h
#define	cml_vector_traits_h

namespace cml {

/** Specializable class wrapping traits for cml::vector<> types. This class
 * is used to simplify static polymorphism by providing a polymorphic base
 * class the types used by a particular derived class.
 *
 * @tparam Vector The vector<> type the traits correspond to.
 */
template<class Vector> struct vector_traits;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
