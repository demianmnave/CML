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

#include "uniform_random_rotation.tpp"