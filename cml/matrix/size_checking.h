/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_size_checking_h
#define	cml_matrix_size_checking_h

#include <cml/common/mpl/int_c.h>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/common/exception.h>

namespace cml {

/* Forward declarations: */
template<class Sub> class readable_matrix;

/** Exception thrown when run-time size checking is enabled, and the
 * operands of a matrix expression have incompatible sizes.
 */
struct incompatible_matrix_size_error : std::runtime_error {
  incompatible_matrix_size_error()
    : std::runtime_error("incompatible matrix expression sizes") {}
};

/** Exception thrown when run-time size checking is enabled, and the
 * operand of a matrix expression does not meet a minimum size.
 */
struct minimum_matrix_size_error : std::runtime_error {
  minimum_matrix_size_error()
    : std::runtime_error("matrix expression too small") {}
};

/** Exception thrown when run-time size checking is enabled, and the
 * operand of a matrix expression does not have the required size.
 */
struct matrix_size_error : std::runtime_error {
  matrix_size_error()
    : std::runtime_error("incorrect matrix expression size") {}
};



/** Front-end for both compile-time and run-time matrix binary expression
 * linear size checking.  Both expressions must derive from
 * readable_matrix.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First matrix expression.
 * @param right Second matrix expression.
 *
 * @throws incompatible_matrix_size_error at run-time if either left or
 * right is a dynamically-sized expression, and left.size() !=
 * right.size().  If both are fixed-size expressions, then the sizes are
 * checked at compile time.
 *
 * @throws incompatible_matrix_size_error at run-time if either left or
 * right is a dynamically-sized expression, and left.rows()*left.cols() !=
 * right.rows()*right.cols().  If left and right are fixed-size
 * expressions, then the sizes are checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_MATRIX_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void check_same_linar_size(
  const readable_matrix<Sub1>& left, const readable_matrix<Sub2>& right);

/** Front-end for both compile-time and run-time matrix binary expression
 * size checking against a fixed-size array.  The first expression must
 * derive from readable_matrix, and std::is_array<>::value must be true for
 * the second expression (e.g. double v[16]).
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left Matrix expression.
 * @param right Fixed-length array.
 *
 * @throws incompatible_matrix_size_error at run-time if left is a
 * dynamically-sized expression, and left.rows()*left.cols() !=
 * array_size_of(right).  If left is a fixed-size expression, then the
 * sizes are checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_MATRIX_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void
check_same_linear_size(const readable_matrix<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>* = 0);

/** Front-end for run-time matrix binary expression length checking.  The
 * first expression must derive from readable_matrix, and the second must
 * implement a size() method for this overload to be enabled.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First matrix expression.
 * @param right Second expression.
 *
 * @throws incompatible_matrix_size_error if left.rows()*left.cols() !=
 * right.size().
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_MATRIX_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> auto
check_same_linear_size(const readable_matrix<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void());


/** Front-end for matrix expression size checking against a run-time linear
 * size.  The expression must derive from readable_matrix.
 *
 * @throws matrix_size_error if left.rows()*left.cols() != N.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_MATRIX_SIZE_CHECKS at compile time.
 */
template<class Sub> void check_linear_size(
  const readable_matrix<Sub>& left, int N);

/** Front-end for compile-time and run-time matrix expression linear size
 * checking against an integer constant via int_c<N>.  The expression
 * must derive from readable_matrix.
 *
 * @throws minimum_matrix_size_error at run-time if left is a
 * dynamically-sized expression and left.rows()*left.cols() != N. If left
 * is a fixed-size expression, then the size is checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_MATRIX_SIZE_CHECKS at compile time.
 */
template<class Sub, int N> void check_linear_size(
  const readable_matrix<Sub>& left, int_c<N>);

/** Front-end for both compile-time and run-time matrix binary expression
 * size checking.  Both expressions must derive from readable_matrix.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First matrix expression.
 * @param right Second matrix expression.
 *
 * @throws incompatible_matrix_size_error at run-time if either left or
 * right is a dynamically-sized expression, and left.size() !=
 * right.size().  If both are fixed-size expressions, then the sizes are
 * checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void check_same_size(
  const readable_matrix<Sub1>& left, const readable_matrix<Sub2>& right);

/** Front-end for both compile-time and run-time matrix expression size
 * checking against a 2D C-array.  @c left must derive from
 * readable_matrix.
 *
 * @tparam Sub the actual type of the first expression.
 * @tparam Other the element type of the array.
 * @tparam Rows the number of array rows.
 * @tparam Cols the number of array cols.
 *
 * @param left First matrix expression.
 * @param right The 2D C-array.
 *
 * @throws incompatible_matrix_size_error at run-time if left is a
 * dynamically-sized expression and does not have the same number of rows
 * and columns as the array.  If left is a fixed-size expression, then the
 * sizes are checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub, class Other, int Rows, int Cols> void check_same_size(
  const readable_matrix<Sub>& left, Other const (&array)[Rows][Cols]);

} // namespace cml

#define __CML_MATRIX_SIZE_CHECKING_TPP
#include <cml/matrix/size_checking.tpp>
#undef __CML_MATRIX_SIZE_CHECKING_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
