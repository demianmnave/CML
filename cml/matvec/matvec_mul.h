/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Multiply two matrices.
 *
 * @todo Implement smarter temporary generation.
 *
 * @todo Does it make sense to put mat-vec multiplication as a node into the
 * expression tree?
 *
 * @internal This does not need to return an expression type, since the
 * temporary generation for the matrix result is handled automatically by the
 * compiler.  i.e. when used in an expression, the result is automatically
 * included in the expression tree as a temporary by the compiler.
 *
 * @internal The implementation here has a different form from the matrix
 * multiplication code since the order of the vector and matrix matter for the
 * purposes of determining the resulting vector type and size.  Having the
 * ability to treat vectors and matrices equivalently in the type system would
 * somewhat simplify things, e.g. by having an AsMatrix<> wrapper for vectors
 * that makes them behave as a matrix type.
 */

#ifndef	matvec_mul_h
#define	matvec_mul_h

#include <cml/core/cml_meta.h>
#include <cml/et/scalar_promotions.h>
#include <cml/vector/vector_expr.h>     // for et::detail::Resize
#include <cml/matvec/matvec_promotions.h>
#include <cml/matrix/matrix_expr.h>


/* This is used below to create a more meaningful compile-time error when
 * mat-vec mul is not provided with the right arguments:
 */
struct mvmul_expects_one_matrix_and_one_vector_arg_error;

/* This is used below to create a more meaningful compile-time error when
 * mat-vec mul is not provided with properly oriented arguments:
 */
struct mvmul_expects_properly_oriented_args_error;

namespace cml {

/* Matrix-vector operators are in their own namespace: */
namespace matvec_ops {

/* Detail contains helpers for mul() below: */
namespace detail {

/* For selecting the right order: */
typedef true_type mul_Ax;
typedef false_type mul_xA;

/** Compute A*x, A is a matrix, x is a (column) vector. */
template<typename ResultT, typename LeftT, typename RightT>
ResultT mul(const LeftT& A, const RightT& x, mul_Ax)
{
    /* Record summation type: */
    typedef typename ResultT::value_type sum_type;

    /* Record size type: */
    typedef typename ResultT::size_tag size_tag;

    /* Check the size: */
    size_t N = CheckedSize(A, x, size_tag());

    ResultT y;
    cml::et::detail::Resize(y, N);
    for(size_t i = 0; i < A.rows(); ++i) {
        /* XXX Should this be unrolled? */
        sum_type sum(A(i,0)*x[0]);
        for(size_t k = 1; k < x.size(); ++k) {
            sum += (A(i,k)*x[k]);
        }
        y[i] = sum;
    }
    return y;
}

/** Compute x*A, x is a (row) vector, A is a matrix. */
template<typename ResultT, typename LeftT, typename RightT>
ResultT mul(const LeftT& x, const RightT& A, mul_xA)
{
    /* Record summation type: */
    typedef typename ResultT::value_type sum_type;

    /* Record size type: */
    typedef typename ResultT::size_tag size_tag;

    /* Check the size: */
    size_t N = CheckedSize(x, A, size_tag());

    ResultT y;
    cml::et::detail::Resize(y, N);
    for(size_t i = 0; i < A.cols(); ++i) {
        /* XXX Should this be unrolled? */
        sum_type sum(x[0]*A(0,i));
        for(size_t k = 1; k < A.rows(); ++k) {
            sum += (x[k]*A(k,i));
        }
        y[i] = sum;
    }
    return y;
}

} // namespace detail


/* Mat-vec multiply without checking orientation: */
/* Note: specifying the legal combinations avoids a name clash with
 * matrix_ops::mul
 */

/** Dispatch for a matrix and a vector. */
template<typename E1, class AT1, class L,
         typename E2, class AT2, class O>
typename et::MatVecPromote<
    matrix<E1,AT1,L>, vector<E2,AT2,O>
>::temporary_type
mul(const matrix<E1,AT1,L>& left,
    const vector<E2,AT2,O>& right)
{
    typedef typename et::MatVecPromote<
        matrix<E1,AT1,L>, vector<E2,AT2,O>
    >::temporary_type result_type;
    return detail::mul<result_type>(left,right,detail::mul_Ax());
}

/** Dispatch for a matrix and a VectorXpr. */
template<typename E, class AT, class L, typename XprT>
typename et::MatVecPromote<
    matrix<E,AT,L>, XprT
>::temporary_type
mul(const matrix<E,AT,L>& left,
    const et::VectorXpr<XprT>& right)
{
    typedef typename et::MatVecPromote<
        matrix<E,AT,L>, XprT
    >::temporary_type result_type;

    /* Generate a temporary, and compute the right-hand expression: */
    typedef typename et::VectorXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp; cml::et::detail::Resize(tmp,right.size());
    tmp = right;

    /* Compute the answer: */
    return detail::mul<result_type>(left,tmp,detail::mul_Ax());
}

/** Dispatch for a MatrixXpr and a vector. */
template<typename XprT, typename E, class AT, class O>
typename et::MatVecPromote<
    XprT, vector<E,AT,O>
>::temporary_type
mul(const et::MatrixXpr<XprT>& left,
    const vector<E,AT,O>& right)
{
    typedef typename et::MatVecPromote<
        XprT, vector<E,AT,O>
    >::temporary_type result_type;

    /* Generate a temporary, and compute the left-hand expression: */
    typedef typename et::MatrixXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp;
    cml::et::detail::Resize(tmp,left.rows(),left.cols());
    tmp = left;

    /* Compute the answer: */
    return detail::mul<result_type>(tmp,right,detail::mul_Ax());
}

/** Dispatch for a MatrixXpr and a VectorXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<
    XprT1, XprT2
>::temporary_type
mul(const et::MatrixXpr<XprT1>& left,
    const et::VectorXpr<XprT2>& right)
{
    typedef typename et::MatVecPromote<
        XprT1, XprT2
    >::temporary_type result_type;

    /* Generate temporaries and compute expressions: */
    typedef typename et::MatrixXpr<XprT1>::temporary_type left_tmp;
    left_tmp ltmp;
    cml::et::detail::Resize(ltmp,left.rows(),left.cols());
    ltmp = left;

