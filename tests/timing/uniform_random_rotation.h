/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#pragma once

#include <random>

namespace cml {
namespace testing {

template<class Gen, class Matrix44T>
void uniform_random_rotation_4(
  Gen& g, std::uniform_real_distribution<>& d, Matrix44T& M);

}} // cml::testing

#define _CML_TESTING_UNIFORM_RANDOM_ROTATION_TPP
#include "uniform_random_rotation.tpp"
#undef _CML_TESTING_UNIFORM_RANDOM_ROTATION_TPP
