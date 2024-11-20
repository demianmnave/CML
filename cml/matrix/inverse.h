/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/temporary.h>
#include <cml/matrix/size_checking.h>

namespace cml {

/** Compute the inverse of @c M and return the result in a temporary. */
template<class Sub>
inline temporary_of_t<Sub>
inverse(const readable_matrix<Sub>& M)
{
  cml::check_square(M);
  return temporary_of_t<Sub>(M).inverse();
}

}  // namespace cml
