/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Multiply two matrices.
 *
 * @todo Does it make sense to put mat-mat multiplication as a node into the
 * expression tree?
 *
 * @internal This does not need to return an expression type, since the
 * temporary generation for the matrix result is handled automatically by the
 * compiler.  i.e. when used in an expression, the result is automatically
 * included in the expression tree as a temporary by the compiler.
 */

#ifndef	matrix_mul_h
#define	matrix_mul_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/size_checking.h>
#include <cml/matrix/matrix_expr.h>


/* This is used below to create a more meaningful compile-time error when
 * mul is not provided with matrix or MatrixExpr arguments:
 */
struct mul_expects_matrix_args_error;

/* This is used below to create a more meaningful compile-time error when
 * fixed-size arguments to mul() have the wrong size:
 */
struct mul_expressions_have_wrong_size_error;

namespace cml {
namespace detail {

/** Verify the sizes of the argument matrices for matrix multiplication.
 *
 * @returns a matrix_size containing the size of the resulting matrix.
 */
template<typename LeftT, typename RightT> matrix_size
MatMulCheckedSize(const LeftT&, const RightT&, fixed_size_tag)
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
MatMulCheckedSize(const LeftT& left, const RightT& right, dynamic_size_tag)
{
    matrix_size left_N = left.size(), right_N = right.size();
    et::GetCheckedSize<LeftT,RightT,dynamic_size_tag>()
        .equal_or_fail(left_N.second, right_N.first); /* cols,rows */
    return matrix_size(left_N.first, right_N.second); /* rows,cols */
}


/** Matrix multiplication.
 *
 * Computes C = A x B using the slow O(n^3) algorithm.
 */
template<class LeftT, class RightT>
typename et::MatrixPromote<
    typename et::ExprTraits<LeftT>::result_type,
    typename et::ExprTraits<RightT>::result_type
>::temporary_type
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

    /* Deduce size type to ensure that a run-time check is performed if
     * necessary:
     */
    typedef typename left_traits::size_tag left_size;
    typedef typename right_traits::size_tag right_size;
    // typedef left_size size_tag;
    typedef typename select_if<
        same_type<left_size,right_size>::is_true
        && same_type<right_size,fixed_size_tag>::is_true,
        fixed_size_tag,dynamic_size_tag>::result size_tag;

    /* Require that left has the same number of columns as right has rows.
     * This automatically checks fixed-size matrices at compile time, and
     * throws at run-time if the sizes don't match:
     */
    detail::MatMulCheckedSize(left, right, size_tag());

    /* Deduce resulting matrix and element type.  ArrayPromotion is
     * specially implemeted to that the resulting type of two fixed-size
     * matrices has the same number of rows as left, and the same number of
     * cols as right.
     */
    typedef typename et::MatrixPromote<
        left_result,right_result>::temporary_type result_type;
    typedef typename result_type::value_type value_type;

    /* Create an array with the right size (resize() is a no-op for
     * fixed-size matrices):
     */
    result_type C;
    cml::et::detail::Resize(C, left.rows(), right.cols());

#if 1
    for(size_t i = 0; i < left.rows(); ++i) {
        for(size_t j = 0; j < right.cols(); ++j) {
            value_type sum(left(i,0)*right(0,j));
            for(size_t k = 1; k < right.rows(); ++k) {
                sum += (left(i,k)*right(k,j));
            }
            C(i,j) = sum;
        }
    }
#endif

#if 0
    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            value_type sum(left(i,0)*right(0,j));
            for(size_t k = 1; k < 4; ++k) {
                sum += (left(i,k)*right(k,j));
            }
            C(i,j) = sum;
        }
    }
#endif

