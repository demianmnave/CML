/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_mathlib_matrix_rotation_h
#define	cml_mathlib_matrix_rotation_h

#include <cml/vector/fwd.h>
#include <cml/matrix/fwd.h>
#include <cml/mathlib/euler_order.h>

/** @defgroup mathlib_matrix_rotation Matrix Rotation Functions */

namespace cml {

/** @addtogroup mathlib_matrix_rotation */
/*@{*/

/** @defgroup mathlib_matrix_rotation_builders 2D Rotation Matrix Builders  */
/*@{*/

/** Compute a 2D rotation matrix give @c angle.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 2x2.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class E> void
matrix_rotation_2D(writable_matrix<Sub>& m, E angle);

/*@}*/

/** @defgroup mathlib_matrix_rotation_builders 3D Rotation Matrix Builders  */
/*@{*/

/** Compute a rotation matrix from an axis and angle.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 3x3.  If @c m is fixed-size, the
 * size is checked at compile-time.
 *
 * @throws vector_size_error at run-time if @c v is dynamically-sized, and
 * is not 3D.  If @c v is fixed-size, the size is checked at compile-time.
 */
template<class Sub1, class Sub2, class E> void matrix_rotation_axis_angle(
  writable_matrix<Sub1>& m, const readable_vector<Sub2>& axis, const E& angle);

/** Compute a rotation matrix given three Euler angles and the required
 * order.
 *
 * The rotations are applied about the cardinal axes in the order specified
 * by the 'order' argument, where 'order' is one of the following
 * enumerants:
 *
 * euler_order_xyz
 * euler_order_xzy
 * euler_order_xyx
 * euler_order_xzx
 * euler_order_yzx
 * euler_order_yxz
 * euler_order_yzy
 * euler_order_yxy
 * euler_order_zxy
 * euler_order_zyx
 * euler_order_zxz
 * euler_order_zyz
 *
 * e.g. euler_order_xyz means compute the column-basis rotation matrix
 * equivalent to R_x * R_y * R_z, where R_i is the rotation matrix above
 * axis i (the row-basis matrix would be R_z * R_y * R_x).
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 3x3.  If @c m is fixed-size, the
 * size is checked at compile-time.
 */
template<class Sub, class E0, class E1, class E2> void
matrix_rotation_euler(writable_matrix<Sub>& m,
  E0 angle_0, E1 angle_1, E2 angle_2, EulerOrder order);

/** Build a matrix of derivatives of Euler angles about the specified axis.
 *
 * The rotation derivatives are applied about the cardinal axes in the
 * order specified by the 'order' argument, where 'order' is one of the
 * following enumerants:
 *
 * euler_order_xyz
 * euler_order_xzy
 * euler_order_yzx
 * euler_order_yxz
 * euler_order_zxy
 * euler_order_zyx
 *
 * e.g. euler_order_xyz means compute the column-basis rotation matrix
 * equivalent to R_x * R_y * R_z, where R_i is the rotation matrix above
 * axis i (the row-basis matrix would be R_z * R_y * R_x).
 *
 * The derivative is taken with respect to the specified 'axis', which is
 * the position of the axis in the triple; e.g. if order = euler_order_xyz,
 * then axis = 0 would mean take the derivative with respect to x.  Note
 * that repeated axes are not currently supported.
 *
 * @throws minimum_matrix_size_error at run-time if @c m is
 * dynamically-sized, and is not at least 3x3.  If @c m is fixed-size, the
 * size is checked at compile-time.
 *
 * @throws std::invalid_argument if @c axis is not 0, 1, or 2, or if @c
 * order has a repeated axis.
 */
template<class Sub, class E0, class E1, class E2> void
matrix_rotation_euler_derivatives(writable_matrix<Sub>& m, int axis,
  E0 angle_0, E1 angle_1, E2 angle_2, EulerOrder order);

/*@}*/

/*@}*/

} // namespace cml

#define __CML_MATHLIB_MATRIX_ROTATION_TPP
#include <cml/mathlib/matrix/rotation.tpp>
#undef __CML_MATHLIB_MATRIX_ROTATION_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
