/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <memory>
#include <cml/common/mpl/if_t.h>
#include <cml/common/size_tags.h>
#include <cml/common/storage_tags.h>
#include <cml/common/memory_tags.h>
#include <cml/storage/type_util.h>

// XXX Temporary, for fixed-size allocated proxies:
#include <cml/storage/compiled_selector.h>

namespace cml {
/* Forward declarations: */
template<class Allocator = std::allocator<void*>, int Size1 = -1,
  int Size2 = -1, class Tag = void>
struct allocated;

/** Base selector to choose dynamically-allocated types (types with runtime
 * storage and either fixed or dynamic size).
 *
 * @tparam Size1 First dimension size.
 *
 * @tparam Size2 Second dimension size.
 *
 * @tparam Allocator Optional allocator type that must be compatible with
 * std::allocator. The default is std::allocator<void>.
 *
 * @tparam Tag Tag specifying the type of storage (e.g.
 * vector_storage_tag).  This is set by instantiating @c rebind with the
 * required tag.
 */
template<class Allocator, int Size1, int Size2>
struct allocated<Allocator, Size1, Size2>
{
  /** Rebind the base selector to the required type. */
  template<class Rebind> struct rebind
  {
    using other = allocated<Allocator, Size1, Size2, Rebind>;
  };

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = allocated<Allocator, N>;
  };

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = allocated<Allocator, R, C>;
  };
};

/** Specialized selector for dynamically-allocated vectors. */
template<class Allocator>
struct allocated<Allocator, -1, -1, vector_storage_tag>
{
  using selector_type = allocated<>;
  using unbound_type = allocated<Allocator>;
  using proxy_type = allocated<Allocator>;
  using storage_tag = vector_storage_tag;
  using size_tag = dynamic_size_tag;
  using memory_tag = allocated_memory_tag;

  /** Unspecified array size. */
  static constexpr int array_size = -1;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = allocated<Allocator, N>;
  };
};

/** Specialized selector for dynamically-allocated, fixed-size vectors.
 *
 * @todo Fixed-size allocated types are not actually implemented by CML, so
 * the proxy_type is set to compiled<Size>.
 */
template<int Size, class Allocator>
struct allocated<Allocator, Size, -1, vector_storage_tag>
{
  using selector_type = allocated<>;
  using unbound_type = allocated<Allocator>;
  //XXX typedef allocated<Allocator, Size>		proxy_type;
  using proxy_type = compiled<Size>;
  using storage_tag = vector_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = allocated_memory_tag;

  /** Constant for the array size. */
  static constexpr int array_size = Size;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    using type = allocated<Allocator, N>;
  };
};

/** Specialized selector for dynamically-allocated matrices. */
template<class Allocator>
struct allocated<Allocator, -1, -1, matrix_storage_tag>
{
  using selector_type = allocated<>;
  using unbound_type = allocated<Allocator>;
  using proxy_type = allocated<Allocator>;
  using storage_tag = matrix_storage_tag;
  using size_tag = dynamic_size_tag;
  using memory_tag = allocated_memory_tag;

  /** Unspecified array rows. */
  static constexpr int array_rows = -1;

  /** Unspecified array columns. */
  static constexpr int array_cols = -1;

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct reshape
  {
    using type = allocated<Allocator, R, C>;
  };
};

/** Specialized selector for dynamically-allocated, fixed-size matrices.
 *
 * @todo Fixed-size allocated types are not actually implemented by CML, so
 * the proxy_type is set to compiled<Size1,Size2>.
 */
template<class Allocator, int Size1, int Size2>
struct allocated<Allocator, Size1, Size2, matrix_storage_tag>
{
  using selector_type = allocated<>;
  using unbound_type = allocated<Allocator>;
  //XXX typedef allocated<Allocator, Size1, Size2>	proxy_type;
  using proxy_type = compiled<Size1, Size2>;
  using storage_tag = matrix_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = allocated_memory_tag;

  /** Constant for the number of array rows. */
  static constexpr int array_rows = Size1;

  /** Constant for the number of array columns. */
  static constexpr int array_cols = Size2;

  /** Make a partially bound selector with size @c R x @c C. */
  template<int R, int C> struct resize
  {
    using type = allocated<Allocator, R, C>;
  };
};

/** Specialized selector for dynamically-allocated quaternions.
 *
 * @todo Fixed-size allocated types are not actually implemented by CML, so
 * the proxy_type is set to compiled<Size>.
 */
template<class Allocator>
struct allocated<Allocator, 4, -1, quaternion_storage_tag>
{
  using selector_type = allocated<>;
  using unbound_type = allocated<Allocator>;
  //XXX typedef allocated<Allocator,4>			proxy_type;
  using proxy_type = compiled<4>;
  using storage_tag = quaternion_storage_tag;
  using size_tag = fixed_size_tag;
  using memory_tag = allocated_memory_tag;

  /** Constant for the array size. */
  static constexpr int array_size = 4;

  /** Make a partially bound selector with size @c N. */
  template<int N> struct resize
  {
    static_assert(N == 4, "invalid quaternion storage size");
    using type = allocated<Allocator, 4>;
  };
};

/** is_storage_selector for allocated<>. */
template<class Allocator, int Size1, int Size2, class Tag>
struct is_storage_selector<allocated<Allocator, Size1, Size2, Tag>>
{
  static constexpr bool value = true;
};

/** Determine an unbound allocated<> storage type using an allocator that
 * best represents the combination of the passed-in allocators.  If the
 * best allocator cannot be determined, std::allocator<> is used.
 *
 * @note This can be specialized for user-defined allocators if the default
 * disambiguation strategy fails to yield the proper type.
 */
template<class Allocator1, int R1, int C1, class Tag1, class Allocator2, int R2,
  int C2, class Tag2>
struct storage_disambiguate<allocated<Allocator1, R1, C1, Tag1>,
    allocated<Allocator2, R2, C2, Tag2>>
{
  /* Rebind the allocators to void* to compare them: */
  using left_traits = std::allocator_traits<Allocator1>;
  using right_traits = std::allocator_traits<Allocator2>;
  using left_type = typename left_traits::template rebind_alloc<void*>;
  using right_type = typename right_traits::template rebind_alloc<void*>;

  /* True if the unbound allocators are the same: */
  static constexpr bool is_same = std::is_same_v<left_type, right_type>;

  /* True if the left and/or right allocators are the default: */
  static constexpr bool left_is_default =
    std::is_same_v<left_type, std::allocator<void*>>;
  static constexpr bool right_is_default =
    std::is_same_v<right_type, std::allocator<void*>>;

  /* Prefer the left allocator if it is not the default allocator: */
  static constexpr bool prefer_left = !left_is_default && right_is_default;

  /* Prefer the right allocator if it is not the default allocator: */
  static constexpr bool prefer_right = !right_is_default && left_is_default;

  /* Use std::allocator<> if the best cannot be determined: */
  static constexpr bool prefer_default = !(is_same || prefer_left || prefer_right);
  static_assert(is_same || prefer_left || prefer_right || prefer_default,
    "unexpected storage_disambiguate result");

  /* Determine the preferred allocator type: */
  using allocator_type = cml::if_t<is_same, left_type,
    cml::if_t<prefer_left, left_type,
      cml::if_t<prefer_right, right_type,
        /*else*/ std::allocator<void*>>>>;

  /* Build the disambiguated unbound storage type: */
  using type = allocated<allocator_type>;
};


/** For compatibility with CML1. */
template<class Allocator = std::allocator<void*>>
using dynamic = allocated<Allocator>;
} // namespace cml
