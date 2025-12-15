/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <ostream>
#include <cml/common/traits.h>
#include <cml/common/memory_tags.h>
#include <cml/common/layout_tags.h>

using matrix44d = double[4][4];

/* Need some specializations for CML: */
namespace cml {

struct matrix44d_traits
{
  using value_type = double;
  using memory_tag = compiled_memory_tag;
#ifdef CML_TIMING_ROW_MAJOR
  using layout_tag = row_major;
#endif
#ifdef CML_TIMING_COL_MAJOR
  using layout_tag = col_major;
#endif
};

template<> struct traits_of<matrix44d>
{
  using type = matrix44d_traits;
};

}  // namespace cml

inline std::ostream&
operator<<(std::ostream& os, const matrix44d& M)
{
  using layout = cml::layout_tag_trait_of_t<matrix44d>;

  if constexpr(std::is_same_v<layout, cml::row_major>) {
    for(int i = 0; i < 4; ++i) {
      os << "[";
      for(int j = 0; j < 4; ++j) os << " " << M[i][j];
      os << " ]";
      if(i != 4 - 1) os << std::endl;
    }
  }

 if constexpr(std::is_same_v<layout, cml::col_major>) {
    for(int i = 0; i < 4; ++i) {
      os << "[";
      for(int j = 0; j < 4; ++j) os << " " << M[j][i];
      os << " ]";
      if(i != 4 - 1) os << std::endl;
    }
  }

  return os;
}
