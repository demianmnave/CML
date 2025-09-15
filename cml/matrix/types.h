/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/selectors.h>
#include <cml/matrix/matrix.h>

namespace cml {
/** @defgroup matrix_types Predefined Matrix Types */
/*@{*/

// Column-basis, row-major:
using matrix22i = matrix<int, fixed<2, 2>>;
using matrix33i = matrix<int, fixed<3, 3>>;
using matrix44i = matrix<int, fixed<4, 4>>;
using matrix23i = matrix<int, fixed<2, 3>>;
using matrix34i = matrix<int, fixed<3, 4>>;
using matrixi = matrix<int, dynamic<>>;
using external22i = matrix<int, external<2, 2>>;
using external33i = matrix<int, external<3, 3>>;
using external44i = matrix<int, external<4, 4>>;
using external23i = matrix<int, external<2, 3>>;
using external34i = matrix<int, external<3, 4>>;
using externalmni = matrix<int, external<>>;

using matrix22f = matrix<float, fixed<2, 2>>;
using matrix33f = matrix<float, fixed<3, 3>>;
using matrix44f = matrix<float, fixed<4, 4>>;
using matrix32f = matrix<float, fixed<2, 3>>;
using matrix34f = matrix<float, fixed<3, 4>>;
using matrixf = matrix<float, dynamic<>>;
using external22f = matrix<float, external<2, 2>>;
using external33f = matrix<float, external<3, 3>>;
using external44f = matrix<float, external<4, 4>>;
using external23f = matrix<float, external<2, 3>>;
using external34f = matrix<float, external<3, 4>>;
using externalmnf = matrix<float, external<>>;

using matrix22d = matrix<double, fixed<2, 2>>;
using matrix33d = matrix<double, fixed<3, 3>>;
using matrix44d = matrix<double, fixed<4, 4>>;
using matrix23d = matrix<double, fixed<2, 3>>;
using matrix34d = matrix<double, fixed<3, 4>>;
using matrixd = matrix<double, dynamic<>>;
using external22d = matrix<double, external<2, 2>>;
using external33d = matrix<double, external<3, 3>>;
using external44d = matrix<double, external<4, 4>>;
using external23d = matrix<double, external<2, 3>>;
using external34d = matrix<double, external<3, 4>>;
using externalmnd = matrix<double, external<>>;


// Row-basis, row-major:
using matrix22i_r = matrix<int, fixed<2, 2>, row_basis, row_major>;
using matrix33i_r = matrix<int, fixed<3, 3>, row_basis, row_major>;
using matrix44i_r = matrix<int, fixed<4, 4>, row_basis, row_major>;
using matrix32i_r = matrix<int, fixed<3, 2>, row_basis, row_major>;
using matrix43i_r = matrix<int, fixed<4, 3>, row_basis, row_major>;
using matrixi_r = matrix<int, dynamic<>, row_basis, row_major>;
using external22i_r = matrix<int, external<2, 2>, row_basis, row_major>;
using external33i_r = matrix<int, external<3, 3>, row_basis, row_major>;
using external44i_r = matrix<int, external<4, 4>, row_basis, row_major>;
using external32i_r = matrix<int, external<3, 2>, row_basis, row_major>;
using external43i_r = matrix<int, external<4, 3>, row_basis, row_major>;
using externalmni_r = matrix<int, external<>, row_basis, row_major>;


using matrix22f_r = matrix<float, fixed<2, 2>, row_basis, row_major>;
using matrix33f_r = matrix<float, fixed<3, 3>, row_basis, row_major>;
using matrix44f_r = matrix<float, fixed<4, 4>, row_basis, row_major>;
using matrix32f_r = matrix<float, fixed<3, 2>, row_basis, row_major>;
using matrix43f_r = matrix<float, fixed<4, 3>, row_basis, row_major>;
using matrixf_r = matrix<float, dynamic<>, row_basis, row_major>;
using external22f_r = matrix<float, external<2, 2>, row_basis, row_major>;
using external33f_r = matrix<float, external<3, 3>, row_basis, row_major>;
using external44f_r = matrix<float, external<4, 4>, row_basis, row_major>;
using external32f_r = matrix<float, external<3, 2>, row_basis, row_major>;
using external43f_r = matrix<float, external<4, 3>, row_basis, row_major>;
using externalmnf_r = matrix<float, external<>, row_basis, row_major>;

using matrix22d_r = matrix<double, fixed<2, 2>, row_basis, row_major>;
using matrix33d_r = matrix<double, fixed<3, 3>, row_basis, row_major>;
using matrix44d_r = matrix<double, fixed<4, 4>, row_basis, row_major>;
using matrix32d_r = matrix<double, fixed<3, 2>, row_basis, row_major>;
using matrix43d_r = matrix<double, fixed<4, 3>, row_basis, row_major>;
using matrixd_r = matrix<double, dynamic<>, row_basis, row_major>;
using external22d_r = matrix<double, external<2, 2>, row_basis, row_major>;
using external33d_r = matrix<double, external<3, 3>, row_basis, row_major>;
using external44d_r = matrix<double, external<4, 4>, row_basis, row_major>;
using external32d_r = matrix<double, external<3, 2>, row_basis, row_major>;
using external43d_r = matrix<double, external<4, 3>, row_basis, row_major>;
using externalmnd_r = matrix<double, external<>, row_basis, row_major>;


// Column-basis, column-major:
using matrix22i_c = matrix<int, fixed<2, 2>, col_basis, col_major>;
using matrix33i_c = matrix<int, fixed<3, 3>, col_basis, col_major>;
using matrix44i_c = matrix<int, fixed<4, 4>, col_basis, col_major>;
using matrix23i_c = matrix<int, fixed<2, 3>, col_basis, col_major>;
using matrix34i_c = matrix<int, fixed<3, 4>, col_basis, col_major>;
using matrixi_c = matrix<int, dynamic<>, col_basis, col_major>;
using external22i_c = matrix<int, external<2, 2>, col_basis, col_major>;
using external33i_c = matrix<int, external<3, 3>, col_basis, col_major>;
using external44i_c = matrix<int, external<4, 4>, col_basis, col_major>;
using external23i_c = matrix<int, external<2, 3>, col_basis, col_major>;
using external34i_c = matrix<int, external<3, 4>, col_basis, col_major>;
using externalmni_c = matrix<int, external<>, col_basis, col_major>;

using matrix22f_c = matrix<float, fixed<2, 2>, col_basis, col_major>;
using matrix33f_c = matrix<float, fixed<3, 3>, col_basis, col_major>;
using matrix44f_c = matrix<float, fixed<4, 4>, col_basis, col_major>;
using matrix23f_c = matrix<float, fixed<2, 3>, col_basis, col_major>;
using matrix34f_c = matrix<float, fixed<3, 4>, col_basis, col_major>;
using matrixf_c = matrix<float, dynamic<>, col_basis, col_major>;
using external22f_c = matrix<float, external<2, 2>, col_basis, col_major>;
using external33f_c = matrix<float, external<3, 3>, col_basis, col_major>;
using external44f_c = matrix<float, external<4, 4>, col_basis, col_major>;
using external23f_c = matrix<float, external<2, 3>, col_basis, col_major>;
using external34f_c = matrix<float, external<3, 4>, col_basis, col_major>;
using externalmnf_c = matrix<float, external<>, col_basis, col_major>;

using matrix22d_c = matrix<double, fixed<2, 2>, col_basis, col_major>;
using matrix33d_c = matrix<double, fixed<3, 3>, col_basis, col_major>;
using matrix44d_c = matrix<double, fixed<4, 4>, col_basis, col_major>;
using matrix23d_c = matrix<double, fixed<2, 3>, col_basis, col_major>;
using matrix34d_c = matrix<double, fixed<3, 4>, col_basis, col_major>;
using matrixd_c = matrix<double, dynamic<>, col_basis, col_major>;
using external22d_c = matrix<double, external<2, 2>, col_basis, col_major>;
using external33d_c = matrix<double, external<3, 3>, col_basis, col_major>;
using external44d_c = matrix<double, external<4, 4>, col_basis, col_major>;
using external23d_c = matrix<double, external<2, 3>, col_basis, col_major>;
using external34d_c = matrix<double, external<3, 4>, col_basis, col_major>;
using externalmnd_c = matrix<double, external<>, col_basis, col_major>;

/*@}*/
} // namespace cml
