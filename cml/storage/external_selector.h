/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/compiled_selector.h>
#include <cml/storage/allocated_selector.h>

namespace cml {

/* Forward declarations: */
template<int Size1 = -1, int Size2 = -1, class Tag = void> struct external;

/** Base selector to choose storage types that wrap a pointer or reference
 * to array data.
 *
 * @tparam Size1 First dimension size.
 *
 * @tparam Size2 Second dimension size.
 *
 * @tparam Tag Tag specifying the type of storage (e.g.
 * vector_storage_tag).  This is set by instantiating @c rebind with the
 * required tag.
 */
template<int Size1, int Size2> struct external<Size1, Size2, void>
{
  /** Rebind the base selector to the required type. */
  template<class Rebind> struct rebind
  {
    using other = external<Size1, Size2, Rebind>;
  };

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = external<N>;
  };

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = external<R, C>;
  };
};

/** Specialized selector for dynamic-size external vectors. */
template<> struct external<-1, -1, vector_storage_tag>
{
  using selector_type = external<>;
  using unbound_type = external<>;
  using proxy_type = allocated<>;
  using storage_tag = vector_storage_tag;
  using size_tag = dynamic_size_tag;
  using memory_tag = external_memory_tag;

  /** Unspecified array size. */
  static const int array_size = -1;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = external<N>;
  };
};

/** Specialized selector for fixed-size external vectors. */
template<int Size> struct external<Size, -1, vector_storage_tag>
{
  using selector_type = external<>;
  using unbound_type = external<>;
  using proxy_type = compiled<Size>;
  using storage_tag = vector_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = external_memory_tag;

  /** Constant for the array size. */
  static const int array_size = Size;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = external<N>;
  };
};

/** Specialized selector for dynamic-size external matrices. */
template<> struct external<-1, -1, matrix_storage_tag>
{
  using selector_type = external<>;
  using unbound_type = external<>;
  using proxy_type = allocated<>;
  using storage_tag = matrix_storage_tag;
  using size_tag = dynamic_size_tag;
  using memory_tag = external_memory_tag;

  /** Unspecified array rows. */
  static const int array_rows = -1;

  /** Unspecified array columns. */
  static const int array_cols = -1;

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = external<R, C>;
  };
};

/** Specialized selector for fixed-size external matrices. */
template<int Size1, int Size2> struct external<Size1, Size2, matrix_storage_tag>
{
  using selector_type = external<>;
  using unbound_type = external<>;
  using proxy_type = compiled<Size1, Size2>;
  using storage_tag = matrix_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = external_memory_tag;

  /** Constant for the number of array rows. */
  static const int array_rows = Size1;

  /** Constant for the number of array columns. */
  static const int array_cols = Size2;

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = external<R, C>;
  };
};

/** Specialized selector for external quaternions. */
template<> struct external<4, -1, quaternion_storage_tag>
{
  using selector_type = external<>;
  using unbound_type = external<>;
  using proxy_type = compiled<4>;
  using storage_tag = quaternion_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = external_memory_tag;

  /** Constant for the array size. */
  static const int array_size = 4;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    static_assert(N == 4, "invalid quaternion storage size");
    using type = external<4>;
  };
};

/** is_storage_selector for external<>. */
template<int Size1, int Size2, class Tag>
struct is_storage_selector<external<Size1, Size2, Tag>>
{
  static const bool value = true;
};

/** Helper to disambiguate external<> types. */
template<int R1, int C1, class Tag1, int R2, int C2, class Tag2>
struct storage_disambiguate<external<R1, C1, Tag1>, external<R2, C2, Tag2>>
{
  using type = external<>;
};

}  // namespace cml
