/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/readable_matrix.h>
#include <cml/matrix/promotion.h>

namespace cml {

/** Multiply two matrices, and return the result as a temporary. */
template<class Sub1, class Sub2, enable_if_matrix_t<Sub1>* = nullptr,
  enable_if_matrix_t<Sub2>* = nullptr>
auto operator*(Sub1&& sub1, Sub2&& sub2)
  -> matrix_inner_product_promote_t<actual_operand_type_of_t<decltype(sub1)>,
    actual_operand_type_of_t<decltype(sub2)>>;

}  // namespace cml

#define __CML_MATRIX_MATRIX_PRODUCT_TPP
#include <cml/matrix/matrix_product.tpp>
#undef __CML_MATRIX_MATRIX_PRODUCT_TPP
