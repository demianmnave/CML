/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_fixed_selector_h
#define	cml_common_fixed_selector_h

#include <cml/common/storage/traits.h>

namespace cml {

/* Forward declarations: */
template<class Element, int Size>
  struct fixed_vector_storage;
template<class Element, int Size1, int Size2, class Layout>
  struct fixed_matrix_storage;

/** Specializable type for selection of vector or matrix storage via a
 * contiugous, fixed-size array of values.
 *
 * @tparam Size1 Fixed first dimension size.
 * @tparam Size2 Optional fixed second dimension size.
 */
template<int Size1, int Size2 = -1> struct fixed;
#if 0
template<int Size1 = -1, int Size2 = -1, class Kind = void>
struct fixed
{
  template<class Rebind> struct rebind {
    typedef fixed<Size1, Size2, Rebind>			type;
  };
};
#endif

/** Selector for fixed-size vectors. */
template<int Size1> struct fixed<Size1, -1> {
  template<class Element> struct rebind_vector {
    typedef fixed_vector_storage<Element, Size1>	type;
  };
};
#if 0
template<int Size>
struct fixed<Size, -1, vector_size_tag>
{
  typedef fixed<>					selector_type;
  typedef vector_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef compiled_memory_tag				memory_tag;
  typedef fixed<Size>					proxy_type;

  static const int array_size = Size;

  template<int N> struct resize {
    typedef fixed<N, -1, vector_storage_tag>		type;
  };
};
#endif

/** Selector for fixed-size matrices. */
template<int Size1, int Size2> struct fixed {
  template<class Element, class Layout> struct rebind_matrix {
    typedef fixed_matrix_storage<Element, Size1, Size2, Layout> type;
  };
};
#if 0
template<int Size1, int Size2>
struct fixed<Size1, Size2, vector_size_tag>
{
  typedef fixed<>					selector_type;
  typedef matrix_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef compiled_memory_tag				memory_tag;
  typedef fixed<Size1,Size2>				proxy_type;

  static const int array_rows = Size1;
  static const int array_cols = Size2;

  template<int R, int C> struct resize {
    typedef fixed<R, C, matrix_storage_tag>		type;
  };
};
#endif

/** is_storage_tag for fixed<>. */
template<int Size1, int Size2>
struct is_storage_tag<fixed<Size1,Size2>> {
  static const bool value = true;
};

} // namespace cml

/* Include here so fixed<> is forward declared above first: */
#include <cml/common/storage/fixed_vector.h>
#include <cml/common/storage/fixed_matrix.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
