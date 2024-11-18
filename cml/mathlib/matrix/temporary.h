/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/basis_tags.h>
#include <cml/storage/resize.h>
#include <cml/storage/type_util.h>
#include <cml/vector/vector.h>
#include <cml/matrix/traits.h>

namespace cml {

/** Deduce a temporary for basis @c N-vectors of @c Matrix. */
template<class Matrix, int N, cml::enable_if_matrix_t<Matrix>* = nullptr>
struct n_basis_vector_of
{
  /* Query the unbound storage type: */
  using traits = matrix_traits<Matrix>;
  using value_type = typename traits::value_type;
  using matrix_storage_type = typename traits::storage_type;
  using unbound_storage_type = typename matrix_storage_type::unbound_type;

  /* Rebind to a proxy vector storage type with the requested size: */
  using resized_type = resize_storage_t<unbound_storage_type, N>;
  using rebound_type = rebind_vector_storage_t<resized_type>;
  using storage_type = proxy_type_of_t<rebound_type>;
  using type = vector<value_type, storage_type>;
};

/** Convenience alias for n_basis_vector_of. */
template<class Matrix, int N>
using n_basis_vector_of_t = typename n_basis_vector_of<Matrix, N>::type;

/** Deduce a temporary for basis vectors of @c Matrix. */
template<class Matrix, cml::enable_if_matrix_t<Matrix>* = nullptr>
struct basis_vector_of
{
  /* Query the unbound storage type: */
  using traits = matrix_traits<Matrix>;
  using value_type = typename traits::value_type;
  using matrix_storage_type = typename traits::storage_type;
  using basis_tag = typename traits::basis_tag;
  using unbound_storage_type = typename matrix_storage_type::unbound_type;

  /* any_basis is not allowed: */
  static_assert(!is_any_basis<traits>::value,
    "any_basis invalid for basis vector type deduction");

  /* Determine the vector size based on the basis: */
  static const int N =
    is_row_basis<traits>::value ? traits::array_cols : traits::array_rows;

  /* Rebind to a proxy vector storage type with the requested size: */
  using resized_type = resize_storage_t<unbound_storage_type, N>;
  using rebound_type = rebind_vector_storage_t<resized_type>;
  using storage_type = proxy_type_of_t<rebound_type>;
  using type = vector<value_type, storage_type>;
};

/** Convenience alias for basis_vector_of. */
template<class Matrix>
using basis_vector_of_t = typename basis_vector_of<Matrix>::type;

}  // namespace cml
