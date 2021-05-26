/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#pragma once

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

} // namespace cml