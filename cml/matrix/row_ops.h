/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/type_util.h>
#include <cml/matrix/row_node.h>

namespace cml {
template<class Sub, enable_if_matrix_t<Sub>* = nullptr>
auto
row(Sub&& sub, int row)
  -> matrix_row_node<actual_operand_type_of_t<decltype(sub)>, -1>
{
  static_assert(
    std::is_same<decltype(sub), decltype(std::forward<Sub>(sub))>::value,
    "internal error: unexpected expression type");

  /* Deduce the operand type of the subexpression (&, const&, &&): */
  using sub_type = actual_operand_type_of_t<decltype(sub)>;
  return matrix_row_node<sub_type, -1>((sub_type) sub, row);
}
} // namespace cml