    typedef typename et::VectorXpr<XprT2>::temporary_type right_tmp;
    right_tmp rtmp; cml::et::detail::Resize(rtmp,right.size());
    rtmp = right;

    return detail::mul<result_type>(ltmp,rtmp,detail::mul_Ax());
}

/** Dispatch for a vector and a matrix. */
template<typename E1, class AT1, class O, typename E2, class AT2, class L>
typename et::MatVecPromote<
    vector<E1,AT1,O>, matrix<E2,AT2,L>
>::temporary_type
mul(const vector<E1,AT1,O>& left,
    const matrix<E2,AT2,L>& right)
{
    typedef typename et::MatVecPromote<
        vector<E1,AT1,O>, matrix<E2,AT2,L>
    >::temporary_type result_type;
    return detail::mul<result_type>(left,right,detail::mul_xA());
}

/** Dispatch for a VectorXpr and a matrix. */
template<typename XprT, typename E, class AT, class L>
typename et::MatVecPromote<
    XprT, matrix<E,AT,L>
>::temporary_type
mul(const et::VectorXpr<XprT>& left,
    const matrix<E,AT,L>& right)
{
    typedef typename et::MatVecPromote<
        XprT, matrix<E,AT,L>
    >::temporary_type result_type;

    /* Generate a temporary, and compute the left-hand expression: */
    typedef typename et::VectorXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp; cml::et::detail::Resize(tmp,left.size());
    tmp = left;

    return detail::mul<result_type>(tmp,right,detail::mul_xA());
}

/** Dispatch for a vector and a MatrixXpr. */
template<typename E, class AT, class O, typename XprT>
typename et::MatVecPromote<
    vector<E,AT,O>, XprT
>::temporary_type
mul(const vector<E,AT,O>& left,
    const et::MatrixXpr<XprT>& right)
{
    typedef typename et::MatVecPromote<
        vector<E,AT,O>, XprT
    >::temporary_type result_type;

    /* Generate a temporary, and compute the right-hand expression: */
    typedef typename et::MatrixXpr<XprT>::temporary_type expr_tmp;
    expr_tmp tmp;
    cml::et::detail::Resize(tmp,right.rows(),right.cols());
    tmp = right;

    /* Compute the answer: */
    return detail::mul<result_type>(left,tmp,detail::mul_Ax());
}

/** Dispatch for a VectorXpr and a MatrixXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<
    XprT1, XprT2
>::temporary_type
mul(const et::VectorXpr<XprT1>& left,
    const et::MatrixXpr<XprT2>& right)
{
    typedef typename et::MatVecPromote<
        XprT1, XprT2
    >::type::temporary_type result_type;

    /* Generate temporaries and compute expressions: */
    typedef typename et::VectorXpr<XprT1>::temporary_type left_tmp;
    left_tmp ltmp; cml::et::detail::Resize(ltmp,left.size());
    ltmp = left;

