/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef typedef_h
#define typedef_h

#include <cml/vector.h>
#include <cml/matrix.h>
#include <cml/quaternion.h>
#include <cml/constants.h>
#include <cml/mathlib/epsilon.h>

namespace cml {

typedef vector< float,  fixed<2> > vector2f;
typedef vector< double, fixed<2> > vector2d;
typedef vector< float,  fixed<3> > vector3f;
typedef vector< double, fixed<3> > vector3d;
typedef vector< float,  fixed<4> > vector4f;
typedef vector< double, fixed<4> > vector4d;

typedef matrix< float,  fixed<2,2>, row_basis, row_major > matrix2x2f_r;
typedef matrix< float,  fixed<2,2>, col_basis, col_major > matrix2x2f_c;
typedef matrix< double, fixed<2,2>, row_basis, row_major > matrix2x2d_r;
typedef matrix< double, fixed<2,2>, col_basis, col_major > matrix2x2d_c;
typedef matrix< float,  fixed<3,3>, row_basis, row_major > matrix3x3f_r;
typedef matrix< float,  fixed<3,3>, col_basis, col_major > matrix3x3f_c;
typedef matrix< double, fixed<3,3>, row_basis, row_major > matrix3x3d_r;
typedef matrix< double, fixed<3,3>, col_basis, col_major > matrix3x3d_c;
typedef matrix< float,  fixed<4,4>, row_basis, row_major > matrix4x4f_r;
typedef matrix< float,  fixed<4,4>, col_basis, col_major > matrix4x4f_c;
typedef matrix< double, fixed<4,4>, row_basis, row_major > matrix4x4d_r;
typedef matrix< double, fixed<4,4>, col_basis, col_major > matrix4x4d_c;
typedef matrix< float,  fixed<3,2>, row_basis, row_major > matrix3x2f_r;
typedef matrix< double, fixed<3,2>, row_basis, row_major > matrix3x2d_r;
typedef matrix< float,  fixed<2,3>, col_basis, col_major > matrix2x3f_c;
typedef matrix< double, fixed<2,3>, col_basis, col_major > matrix2x3d_c;
typedef matrix< float,  fixed<4,3>, row_basis, row_major > matrix4x3f_r;
typedef matrix< double, fixed<4,3>, row_basis, row_major > matrix4x3d_r;
typedef matrix< float,  fixed<3,4>, col_basis, col_major > matrix3x4f_c;
typedef matrix< double, fixed<3,4>, col_basis, col_major > matrix3x4d_c;

typedef quaternion<float, fixed<>,vector_first,negative_cross> quaternionf_n;
typedef quaternion<float, fixed<>,vector_first,positive_cross> quaternionf_p;
typedef quaternion<double,fixed<>,vector_first,negative_cross> quaterniond_n;
typedef quaternion<double,fixed<>,vector_first,positive_cross> quaterniond_p;

typedef vector< float,  dynamic<> > vectorf;
typedef vector< double, dynamic<> > vectord;

typedef matrix< float,  dynamic<>, row_basis, row_major > matrixf_r;
typedef matrix< float,  dynamic<>, col_basis, col_major > matrixf_c;
typedef matrix< double, dynamic<>, row_basis, row_major > matrixd_r;
typedef matrix< double, dynamic<>, col_basis, col_major > matrixd_c;

typedef constants<float>  constantsf;
typedef constants<double> constantsd;

typedef epsilon<float>  epsilonf;
typedef epsilon<double> epsilond;

} // namespace cml

#endif