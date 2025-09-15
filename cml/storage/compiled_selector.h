/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/size_tags.h>
#include <cml/common/storage_tags.h>
#include <cml/common/memory_tags.h>
#include <cml/storage/type_util.h>

namespace cml {
/* Forward declarations: */
template<int Size1 = -1, int Size2 = -1, class Tag = void> struct compiled;

/** Base selector to choose compiled storage types.
 *
 * @tparam Size1 First dimension size.
 *
 * @tparam Size2 Second dimension size.
 *
 * @tparam Tag Tag specifying the type of storage (e.g.
 * vector_storage_tag).  This is set by instantiating @c rebind with the
 * required tag.
 */
template<int Size1, int Size2> struct compiled<Size1, Size2, void>
{
  /** Rebind the base selector to the required type. */
  template<class Rebind> struct rebind
  {
    using other = compiled<Size1, Size2, Rebind>;
  };

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = compiled<N>;
  };

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = compiled<R, C>;
  };
};

/** Specialized selector for fixed-size compiled vectors. */
template<int Size> struct compiled<Size, -1, vector_storage_tag>
{
  using selector_type = compiled<>;
  using unbound_type = compiled<>;
  using proxy_type = compiled<Size>;
  using storage_tag = vector_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = compiled_memory_tag;

  /** Constant for the array size. */
  static const int array_size = Size;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = compiled<N>;
  };
};

/** Specialized selector for fixed-size compiled matrices. */
template<int Size1, int Size2> struct compiled<Size1, Size2, matrix_storage_tag>
{
  using selector_type = compiled<>;
  using unbound_type = compiled<>;
  using proxy_type = compiled<Size1, Size2>;
  using storage_tag = matrix_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = compiled_memory_tag;

  /** Constant for the number of array rows. */
  static const int array_rows = Size1;

  /** Constant for the number of array columns. */
  static const int array_cols = Size2;

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = compiled<R, C>;
  };
};

/** Specialized selector for quaternions. */
template<> struct compiled<4, -1, quaternion_storage_tag>
{
  using selector_type = compiled<>;
  using unbound_type = compiled<>;
  using proxy_type = compiled<>;
  using storage_tag = quaternion_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = compiled_memory_tag;

  /** Constant for the array size. */
  static const int array_size = 4;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    static_assert(N == 4, "invalid quaternion storage size");
    using type = compiled<4>;
  };
};

/** is_storage_selector for compiled<>. */
template<int Size1, int Size2, class Tag>
struct is_storage_selector<compiled<Size1, Size2, Tag>>
{
  static const bool value = true;
};

/** Helper to disambiguate compiled<> types. */
template<int R1, int C1, class Tag1, int R2, int C2, class Tag2>
struct storage_disambiguate<compiled<R1, C1, Tag1>, compiled<R2, C2, Tag2>>
{
  using type = compiled<>;
};

/** For compatibility with CML1. */
template<int Size1 = -1, int Size2 = -1> using fixed = compiled<Size1, Size2>;
} // namespace cml
