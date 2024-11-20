/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/traits.h>
#include <cml/vector/type_util.h>

namespace cml {

/** Specializable class wrapping traits for vector<> types. This class is
 * used to simplify static polymorphism by providing a base class the types
 * used by a particular derived class.
 *
 * @tparam Vector The vector<> type the traits correspond to.
 */
template<class Vector> struct vector_traits;

/** traits_of for vector types. */
template<class Vector> struct traits_of<Vector, enable_if_vector_t<Vector>>
{
  using type = vector_traits<Vector>;
};

}  // namespace cml
