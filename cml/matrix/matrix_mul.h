/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Multiply two matrices.
 *
 * @todo Add a dedicated size checker for efficiency (if needed).
 *
 * @internal This does not need to return an expression type, since the
 * temporary generation for the matrix result is handled automatically by the
 * compiler.  i.e. when used in an expression, the result is automatically
 * included in the expression tree as a temporary by the compiler.
 *
 * @todo Completely unrolling the multiplication for 4x4 matrices gets
 * better-than-C performance with GCC 4 on a P4!
 */

#ifndef	matrix_mul_h
#define	matrix_mul_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>


/* This is used below to create a more meaningful compile-time error when
 * mul is not provided with matrix or MatrixExpr arguments:
 */
struct mul_expects_matrix_args_error;

/* This is used below to create a more meaningful compile-time error when
 * fixed-size arguments to mul() have the wrong size:
 */
struct mul_expressions_have_wrong_size_error;

namespace cml {

/* Detail contains helpers for mul() below: */
namespace detail {

/** Verify the sizes of the argument matrices for matrix multiplication.
 *
 * @returns a matrix_size containing the size of the resulting matrix.
 */
template<typename LeftT, typename RightT> matrix_size
CheckedSize(const LeftT&, const RightT&, fixed_size_tag)
{
    CML_STATIC_REQUIRE_M(
            ((size_t)LeftT::array_cols == (size_t)RightT::array_rows),
            mul_expressions_have_wrong_size_error);
    return matrix_size(LeftT::array_rows,RightT::array_cols);
}

/** Verify the sizes of the argument matrices for matrix multiplication.
 *
 * @returns a matrix_size containing the size of the resulting matrix.
 */
template<typename LeftT, typename RightT> matrix_size
CheckedSize(const LeftT& left, const RightT& right, dynamic_size_tag)
{
    matrix_size left_N = left.size(), right_N = right.size();
    et::GetCheckedSize<LeftT,RightT,dynamic_size_tag>()
        .equal_or_fail(left_N.second, right_N.first); /* cols,rows */
    return matrix_size(left_N.first, right_N.second); /* rows,cols */
}

} // namespace detail

/* Matrix operators are in their own namespace: */
namespace matrix_ops {

/** Matrix multiplication.
 *
 * Computes C = A x B using the slow O(n^3) algorithm.
 *
 * @internal With NRVO, there shouldn't be a temporary created on assignment.
 * A temporary will be generated if this is used as part of an expression
 * tree.
 */
template<class LeftT, class RightT>
typename et::MatrixPromote<
    typename et::ExprTraits<LeftT>::result_type,
    typename et::ExprTraits<RightT>::result_type
>::type
mul(const LeftT& left, const RightT& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;

    /* First, require matrix expressions: */
    typedef typename left_traits::result_tag left_result_tag;
    typedef typename right_traits::result_tag right_result_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<left_result_tag,et::matrix_result_tag>::is_true
             && same_type<right_result_tag,et::matrix_result_tag>::is_true),
            mul_expects_matrix_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    /* Deduce size type: */
    typedef typename left_traits::size_tag left_size;
    typedef typename right_traits::size_tag right_size;
    // typedef left_size size_tag;
    typedef typename select_if<
        same_type<left_size,right_size>::is_true
        && same_type<right_size,fixed_size_tag>::is_true,
        fixed_size_tag,dynamic_size_tag>::result size_tag;

    /* Require that left has the same number of columns as right has rows.
     * This automatically checks fixed-size vectors at compile time, and
     * throws at run-time if the sizes don't match:
     */
    detail::CheckedSize(left, right, size_tag());
    /* XXX This is probably a pretty inefficient way to verify the matrix
     * sizes---a dedicated size checker would be better here.
     */

    /* Deduce resulting matrix and element type.  ArrayPromotion is
     * specially implemeted to that the resulting type of two fixed-size
     * matrices has the same number of rows as left, and the same number of
     * cols as right.
     */
    typedef typename et::MatrixPromote<
        left_result,right_result>::type result_type;
    typedef typename result_type::value_type value_type;

    /* Create an array with the right size (resize() is a no-op for
     * fixed-size matrices):
     */
    /* XXX Unrolling these loops for 4x4 matrices gets better performance
     * than hand-coded C with GCC4 on a P4!
     */
    result_type C; C.resize(left.rows(), right.cols());
    for(size_t i = 0; i < left.rows(); ++i) {
        for(size_t j = 0; j < right.cols(); ++j) {
            value_type sum(left(i,0)*right(0,j));
            for(size_t k = 1; k < right.rows(); ++k) {
                sum += (left(i,k)*right(k,j));
            }
            C(i,j) = sum;
        }
    }

    return C;
}


/* This is for testing only: */
template<class LeftT, class RightT> void
mul(
        typename et::MatrixPromote<
            typename et::ExprTraits<LeftT>::result_type,
            typename et::ExprTraits<RightT>::result_type
        >::type& C,
        const LeftT& left,
        const RightT& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;

    /* First, require matrix expressions: */
    typedef typename left_traits::result_tag left_result_tag;
    typedef typename right_traits::result_tag right_result_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<left_result_tag,et::matrix_result_tag>::is_true
             && same_type<right_result_tag,et::matrix_result_tag>::is_true),
            mul_expects_matrix_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    /* Then, require that A has the same number of rows as B has columns.
     * This automatically checks fixed-size vectors at compile time, and
     * throws at run-time if the sizes don't match:
     */
    CheckedSize(left, right, et::vector_result_tag());
    /* XXX This is probably a pretty inefficient way to verify the matrix
     * sizes---a dedicated size checker would be better here.
     */

    /* Deduce resulting matrix and element type: */
    typedef typename et::MatrixPromote<
        left_result,right_result>::type result_type;
    typedef typename result_type::value_type value_type;

    for(size_t row = 0; row < left.rows(); ++row) {
        for(size_t col = 0; col < right.cols(); ++col) {
            value_type sum(left(row,0)*right(0,col));
            for(size_t k = 1; k < right.rows(); ++k) {
                sum += (left(row,k)*right(k,col));
            }
            C(row,col) = sum;
        }
    }
}

} // namespace matrix_ops

/** Dispatch for two matrices. */
template<typename E1, class AT1, typename E2, class AT2>
typename et::MatrixPromote< matrix<E1,AT1>, matrix<E2,AT2> >::type
operator*(const matrix<E1,AT1>& left,
          const matrix<E2,AT2>& right)
{
    return matrix_ops::mul(left,right);
}

/** Dispatch for a matrix and a MatrixXpr. */
template<typename E, class AT, typename XprT>
typename et::MatrixPromote< matrix<E,AT>, XprT >::type
operator*(const matrix<E,AT>& left,
          const et::MatrixXpr<XprT>& right)
{
    return matrix_ops::mul(left,right);
}

/** Dispatch for a MatrixXpr and a matrix.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_matrix, and right
 * must be a col_matrix.
 */
template<typename XprT, typename E, class AT>
typename et::MatrixPromote< XprT, matrix<E,AT> >::type
operator*(const et::MatrixXpr<XprT>& left,
          const matrix<E,AT>& right)
{
    return matrix_ops::mul(left,right);
}

/** Dispatch for two MatrixXpr's. */
template<typename XprT1, typename XprT2>
typename et::MatrixPromote<XprT1, XprT2>::type
operator*(const et::MatrixXpr<XprT1>& left,
          const et::MatrixXpr<XprT2>& right)
{
    return matrix_ops::mul(left,right);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
