/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/temporary.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/vector/traits.h>
#include <cml/vector/vector.h>

namespace cml {
/** Deduce a temporary for a vector expression. */
template<class Vector>
struct temporary_of<Vector, cml::enable_if_vector_t<Vector>>
{
  using vector_type = cml::unqualified_type_t<Vector>;

  /* Propagate the element type of the original vector: */
  using traits_type = vector_traits<vector_type>;
  using value_type = typename traits_type::value_type;
  using storage_type = typename traits_type::storage_type;

  /* Need the proxy for the storage type: */
  using proxy_type = proxy_type_of_t<storage_type>;

  /* Build the temporary: */
  using type = vector<value_type, proxy_type>;
};

/** Deduce a subvector temporary type for a vector expression. */
template<class Vector,
  typename std::enable_if<vector_traits<Vector>::array_size
    == vector_traits<Vector>::array_size>::type* = nullptr>
struct subvector_of
{
  using vector_type = cml::unqualified_type_t<Vector>;

  /* Propagate the element type of the original vector: */
  using traits_type = vector_traits<vector_type>;
  using storage_type = typename traits_type::storage_type;
  using value_type = typename traits_type::value_type;
  using size_tag = typename traits_type::size_tag;

  /* Compute the new storage size: */

  private:
  static const int old_array_size = traits_type::array_size;
  static const int new_array_size = old_array_size - 1;
  static const int N = new_array_size > 0 ? new_array_size : -1;

  public:
  /* Determine the new storage type: */
  using resized_type = resize_storage_t<storage_type, N>;
  using rebound_type = rebind_t<resized_type, vector_storage_tag>;
  using proxy_type = proxy_type_of_t<rebound_type>;

  /* Build the subvector from the new storage type: */
  using type = vector<value_type, proxy_type>;
};

/** Convenience alias for subvector_of. */
template<class T> using subvector_of_t = typename subvector_of<T>::type;

/** Deduce a supervector temporary type for a vector expression. */
template<class Vector,
  typename std::enable_if<vector_traits<Vector>::array_size
    == vector_traits<Vector>::array_size>::type* = nullptr>
struct supervector_of
{
  using vector_type = cml::unqualified_type_t<Vector>;

  /* Propagate the element type of the original vector: */
  using traits_type = vector_traits<vector_type>;
  using storage_type = typename traits_type::storage_type;
  using value_type = typename traits_type::value_type;
  using size_tag = typename traits_type::size_tag;

  /* Compute the new storage size: */

  private:
  static const int old_array_size = traits_type::array_size;
  static const int new_array_size = old_array_size + 1;
  static const int N = new_array_size > 0 ? new_array_size : -1;

  public:
  /* Determine the new storage type: */
  using resized_type = resize_storage_t<storage_type, N>;
  using rebound_type = rebind_t<resized_type, vector_storage_tag>;
  using proxy_type = proxy_type_of_t<rebound_type>;

  /* Build the supervector from the new storage type: */
  using type = vector<value_type, proxy_type>;
};

/** Convenience alias for supervector_of. */
template<class T> using supervector_of_t = typename supervector_of<T>::type;
} // namespace cml