#if 0
#if 1
    /* XXX ICC9/x86 Linux likes the unrolled version: */
    double sum;

    sum  = left(0,0)*right(0,0)
         + left(0,1)*right(1,0)
         + left(0,2)*right(2,0)
         + left(0,3)*right(3,0);
    C(0,0) = sum;

    sum  = left(0,0)*right(0,1)
         + left(0,1)*right(1,1)
         + left(0,2)*right(2,1)
         + left(0,3)*right(3,1);
    C(0,1) = sum;

    sum  = left(0,0)*right(0,2)
         + left(0,1)*right(1,2)
         + left(0,2)*right(2,2)
         + left(0,3)*right(3,2);
    C(0,2) = sum;

    sum  = left(0,0)*right(0,3)
         + left(0,1)*right(1,3)
         + left(0,2)*right(2,3)
         + left(0,3)*right(3,3);
    C(0,3) = sum;


    sum  = left(1,0)*right(0,0)
         + left(1,1)*right(1,0)
         + left(1,2)*right(2,0)
         + left(1,3)*right(3,0);
    C(1,0) = sum;

    sum  = left(1,0)*right(0,1)
         + left(1,1)*right(1,1)
         + left(1,2)*right(2,1)
         + left(1,3)*right(3,1);
    C(1,1) = sum;

    sum  = left(1,0)*right(0,2)
         + left(1,1)*right(1,2)
         + left(1,2)*right(2,2)
         + left(1,3)*right(3,2);
    C(1,2) = sum;

    sum  = left(1,0)*right(0,3)
         + left(1,1)*right(1,3)
         + left(1,2)*right(2,3)
         + left(1,3)*right(3,3);
    C(1,3) = sum;


    sum  = left(2,0)*right(0,0)
         + left(2,1)*right(1,0)
         + left(2,2)*right(2,0)
         + left(2,3)*right(3,0);
    C(2,0) = sum;

    sum  = left(2,0)*right(0,1)
         + left(2,1)*right(1,1)
         + left(2,2)*right(2,1)
         + left(2,3)*right(3,1);
    C(2,1) = sum;

    sum  = left(2,0)*right(0,2)
         + left(2,1)*right(1,2)
         + left(2,2)*right(2,2)
         + left(2,3)*right(3,2);
    C(2,2) = sum;

    sum  = left(2,0)*right(0,3)
         + left(2,1)*right(1,3)
         + left(2,2)*right(2,3)
         + left(2,3)*right(3,3);
    C(2,3) = sum;


    sum  = left(3,0)*right(0,0)
         + left(3,1)*right(1,0)
         + left(3,2)*right(2,0)
         + left(3,3)*right(3,0);
    C(3,0) = sum;

    sum  = left(3,0)*right(0,1)
         + left(3,1)*right(1,1)
         + left(3,2)*right(2,1)
         + left(3,3)*right(3,1);
    C(3,1) = sum;

    sum  = left(3,0)*right(0,2)
         + left(3,1)*right(1,2)
         + left(3,2)*right(2,2)
         + left(3,3)*right(3,2);
    C(3,2) = sum;

    sum  = left(3,0)*right(0,3)
         + left(3,1)*right(1,3)
         + left(3,2)*right(2,3)
         + left(3,3)*right(3,3);
    C(3,3) = sum;