    typedef typename et::MatrixXpr<XprT2>::temporary_type right_tmp;
    right_tmp rtmp;
    cml::et::detail::Resize(rtmp,right.rows(),right.cols());
    rtmp = right;

    return detail::mul<result_type>(ltmp,rtmp,detail::mul_xA());
}

} // namespace matvec_ops

/* Global operators: */

/** Dispatch for a matrix and a vector. */
template<typename E1, class AT1, class L,
         typename E2, class AT2, class O>
typename et::MatVecPromote<
    matrix<E1,AT1,L>, vector<E2,AT2,O>
>::temporary_type
operator*(const matrix<E1,AT1,L>& left,
          const vector<E2,AT2,O>& right)
{
    /* Require a column vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O,col_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

/** Dispatch for a matrix and a VectorXpr. */
template<typename E, class AT, class L, typename XprT>
typename et::MatVecPromote<
    matrix<E,AT,L>, XprT
>::temporary_type
operator*(const matrix<E,AT,L>& left,
          const et::VectorXpr<XprT>& right)
{
    /* Require a column vector: */
    typedef typename XprT::result_type::oriented_tag orient_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<orient_tag,col_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

/** Dispatch for a MatrixXpr and a VectorXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<
    XprT1, XprT2
>::temporary_type
operator*(const et::MatrixXpr<XprT1>& left,
          const et::VectorXpr<XprT2>& right)
{
    /* Require a column vector: */
    typedef typename XprT2::result_type::oriented_tag orient_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<orient_tag,col_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

/** Dispatch for a vector and a matrix. */
template<typename E1, class AT1, class O, typename E2, class AT2, class L>
typename et::MatVecPromote<
    vector<E1,AT1,O>, matrix<E2,AT2,L>
>::temporary_type
operator*(const vector<E1,AT1,O>& left,
          const matrix<E2,AT2,L>& right)
{
    /* Require a row vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O,row_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

/** Dispatch for a VectorXpr and a matrix. */
template<typename XprT, typename E, class AT, class L>
typename et::MatVecPromote<
    XprT, matrix<E,AT,L>
>::temporary_type
operator*(const et::VectorXpr<XprT>& left,
          const matrix<E,AT,L>& right)
{
    /* Require a column vector: */
    typedef typename XprT::result_type::oriented_tag orient_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<orient_tag,col_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

/** Dispatch for a VectorXpr and a MatrixXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<
    XprT1, XprT2
>::temporary_type
operator*(const et::VectorXpr<XprT1>& left,
          const et::MatrixXpr<XprT2>& right)
{
    /* Require a column vector: */
    typedef typename XprT1::result_type::oriented_tag orient_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<orient_tag,col_vector>::is_true),
            mvmul_expects_properly_oriented_args_error);

    return matvec_ops::mul(left,right);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
