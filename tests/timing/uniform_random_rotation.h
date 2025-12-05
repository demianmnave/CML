/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <random>
#include <cml/matrix.h>

namespace cml::testing {

template<class Gen, class Matrix44dT>
void uniform_random_rotation_4(Gen& g, std::uniform_real_distribution<>& d,
  Matrix44dT& M);

}  // namespace cml::testing

#define _CML_TESTING_UNIFORM_RANDOM_ROTATION_TPP
#include "uniform_random_rotation.tpp"
#undef _CML_TESTING_UNIFORM_RANDOM_ROTATION_TPP