#else
    C(0,0)  = left(0,0)*right(0,0);
    C(0,0) += left(0,1)*right(1,0);
    C(0,0) += left(0,2)*right(2,0);
    C(0,0) += left(0,3)*right(3,0);

    C(0,1)  = left(0,0)*right(0,1);
    C(0,1) += left(0,1)*right(1,1);
    C(0,1) += left(0,2)*right(2,1);
    C(0,1) += left(0,3)*right(3,1);

    C(0,2)  = left(0,0)*right(0,2);
    C(0,2) += left(0,1)*right(1,2);
    C(0,2) += left(0,2)*right(2,2);
    C(0,2) += left(0,3)*right(3,2);

    C(0,3)  = left(0,0)*right(0,3);
    C(0,3) += left(0,1)*right(1,3);
    C(0,3) += left(0,2)*right(2,3);
    C(0,3) += left(0,3)*right(3,3);

    C(1,0)  = left(1,0)*right(0,0);
    C(1,0) += left(1,1)*right(1,0);
    C(1,0) += left(1,2)*right(2,0);
    C(1,0) += left(1,3)*right(3,0);

    C(1,1)  = left(1,0)*right(0,1);
    C(1,1) += left(1,1)*right(1,1);
    C(1,1) += left(1,2)*right(2,1);
    C(1,1) += left(1,3)*right(3,1);

    C(1,2)  = left(1,0)*right(0,2);
    C(1,2) += left(1,1)*right(1,2);
    C(1,2) += left(1,2)*right(2,2);
    C(1,2) += left(1,3)*right(3,2);

    C(1,3)  = left(1,0)*right(0,3);
    C(1,3) += left(1,1)*right(1,3);
    C(1,3) += left(1,2)*right(2,3);
    C(1,3) += left(1,3)*right(3,3);

    C(2,0)  = left(2,0)*right(0,0);
    C(2,0) += left(2,1)*right(1,0);
    C(2,0) += left(2,2)*right(2,0);
    C(2,0) += left(2,3)*right(3,0);

    C(2,1)  = left(2,0)*right(0,1);
    C(2,1) += left(2,1)*right(1,1);
    C(2,1) += left(2,2)*right(2,1);
    C(2,1) += left(2,3)*right(3,1);

    C(2,2)  = left(2,0)*right(0,2);
    C(2,2) += left(2,1)*right(1,2);
    C(2,2) += left(2,2)*right(2,2);
    C(2,2) += left(2,3)*right(3,2);

    C(2,3)  = left(2,0)*right(0,3);
    C(2,3) += left(2,1)*right(1,3);
    C(2,3) += left(2,2)*right(2,3);
    C(2,3) += left(2,3)*right(3,3);

    C(3,0)  = left(3,0)*right(0,0);
    C(3,0) += left(3,1)*right(1,0);
    C(3,0) += left(3,2)*right(2,0);
    C(3,0) += left(3,3)*right(3,0);

    C(3,1)  = left(3,0)*right(0,1);
    C(3,1) += left(3,1)*right(1,1);
    C(3,1) += left(3,2)*right(2,1);
    C(3,1) += left(3,3)*right(3,1);

    C(3,2)  = left(3,0)*right(0,2);
    C(3,2) += left(3,1)*right(1,2);
    C(3,2) += left(3,2)*right(2,2);
    C(3,2) += left(3,3)*right(3,2);

    C(3,3)  = left(3,0)*right(0,3);
    C(3,3) += left(3,1)*right(1,3);
    C(3,3) += left(3,2)*right(2,3);
    C(3,3) += left(3,3)*right(3,3);
#endif
#endif

    return C;
}

} // namespace detail


/** operator*() for two matrices. */
template<typename E1, class AT1, typename L1,
         typename E2, class AT2, typename L2>
typename et::MatrixPromote<
    matrix<E1,AT1,L1>, matrix<E2,AT2,L2>
>::temporary_type
operator*(const matrix<E1,AT1,L1>& left,
          const matrix<E2,AT2,L2>& right)
{
    return detail::mul(left,right);
}

/** operator*() for a matrix and a MatrixXpr. */
template<typename E, class AT, typename L, typename XprT>
typename et::MatrixPromote<
    matrix<E,AT,L>, XprT
>::temporary_type
operator*(const matrix<E,AT,L>& left,
          const et::MatrixXpr<XprT>& right)
{
    /* Generate a temporary, and compute the right-hand expression: */
    typedef typename et::MatrixXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp;
    cml::et::detail::Resize(tmp,right.rows(),right.cols());
    tmp = right;

    return detail::mul(left,tmp);
}

/** operator*() for a MatrixXpr and a matrix. */
template<typename XprT, typename E, class AT, typename L>
typename et::MatrixPromote<
    XprT, matrix<E,AT,L>
>::temporary_type
operator*(const et::MatrixXpr<XprT>& left,
          const matrix<E,AT,L>& right)
{
    /* Generate a temporary, and compute the left-hand expression: */
    typedef typename et::MatrixXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp;
    cml::et::detail::Resize(tmp,left.rows(),left.cols());
    tmp = left;

    return detail::mul(tmp,right);
}

/** operator*() for two MatrixXpr's. */
template<typename XprT1, typename XprT2>
typename et::MatrixPromote<
    XprT1, XprT2
>::temporary_type
operator*(const et::MatrixXpr<XprT1>& left,
          const et::MatrixXpr<XprT2>& right)
{
    /* Generate temporaries and compute expressions: */
    typedef typename et::MatrixXpr<XprT1>::temporary_type left_tmp;
    left_tmp ltmp;
    cml::et::detail::Resize(ltmp,left.rows(),left.cols());
    ltmp = left;

    typedef typename et::MatrixXpr<XprT2>::temporary_type right_tmp;
    right_tmp rtmp;
    cml::et::detail::Resize(rtmp,right.rows(),right.cols());
    rtmp = right;

    return detail::mul(ltmp,rtmp);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
