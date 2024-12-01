/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <utility>
#include <cml/matrix.h>

namespace cml::testing {

template<class Matrix44dT>
std::vector<std::tuple<Matrix44dT, Matrix44dT, cml::matrix44d>>
make_rotation_matrix_pairs(int N);

}  // namespace cml::testing

#define _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
#include "make_rotation_matrix_pairs.tpp"
#undef _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
