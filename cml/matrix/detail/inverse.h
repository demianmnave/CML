/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_detail_inverse_h
#define	cml_matrix_detail_inverse_h

#include <array>
#include <vector>
#include <cml/common/mpl/int_c.h>
#include <cml/matrix/writable_matrix.h>

namespace cml {
namespace detail {

/** 2x2 inverse implementation. */
template<class Sub> inline void
inverse(writable_matrix<Sub>& M, int_c<2>)
{
  typedef value_type_trait_of_t<Sub>			value_type;

  /* Compute determinant and inverse: */
  value_type M00 = M(0,0), M01 = M(0,1);
  value_type M10 = M(1,0), M11 = M(1,1);
  value_type D = value_type(1) / (M00*M11 - M01*M10);

  /* Replace M: */
  M(0,0) =   M11*D;
  M(0,1) = - M01*D;
  M(1,0) = - M10*D;
  M(1,1) =   M00*D;
}

/** 3x3 inverse implementation. */
template<class Sub> inline void
inverse(writable_matrix<Sub>& M, int_c<3>)
{
  typedef value_type_trait_of_t<Sub>			value_type;

  /* Compute cofactors for each entry: */
  value_type m_00 = M(1,1)*M(2,2) - M(1,2)*M(2,1);
  value_type m_01 = M(1,2)*M(2,0) - M(1,0)*M(2,2);
  value_type m_02 = M(1,0)*M(2,1) - M(1,1)*M(2,0);

  value_type m_10 = M(0,2)*M(2,1) - M(0,1)*M(2,2);
  value_type m_11 = M(0,0)*M(2,2) - M(0,2)*M(2,0);
  value_type m_12 = M(0,1)*M(2,0) - M(0,0)*M(2,1);

  value_type m_20 = M(0,1)*M(1,2) - M(0,2)*M(1,1);
  value_type m_21 = M(0,2)*M(1,0) - M(0,0)*M(1,2);
  value_type m_22 = M(0,0)*M(1,1) - M(0,1)*M(1,0);

  /* Compute determinant from the minors: */
  value_type D =
    value_type(1) / (M(0,0)*m_00 + M(0,1)*m_01 + M(0,2)*m_02);

  /* Assign the inverse as (1/D) * (cofactor matrix)^T: */
  M(0,0) = m_00*D;  M(0,1) = m_10*D;  M(0,2) = m_20*D;
  M(1,0) = m_01*D;  M(1,1) = m_11*D;  M(1,2) = m_21*D;
  M(2,0) = m_02*D;  M(2,1) = m_12*D;  M(2,2) = m_22*D;
}

/** 4x4 inverse implementation. */
template<class Sub> inline void
inverse(writable_matrix<Sub>& M, int_c<4>)
{
  typedef value_type_trait_of_t<Sub>			value_type;

  /* Common cofactors, rows 0,1: */
  value_type m_22_33_23_32 = M(2,2)*M(3,3) - M(2,3)*M(3,2);
  value_type m_23_30_20_33 = M(2,3)*M(3,0) - M(2,0)*M(3,3);
  value_type m_20_31_21_30 = M(2,0)*M(3,1) - M(2,1)*M(3,0);
  value_type m_21_32_22_31 = M(2,1)*M(3,2) - M(2,2)*M(3,1);
  value_type m_23_31_21_33 = M(2,3)*M(3,1) - M(2,1)*M(3,3);
  value_type m_20_32_22_30 = M(2,0)*M(3,2) - M(2,2)*M(3,0);

  /* Compute minors: */
  value_type d00
    = M(1,1)*m_22_33_23_32+M(1,2)*m_23_31_21_33+M(1,3)*m_21_32_22_31;

  value_type d01
    = M(1,0)*m_22_33_23_32+M(1,2)*m_23_30_20_33+M(1,3)*m_20_32_22_30;

  value_type d02
    = M(1,0)*-m_23_31_21_33+M(1,1)*m_23_30_20_33+M(1,3)*m_20_31_21_30;

  value_type d03
    = M(1,0)*m_21_32_22_31+M(1,1)*-m_20_32_22_30+M(1,2)*m_20_31_21_30;

  /* Compute minors: */
  value_type d10
    = M(0,1)*m_22_33_23_32+M(0,2)*m_23_31_21_33+M(0,3)*m_21_32_22_31;

  value_type d11
    = M(0,0)*m_22_33_23_32+M(0,2)*m_23_30_20_33+M(0,3)*m_20_32_22_30;

  value_type d12
    = M(0,0)*-m_23_31_21_33+M(0,1)*m_23_30_20_33+M(0,3)*m_20_31_21_30;

  value_type d13
    = M(0,0)*m_21_32_22_31+M(0,1)*-m_20_32_22_30+M(0,2)*m_20_31_21_30;

  /* Common cofactors, rows 2,3: */
  value_type m_02_13_03_12 = M(0,2)*M(1,3) - M(0,3)*M(1,2);
  value_type m_03_10_00_13 = M(0,3)*M(1,0) - M(0,0)*M(1,3);
  value_type m_00_11_01_10 = M(0,0)*M(1,1) - M(0,1)*M(1,0);
  value_type m_01_12_02_11 = M(0,1)*M(1,2) - M(0,2)*M(1,1);
  value_type m_03_11_01_13 = M(0,3)*M(1,1) - M(0,1)*M(1,3);
  value_type m_00_12_02_10 = M(0,0)*M(1,2) - M(0,2)*M(1,0);

  /* Compute minors (uses row 3 as the multipliers instead of row 0,
   * which uses the same signs as row 0):
   */
  value_type d20
    = M(3,1)*m_02_13_03_12+M(3,2)*m_03_11_01_13+M(3,3)*m_01_12_02_11;

  value_type d21
    = M(3,0)*m_02_13_03_12+M(3,2)*m_03_10_00_13+M(3,3)*m_00_12_02_10;

  value_type d22
    = M(3,0)*-m_03_11_01_13+M(3,1)*m_03_10_00_13+M(3,3)*m_00_11_01_10;

  value_type d23
    = M(3,0)*m_01_12_02_11+M(3,1)*-m_00_12_02_10+M(3,2)*m_00_11_01_10;

  /* Compute minors: */
  value_type d30
    = M(2,1)*m_02_13_03_12+M(2,2)*m_03_11_01_13+M(2,3)*m_01_12_02_11;

  value_type d31
    = M(2,0)*m_02_13_03_12+M(2,2)*m_03_10_00_13+M(2,3)*m_00_12_02_10;

  value_type d32
    = M(2,0)*-m_03_11_01_13+M(2,1)*m_03_10_00_13+M(2,3)*m_00_11_01_10;

  value_type d33
    = M(2,0)*m_01_12_02_11+M(2,1)*-m_00_12_02_10+M(2,2)*m_00_11_01_10;

  /* Finally, compute determinant from the minors, and assign the
   * inverse as (1/D) * (cofactor matrix)^T:
   */
  value_type D = value_type(1) /
    (M(0,0)*d00 - M(0,1)*d01 + M(0,2)*d02 - M(0,3)*d03);
  M(0,0) = +d00*D; M(0,1) = -d10*D; M(0,2) = +d20*D; M(0,3) = -d30*D;
  M(1,0) = -d01*D; M(1,1) = +d11*D; M(1,2) = -d21*D; M(1,3) = +d31*D;
  M(2,0) = +d02*D; M(2,1) = -d12*D; M(2,2) = +d22*D; M(2,3) = -d32*D;
  M(3,0) = -d03*D; M(3,1) = +d13*D; M(3,2) = -d23*D; M(3,3) = +d33*D;
}

namespace {

/** Internal NxN inverse implementation using pivoting. @c row_index, @c
 * col_index, and @c pivoted should be either std::vector<> or
 * std::array<>, depending on whether the rank of @c M is known at run-time
 * or compile-time.
 */
template<class Sub, class RowIndexArray, class ColIndexArray, class Markers>
inline void inverse_pivot(writable_matrix<Sub>& M,
  RowIndexArray& row_index, ColIndexArray& col_index, Markers& pivoted
  )
{
  typedef value_type_trait_of_t<Sub>			value_type;
  typedef traits_of_t<value_type>			value_traits;

  int N = M.rows();

  /* For each column */
  for(int i = 0; i < N; ++ i) {

    /* Find the pivot */
    int row = 0, col = 0;
    value_type max = value_type(0);
    for(int j = 0; j < N; ++ j) {
      if(pivoted[j]) continue;

      for(int k = 0; k < N; ++ k) {
	if(pivoted[k]) continue;

	value_type mag = value_traits::fabs(M(j,k));
	if(mag > max) {
	  max = mag;
	  row = j;
	  col = k;
	}
      }
    }

    /* TODO: Check max against epsilon here to catch singularity */

    row_index[i] = row;
    col_index[i] = col;

    /* Swap rows if necessary */
    if(row != col) {
      for(int j = 0; j < M.cols(); ++ j)
       	std::swap(M(row,j), M(col,j));
    }

    /* Process pivot row */
    pivoted[col] = true;
    value_type pivot = M(col,col);
    M(col,col) = value_type(1);
    value_type k = value_type(1) / pivot;
    for(int j = 0; j < M.cols(); ++ j) M(col,j) *= k;
    /*M.row_op_mult(col,value_type(1)/pivot);*/

    /* Process other rows */
    for(int j = 0; j < N; ++ j) {
      if(j == col) continue;

      value_type mult = -M(j,col);
      M(j,col) = value_type(0);
      for(int k = 0; k < M.cols(); ++ k) M(j,k) += mult * M(col,k);
      /*M.row_op_add_mult(col,j,mult);*/
    }
  }

  /* Swap columns if necessary */
  for(int i = 0; i < N; ++ i) {
    if(row_index[i] == col_index[i]) continue;

    for(int j = 0; j < M.rows(); ++ j)
      std::swap(M(j,row_index[i]), M(j,col_index[i]));
    /*M.col_op_swap(row_index[i],col_index[i]);*/
  }
}

}

/** Inverse implementation for statically-sized matrices with rank greater
 * than 4, using a pivoting algorithm to compute the result.
 *
 * @note It is up to the caller to ensure @c M is a square matrix.
 */
template<class Sub, int N> inline void
inverse(writable_matrix<Sub>& M, int_c<N>)
{
  /* For tracking pivots */
  std::array<int, N> row_index, col_index;
  std::array<bool, N> pivoted; pivoted.fill(false);

  /* Call the implementation: */
  inverse_pivot(M, row_index, col_index, pivoted);
}

/** Inverse implementation for dynamically-sized matrices.  This dispatches
 * to a small matrix implementation when the rank of @c M is no more than
 * 4.  Otherwise, the general pivoting implementation is used.
 *
 * @note It is up to the caller to ensure @c M is a square matrix.
 */
template<class Sub> inline void
inverse(writable_matrix<Sub>& M, int_c<-1>)
{
  /* Size of matrix */
  int N = M.rows();

  /* Use small matrix inverse if possible: */
  switch(N) {
    case 2: inverse(M, int_c<2>()); return; break;
    case 3: inverse(M, int_c<3>()); return; break;
    case 4: inverse(M, int_c<4>()); return; break;
  }

  /* Otherwise, use the pivoting inverse: */

  /* For tracking pivots */
  std::vector<int> row_index(N), col_index(N);
  std::vector<bool> pivoted(N, false);

  /* Call the implementation: */
  inverse_pivot(M, row_index, col_index, pivoted);
}

} // namespace detail
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
