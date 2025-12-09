/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/size_tags.h>
#include <cml/common/storage_tags.h>
#include <cml/common/memory_tags.h>
#include <cml/storage/type_util.h>

namespace cml {
/** Base selector to specify an arbitrary or unknown storage type.
 *
 * @tparam Tag Tag specifying the type of storage (e.g.
 * vector_storage_tag).  This is set by instantiating @c rebind with the
 * required tag.
 */
template<class Tag = void> struct any_storage
{
  /** Rebind the base selector to the required type. */
  template<class Rebind> struct rebind
  {
    using other = any_storage<Rebind>;
  };

  /** Make a partially bound selector by resizing. The new size is ignored
   * for any_storage<>.
   */
  template<int> struct resize
  {
    using type = any_storage<>;
  };

  /** Make a partially bound selector by reshaping.  The new shape is ignored
   * for any_storage<>.
   */
  template<int, int> struct reshape
  {
    using type = any_storage<>;
  };
};

/** Specialized selector for any vector storage. */
template<> struct any_storage<vector_storage_tag>
{
  using selector_type = any_storage<>;
  using unbound_type = any_storage<>;
  using proxy_type = any_storage<>;
  using storage_tag = vector_storage_tag;
  using size_tag = any_size_tag;
  using memory_tag = any_memory_tag;

  /** Unspecified array size. */
  static constexpr int array_size = -1;

  /** Rebind to a new vector any_storage<> selector (the template parameter
   * is ignored).
   */
  template<int> struct resize
  {
    using type = any_storage<>;
  };
};

/** Specialized selector for any matrix storage. */
template<> struct any_storage<matrix_storage_tag>
{
  using selector_type = any_storage<>;
  using unbound_type = any_storage<>;
  using proxy_type = any_storage<>;
  using storage_tag = matrix_storage_tag;
  using size_tag = any_size_tag;
  using memory_tag = any_memory_tag;

  /** Unspecified number of array rows. */
  static constexpr int array_rows = -1;

  /** Unspecified number of array columns. */
  static constexpr int array_cols = -1;

  /** Rebind to a new matrix any_storage<> selector (the template
   * parameters are ignored).
   */
  template<int, int> struct reshape
  {
    using type = any_storage<>;
  };
};

/** Specialized selector for any quaternion storage. */
template<> struct any_storage<quaternion_storage_tag>
{
  using selector_type = any_storage<>;
  using unbound_type = any_storage<>;
  using proxy_type = any_storage<>;
  using storage_tag = quaternion_storage_tag;
  using size_tag = any_size_tag;
  using memory_tag = any_memory_tag;

  /** Unspecified array size. */
  static constexpr int array_size = -1;

  /** Rebind to a new vector any_storage<> selector (the template parameter
   * is ignored).
   */
  template<int> struct resize
  {
    using type = any_storage<>;
  };
};

/** is_storage_selector for any_storage<>. */
template<class Tag> struct is_storage_selector<any_storage<Tag>>
{
  static constexpr bool value = true;
};

/** Helper to detect any_storage<> types. */
template<class Storage> struct is_any_storage
{
  static constexpr bool value =
    std::is_same_v<typename Storage::selector_type, any_storage<>>;
};

/** Helper to disambiguate any_storage<> types. */
template<class Tag1, class Tag2>
struct storage_disambiguate<any_storage<Tag1>, any_storage<Tag2>>
{
  using type = any_storage<>;
};
} // namespace cml
