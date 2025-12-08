/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <ostream>
#include <cml/common/traits.h>

using matrix44d = double[4][4];

/* Need some specializations for CML: */
namespace cml {

struct matrix44d_traits
{
  using value_type = double;
};

template<> struct traits_of<matrix44d>
{
  using type = matrix44d_traits;
};

}  // namespace cml

inline std::ostream&
operator<<(std::ostream& os, const matrix44d& M)
{
  for(int i = 0; i < 4; ++i) {
    os << "[";
    for(int j = 0; j < 4; ++j) os << " " << M[i][j];
    os << " ]";
    if(i != 4 - 1) os << std::endl;
  }
  return os;
}
