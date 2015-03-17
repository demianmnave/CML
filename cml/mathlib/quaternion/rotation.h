/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_quaternion_rotation_h
#define	cml_mathlib_quaternion_rotation_h

#include <cml/vector/temporary.h>
#include <cml/quaternion/writable_quaternion.h>

/** @defgroup mathlib_quaternion_rotation Quaternion Rotation Functions
 *
 * @note A number of these functions simply wrap calls to the corresponding
 * matrix functions. Some of them (the 'aim-at' and 'align' functions in
 * particular) might be considered a bit superfluous, since the resulting
 * quaternion will most likely be converted to a matrix at some point
 * anyway.  However, they're included here for completeness, and for
 * convenience in cases where a quaternion is being used as the primary
 * rotation representation.
 */

namespace cml {

/** @addtogroup mathlib_quaternion_rotation */
/*@{*/

/** Build a quaternion representing a rotation about world axis @c axis.
 *
 * @throws std::invalid_argument if @c axis < 0 or @c axis > 2.
 */
template<class Sub, class E> void
quaternion_rotation_world_axis(writable_quaternion<Sub>& q, int axis, E angle);

/** Build a quaternion representing a rotation about world x-axis. */
template<class Sub, class E> void
quaternion_rotation_world_x(writable_quaternion<Sub>& q, E angle);

/** Build a quaternion representing a rotation about world y-axis. */
template<class Sub, class E> void
quaternion_rotation_world_y(writable_quaternion<Sub>& q, E angle);

/** Build a quaternion representing a rotation about world z-axis. */
template<class Sub, class E> void
quaternion_rotation_world_z(writable_quaternion<Sub>& q, E angle);


/** Build a quaternion from an axis-angle pair.
 *
 * @throws vector_size_error at run-time if @c axis is dynamically-sized,
 * and is not 3D.  If @c axis is fixed-size, the size is checked at
 * compile-time.
 */
template<class Sub, class Axis, class E, enable_if_vector_t<Axis>* = nullptr>
void quaternion_rotation_axis_angle(
  writable_quaternion<Sub>& q, const Axis& axis, E angle);

/*@}*/

} // namespace cml

#define __CML_MATHLIB_QUATERNION_ROTATION_TPP
#include <cml/mathlib/quaternion/rotation.tpp>
#undef __CML_MATHLIB_QUATERNION_ROTATION_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
