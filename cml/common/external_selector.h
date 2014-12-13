/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_external_selector_h
#define	cml_common_external_selector_h

#include <cml/common/storage_traits.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>

namespace cml {

/** Specializable type for 1D or 2D storage via an external (wrapped)
 * pointer.
 *
 * @tparam Size1 Fixed first dimension size, optional if Size2 is not needed.
 * @tparam Size2 Optional fixed second dimension size.
 *
 * @note If neither Size1 nor Size2 are set, then the size is determined at
 * run-time.
 *
 * @note Fixed-length 1D arrays must define a constant, array_size,
 * containing the array length.
 *
 * @note Fixed-length 2D arrays must define two constants, array_rows and
 * array_cols, containing the number of rows and columns.
 */
template<int Size1 = -1, int Size2 = -1> struct external;

/** storage_traits for dynamic-size external<> vector or matrix. */
template<> struct storage_traits<external<-1,-1>> {
  typedef external<-1,-1>				storage_type;
  typedef dynamic<>					solid_type;
  typedef dynamic_size_tag				size_tag;
};

/** storage_traits for dynamic-size external<> vector. */
template<int Size1> struct storage_traits<external<Size1,-1>> {
  typedef external<Size1>				storage_type;
  typedef fixed<Size1,-1>				solid_type;
  typedef fixed_size_tag				size_tag;
};

/** storage_traits for fixed-size external<> matrix. */
template<int Size1, int Size2> struct storage_traits<external<Size1,Size2>> {
  typedef external<Size1,Size2>				storage_type;
  typedef fixed<Size1,Size2>				solid_type;
  typedef fixed_size_tag				size_tag;
};

/** traits_of for external<>. */
template<int Size1, int Size2> struct traits_of<external<Size1,Size2>, void> {
  typedef storage_traits<external<Size1,Size2>>		type;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
