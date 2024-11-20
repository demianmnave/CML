/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/selectors.h>
#include <cml/vector/vector.h>

namespace cml {

/** @defgroup vector_types Predefined Vector Types */
/*@{*/

using vector2i = vector<int, fixed<2>>;
using vector3i = vector<int, fixed<3>>;
using vector4i = vector<int, fixed<4>>;
using vectori = vector<int, dynamic<>>;
using external2i = vector<int, external<2>>;
using external3i = vector<int, external<3>>;
using external4i = vector<int, external<4>>;
using externalni = vector<int, external<>>;
using external2ci = vector<const int, external<2>>;
using external3ci = vector<const int, external<3>>;
using external4ci = vector<const int, external<4>>;
using externalnci = vector<const int, external<>>;

using vector2f = vector<float, fixed<2>>;
using vector3f = vector<float, fixed<3>>;
using vector4f = vector<float, fixed<4>>;
using vectorf = vector<float, dynamic<>>;
using external2f = vector<float, external<2>>;
using external3f = vector<float, external<3>>;
using external4f = vector<float, external<4>>;
using externalnf = vector<float, external<>>;
using external2cf = vector<const float, external<2>>;
using external3cf = vector<const float, external<3>>;
using external4cf = vector<const float, external<4>>;
using externalncf = vector<const float, external<>>;

using vector2d = vector<double, fixed<2>>;
using vector3d = vector<double, fixed<3>>;
using vector4d = vector<double, fixed<4>>;
using vectord = vector<double, dynamic<>>;
using external2d = vector<double, external<2>>;
using external3d = vector<double, external<3>>;
using external4d = vector<double, external<4>>;
using externalnd = vector<double, external<>>;
using external2cd = vector<const double, external<2>>;
using external3cd = vector<const double, external<3>>;
using external4cd = vector<const double, external<4>>;
using externalncd = vector<const double, external<>>;

/*@}*/

}  // namespace cml
