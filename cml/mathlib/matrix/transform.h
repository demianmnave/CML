/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_matrix_transform_h
#define	cml_mathlib_matrix_transform_h

#include <cml/vector/fwd.h>
#include <cml/matrix/fwd.h>
#include <cml/mathlib/constants.h>

/** @defgroup mathlib_matrix_transform Matrix Transform Functions */

namespace cml {

/** @addtogroup mathlib_matrix_transform */
/*@{*/

/** @defgroup mathlib_matrix_transform_3D 3D Matrix Transform Functions */
/*@{*/

/** Build a matrix representing a 'look at' view transform given the eye
 * position, target, reference up vector, and the handedness.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 4x4.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class SubEye, class SubTarget, class SubUp> void
matrix_look_at(writable_matrix<Sub>& m,
    const readable_vector<SubEye>& position,
    const readable_vector<SubTarget>& target,
    const readable_vector<SubUp>& up,
    AxisOrientation handedness);

/** Build a matrix representing a left-handed 'look at' view transform
 * given the eye position, target, and reference up vector.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 4x4.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class SubEye, class SubTarget, class SubUp> void
matrix_look_at_LH(writable_matrix<Sub>& m,
    const readable_vector<SubEye>& position,
    const readable_vector<SubTarget>& target,
    const readable_vector<SubUp>& up);

/** Build a matrix representing a right-handed 'look at' view transform
 * given the eye position, target, and reference up vector.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 4x4.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class SubEye, class SubTarget, class SubUp> void
matrix_look_at_RH(writable_matrix<Sub>& m,
    const readable_vector<SubEye>& position,
    const readable_vector<SubTarget>& target,
    const readable_vector<SubUp>& up);

/*@}*/

/*@}*/

} // namespace cml

#define __CML_MATHLIB_MATRIX_TRANSFORM_TPP
#include <cml/mathlib/matrix/transform.tpp>
#undef __CML_MATHLIB_MATRIX_TRANSFORM_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
