/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/temporary.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/matrix/traits.h>
#include <cml/matrix/matrix.h>

namespace cml {
/** Deduce a temporary for a matrix expression. */
template<class Matrix>
struct temporary_of<Matrix, cml::enable_if_matrix_t<Matrix>>
{
  using matrix_type = cml::unqualified_type_t<Matrix>;

  /* Propagate the element type of the original matrix: */
  using traits_type = matrix_traits<matrix_type>;
  using value_type = typename traits_type::value_type;
  using storage_type = typename traits_type::storage_type;
  using basis_tag = typename traits_type::basis_tag;
  using layout_tag = typename traits_type::layout_tag;

  /* Need the proxy for the storage type: */
  using proxy_type = typename storage_type::proxy_type;

  /* Build the temporary: */
  using type = matrix<value_type, proxy_type, basis_tag, layout_tag>;
};
} // namespace cml
