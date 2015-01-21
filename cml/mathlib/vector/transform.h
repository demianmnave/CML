/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_vector_transform_h
#define	cml_mathlib_vector_transform_h

#include <cml/vector/temporary.h>
#include <cml/matrix/fwd.h>


/** @defgroup mathlib_vector_transform Vector Transformation Functions */

namespace cml {

/** @addtogroup mathlib_vector_transform */
/*@{*/

/** @defgroup mathlib_vector_transform_3D 3D Vector Transformations  */
/*@{*/

/** Apply a 3D affine transform to a 3D vector, taking basis orientation
 * into account.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not sized for a 3D affine transformation.  If
 * @c m is fixed-size, the size is checked at compile-time.
 *
 * @throws vector_size_error at run-time if @c v is dynamically-sized, and
 * is not 3D.  If @c v is fixed-size, the size is checked at compile-time.
 */
template<class Sub1, class Sub2> auto transform_vector(
  const readable_matrix<Sub1>& m, const readable_vector<Sub2>& v)
  -> temporary_of_t<Sub2>;

/*@}*/

/*@}*/

} // namespace cml

#define __CML_MATHLIB_VECTOR_TRANSFORM_TPP
#include <cml/mathlib/vector/transform.tpp>
#undef __CML_MATHLIB_VECTOR_TRANSFORM_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
