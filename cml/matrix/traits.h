/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/traits.h>
#include <cml/matrix/type_util.h>

namespace cml {

/** Specializable class wrapping traits for matrix<> types. This class
 * is used to simplify static polymorphism by providing a polymorphic base
 * class the types used by a particular derived class.
 *
 * @tparam Matrix The matrix<> type the traits correspond to.
 */
template<class Matrix> struct matrix_traits;

/** traits_of for matrix types. */
template<class Matrix> struct traits_of<Matrix, enable_if_matrix_t<Matrix>>
{
  using type = matrix_traits<Matrix>;
};

}  // namespace cml
