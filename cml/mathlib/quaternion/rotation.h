/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_quaternion_rotation_h
#define	cml_mathlib_quaternion_rotation_h

#include <cml/vector/fwd.h>
#include <cml/matrix/fwd.h>
#include <cml/quaternion/writable_quaternion.h>
#include <cml/mathlib/euler_order.h>
#include <cml/mathlib/axis_order.h>

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

/** @defgroup mathlib_quaternion_rotation_builders Quaternion Rotation Builders  */
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
template<class Sub, class ASub, class E> void
quaternion_rotation_axis_angle(
  writable_quaternion<Sub>& q, const readable_vector<ASub>& axis, E angle);

/** Build a quaternion from a rotation matrix.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 3x3.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class MSub> void
quaternion_rotation_matrix(
  writable_quaternion<Sub>& q, const readable_matrix<MSub>& m);

template<class Sub, class E0, class E1, class E2> void
quaternion_rotation_euler(writable_quaternion<Sub>& q,
  E0 angle_0, E1 angle_1, E2 angle_2, euler_order order);

/*@}*/


/** @defgroup mathlib_quaternion_rotation_alignment Quaternion Alignment  */
/*@{*/

/** Compute a quaternion that aligns vector @c align to @c reference,
 * using rotations in axis order @c order.
 *
 * @note This uses matrix_rotation_align internally.
 */
template<class Sub, class ASub, class RSub> void
quaternion_rotation_align(writable_quaternion<Sub>& q,
  const readable_vector<ASub>& align, const readable_vector<RSub>& reference,
  bool normalize = true, AxisOrder order = axis_order_zyx);

/** Compute a quaternion to align the vector from @c pos to @c target
 * with @c reference.
 *
 * @note This uses matrix_rotation_aim_at internally.
 */
template<class Sub, class PSub, class TSub, class RSub> void
quaternion_rotation_aim_at(writable_quaternion<Sub>& q,
  const readable_vector<PSub>& pos, const readable_vector<TSub>& target,
  const readable_vector<RSub>& reference, AxisOrder order = axis_order_zyx);

/*@}*/

/*@}*/

} // namespace cml

#define __CML_MATHLIB_QUATERNION_ROTATION_TPP
#include <cml/mathlib/quaternion/rotation.tpp>
#undef __CML_MATHLIB_QUATERNION_ROTATION_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
