/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_traits_h
#define	cml_matrix_traits_h

namespace cml {

/** Specializable class wrapping traits for cml::matrix<> types. This class
 * is used to simplify static polymorphism by providing a polymorphic base
 * class the types used by a particular derived class.
 *
 * @tparam Matrix The matrix<> type the traits correspond to.
 */
template<class Matrix> struct matrix_traits;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
