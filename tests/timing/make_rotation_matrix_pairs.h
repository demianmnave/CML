/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#pragma once

#include <vector>
#include <utility>

namespace cml {
namespace testing {

template<class Matrix44T>
std::vector<std::pair<Matrix44T, Matrix44T>>
make_rotation_matrix_pairs(int N);

}} // cml::testing

#define _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
#include "make_rotation_matrix_pairs.tpp"
#undef _CML_TESTING_MAKE_ROTATION_MATRIX_PAIRS_TPP
