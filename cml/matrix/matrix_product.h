/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {

/** Multiply two matrices and return the result as a temporary. */
template<class Sub1, class Sub2, typename = enable_if_matrix_t<Sub1>,
  typename = enable_if_matrix_t<Sub2>>
auto operator*(Sub1&& sub1, Sub2&& sub2) -> matrix_inner_product_promote_t<
  actual_type_of_t<Sub1>, actual_type_of_t<Sub2>>;

}  // namespace cml

#include <cml/matrix/matrix_product.tpp>
