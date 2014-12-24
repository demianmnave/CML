/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_external_selector_h
#define	cml_common_external_selector_h

#include <cml/common/storage/traits.h>

namespace cml {

/* Forward declarations: */
template<class Element, int Size>
  struct external_vector_storage;
template<class Element, int Size1, int Size2, class Layout>
  struct external_matrix_storage;

/** Specializable type for selection of vector or matrix storage via an
 * external (wrapped) pointer.
 *
 * @tparam Size1 Fixed first dimension size, optional if Size2 is not needed.
 * @tparam Size2 Optional fixed second dimension size.
 *
 * @note If neither Size1 nor Size2 are set, then the size is determined at
 * run-time.
 */
template<int Size1 = -1, int Size2 = -1> struct external;
#if 0
template<int Size1 = -1, int Size2 = -1, class Kind = void>
struct external
{
  template<class Rebind> struct rebind {
    typedef external<Size1, Size2, Rebind>		type;
  };
};
#endif

/** Selector for dynamic-size external vectors and matrices. */
template<> struct external<-1, -1> {
  template<class Element> struct rebind_vector {
    typedef external_vector_storage<Element,-1>		type;
  };
  template<class Element, class Layout> struct rebind_matrix {
    typedef external_matrix_storage<Element, -1,-1, Layout> type;
  };
};
#if 0
template<>
struct external<-1, -1, vector_storage_tag>
{
  typedef external<>					selector_type;
  typedef vector_storage_tag				storage_tag;
  typedef dynamic_size_tag				size_tag;
  typedef external_memory_tag				memory_tag;
  typedef allocated<-1, -1, vector_storage_tag>		proxy_type;

  static const int array_size = -1;

  template<int N> struct resize {
    typedef external<N, -1, vector_storage_tag>		type;
  };
};

template<> struct external<-1, -1, matrix_storage_tag>
{
  typedef external<>					selector_type;
  typedef matrix_storage_tag				storage_tag;
  typedef dynamic_size_tag				size_tag;
  typedef external_memory_tag				memory_tag;
  typedef allocated<-1, -1, matrix_storage_tag>		proxy_type;

  static const int array_rows = -1;
  static const int array_cols = -1;

  template<int R, int C> struct resize {
    typedef external<R, C, matrix_storage_tag>		type;
  };
};
#endif

/** Selector for fixed-size external vectors. */
template<int Size> struct external<Size, -1> {
  template<class Element> struct rebind_vector {
    typedef external_vector_storage<Element, Size>	type;
  };
};
#if 0
template<int Size>
struct external<Size, -1, vector_storage_tag>
{
  typedef external<>					selector_type;
  typedef vector_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef external_memory_tag				memory_tag;
  typedef fixed<Size, -1, vector_storage_tag>		proxy_type;

  static const int array_size = Size;

  template<int N> struct resize {
    typedef external<N, -1, vector_storage_tag>		type;
  };
};
#endif

/** Selector for fixed-size external matrices. */
template<int Size1, int Size2> struct external {
  template<class Element, class Layout> struct rebind_matrix {
    typedef external_matrix_storage<Element, Size1,Size2, Layout> type;
  };
};
#if 0
template<int Size1, int Size2>
struct external<Size1, Size2, matrix_storage_tag>
{
  typedef external<>					selector_type;
  typedef matrix_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef external_memory_tag				memory_tag;
  typedef fixed<Size1, Size2, matrix_storage_tag>	proxy_type;

  static const int array_rows = Size1;
  static const int array_cols = Size2;

  template<int R, int C> struct resize {
    typedef external<R, C, matrix_storage_tag>		type;
  };
};
#endif

/** is_storage_tag for external<>. */
template<int Size1, int Size2>
struct is_storage_tag<external<Size1,Size2>> {
  static const bool value = true;
};

} // namespace cml

/* Include here so external<> is forward declared above first: */
#include <cml/common/storage/external_vector.h>
#include <cml/common/storage/external_matrix.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
