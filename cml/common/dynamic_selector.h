/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_dynamic_selector_h
#define	cml_common_dynamic_selector_h

#include <memory>
#include <cml/common/storage/traits.h>

namespace cml {

/* Forward declarations: */
template<class Element, class Alloc>
  struct dynamic_vector_storage;
template<class Element, class Layout, class Alloc>
  struct dynamic_matrix_storage;

/** Specializable type for selection of vector or matrix storage via a
 * dynamically-allocated, contiguous array of values.
 *
 * @tparam Allocator Optional allocator type that must be compatible with
 * std::allocator.  The default is std::allocator<void>.
 *
 * @warning Stateful allocators are not supported by CML built-in types.
 */
template<class Allocator = std::allocator<void>> struct dynamic {
  template<class Element> struct rebind_vector {
    typedef dynamic_vector_storage<Element, Allocator>		type;
  };
  template<class Element, class Layout> struct rebind_matrix {
    typedef dynamic_matrix_storage<Element, Layout, Allocator> type;
  };
};
#if 0
template<int Size1 = -1, int Size2 = -1, class Kind = void,
  class Allocator = std::allocator<void>>
struct allocated
{
  template<class Rebind> struct rebind {
    typedef allocated<Size1, Size2, Rebind, Allocator> type;
  };
};

template<class Allocator>
struct allocated<-1, -1, vector_storage_tag, Allocator>
{
  typedef allocated<>					selector_type;
  typedef vector_storage_tag				storage_tag;
  typedef dynamic_size_tag				size_tag;
  typedef allocated_memory_tag				memory_tag;
  typedef allocated					proxy_type;

  static const int array_size = -1;

  template<int N> struct resize {
    typedef allocated<N, -1, Allocator, vector_storage_tag> type;
  };
};

template<int Size, class Allocator>
struct allocated<Size, -1, Allocator, vector_storage_tag>
{
  typedef allocated<>					selector_type;
  typedef vector_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef allocated_memory_tag				memory_tag;
  typedef allocated					proxy_type;

  static const int array_size = Size;

  template<int N> struct resize {
    typedef allocated<N, -1, vector_storage_tag, Allocator> type;
  };
};

template<class Allocator>
struct allocated<-1, -1, matrix_storage_tag, Allocator>
{
  typedef allocated<>					selector_type;
  typedef matrix_storage_tag				storage_tag;
  typedef dynamic_size_tag				size_tag;
  typedef allocated_memory_tag				memory_tag;
  typedef allocated					proxy_type;

  static const int array_rows = -1;
  static const int array_cols = -1;

  template<int R, int C> struct resize {
    typedef allocated<R, C, matrix_storage_tag, Allocator> type;
  };
};

template<int Size1, int Size2, class Allocator>
struct allocated<Size1, Size2, Allocator, matrix_storage_tag>
{
  typedef allocated<>					selector_type;
  typedef matrix_storage_tag				storage_tag;
  typedef fixed_size_tag				size_tag;
  typedef allocated_memory_tag				memory_tag;
  typedef allocated					proxy_type;

  static const int array_rows = Size1;
  static const int array_cols = Size2;

  template<int R, int C> struct resize {
    typedef allocated<R, C, Allocator, matrix_storage_tag> type;
  };
};

template<class Allocator> using dynamic = allocated<-1, -1, Allocator>;
#endif

/** is_storage_tag for dynamic<>. */
template<class Allocator>
struct is_storage_tag<dynamic<Allocator>> {
  static const bool value = true;
};

} // namespace cml

/* Include here so dynamic<> is forward declared above first: */
#include <cml/common/storage/dynamic_vector.h>
#include <cml/common/storage/dynamic_matrix.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
