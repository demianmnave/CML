/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/binary_ops.h>

namespace cml {
/** Elementwise (Hadamard) product of two matrixs. */
template<class Sub1, class Sub2, enable_if_matrix_t<Sub1>* = nullptr,
  enable_if_matrix_t<Sub2>* = nullptr>
auto
hadamard(Sub1&& sub1, Sub2&& sub2)
  -> decltype(make_matrix_binary_node<binary_multiply_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2)))
{
  return make_matrix_binary_node<binary_multiply_t<Sub1, Sub2>>(
    std::forward<Sub1>(sub1), std::forward<Sub2>(sub2));
}
} // namespace cml
