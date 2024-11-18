/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/array_size_of.h>
#include <cml/vector/type_util.h>

namespace cml {

/** Specialize array_rows_of_c for vectors to return 1. */
template<class Sub> struct array_rows_of_c<Sub, enable_if_vector_t<Sub>>
{
  static const int value = 1;
};

/** Specialize array_cols_of_c for vectors to return 1. */
template<class Sub> struct array_cols_of_c<Sub, enable_if_vector_t<Sub>>
{
  static const int value = 1;
};

}  // namespace cml
