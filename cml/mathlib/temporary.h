/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_temporary_h
#define	cml_mathlib_temporary_h

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
  typedef matrix_traits<Matrix>				traits;
  typedef typename traits::value_type			value_type;
  typedef typename traits::storage_type			matrix_storage_type;
  typedef typename matrix_storage_type::unbound_type	unbound_storage_type;

  /* Rebind to a proxy vector storage type with the requested size: */
  typedef resize_storage_t<unbound_storage_type, N>	resized_type;
  typedef rebind_vector_storage_t<resized_type>		rebound_type;
  typedef proxy_type_of_t<rebound_type>			storage_type;
  typedef vector<value_type, storage_type>		type;
};

/** Convenience alias for n_basis_vector_of. */
template<class Matrix, int N>
  using n_basis_vector_of_t = typename n_basis_vector_of<Matrix,N>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
