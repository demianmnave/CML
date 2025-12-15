/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <utility>
#include <cml/vector/types.h>

namespace cml::testing {

// template<class Matrix33dT, class Vector3dT, int K>
// std::vector<std::tuple<Matrix33dT, Vector3dT, cml::vector3d>>
// make_matrix_vector_pairs(int N, cml::int_c<3>);

template<class Matrix44dT, class Vector4dT>
auto make_matrix_vector_pairs(int N, cml::int_c<4>)
  -> std::vector<std::tuple<Matrix44dT, Vector4dT, cml::vector4d>>;

template<class MatrixT, class VectorT, int K>
auto
make_matrix_vector_pairs(int N)
{
  static_assert(K == 3 || K == 4);
  return make_matrix_vector_pairs<MatrixT, VectorT>(N, cml::int_c<K>());
}

}  // namespace cml::testing

#include "make_matrix_vector_pairs.tpp"
