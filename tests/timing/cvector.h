/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <ostream>

using vector4d = double[4];

/* Need some specializations for CML: */
namespace cml {

struct vector4d_traits
{
  using value_type = double;
};

template<> struct traits_of<vector4d>
{
  using type = vector4d_traits;
};

}  // namespace cml

inline std::ostream&
operator<<(std::ostream& os, const vector4d& v)
{
  os << "[";
  for(int i = 0; i < 4; ++i) os << " " << v[i];
  os << " ]";
  return os;
}
