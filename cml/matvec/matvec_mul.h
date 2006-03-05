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
 */

#ifndef	matvec_mul_h
#define	matvec_mul_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/matvec_promotions.h>
#include <cml/et/matrix_rowcol.h>
#include <cml/vector_dot.h>


/* This is used below to create a more meaningful compile-time error when
 * mat-vec mul is not provided with the right arguments:
 */
struct mvmul_expects_one_matrix_and_one_vector_arg_error;

namespace cml {

/* Matrix-vector operators are in their own namespace: */
namespace matvec_ops {

/* Detail contains helpers for mul() below: */
namespace detail {

/** Compute A*x, A is a matrix, x is a (column) vector. */
template<typename ResultT, typename LeftT, typename RightT> void
mul(ResultT& y, const LeftT& A, const RightT& x, true_type)
{
    /* Shorthand: */
    typedef typename ResultT::value_type sum_type;
    for(size_t i = 0; i < A.rows(); ++i) {
        /* XXX Should this be unrolled? */
        sum_type sum(A(i,0)*x[0]);
        for(size_t k = 1; k < x.size(); ++k) {
            sum += (A(i,k)*x[k]);
        }
        y[i] = sum;
    }
}

/** Compute x*A, x is a (row) vector, A is a matrix. */
template<typename ResultT, typename LeftT, typename RightT> void
mul(ResultT& y, const LeftT& x, const RightT& A, false_type)
{
    /* Shorthand: */
    typedef typename ResultT::value_type sum_type;
    for(size_t i = 0; i < A.cols(); ++i) {
        /* XXX Should this be unrolled? */
        sum_type sum(x[0]*A(0,i));
        for(size_t k = 1; k < A.rows(); ++k) {
            sum += (x[k]*A(k,i));
        }
        y[i] = sum;
    }
}

} // namespace detail

/** Matrix-vector multiplication.
 *
 * Computes C = A x b using a slow O(n^2) algorithm.  This function does
 * ignores the orientation of the argument vector (it's implied by calling
 * mul).
 *
 * @internal With NRVO, there shouldn't be a temporary created on assignment.
 * A temporary will be generated if this is used as part of an expression
 * tree.
 */
template<class LeftT, class RightT>
typename et::MatVecPromote<
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

    /* First, require the right argument types: */
    typedef typename left_traits::result_tag left_result_tag;
    typedef typename right_traits::result_tag right_result_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<left_result_tag,et::matrix_result_tag>::is_true
             && same_type<right_result_tag,et::vector_result_tag>::is_true)
            || (same_type<left_result_tag,et::vector_result_tag>::is_true
                && same_type<right_result_tag,et::matrix_result_tag>::is_true),
            mvmul_expects_one_matrix_and_one_vector_arg_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas.
     */

    /* Deduce size type: */
    typedef typename left_traits::size_tag left_size;
    typedef typename right_traits::size_tag right_size;
    // typedef left_size size_tag;
    typedef typename select_if<
        same_type<left_size,right_size>::is_true
        && same_type<right_size,fixed_size_tag>::is_true,
        fixed_size_tag,dynamic_size_tag>::result size_tag;

    /* Check the size: */
    size_t N = CheckedSize(left, right, size_tag());

    /* Deduce resulting matrix and element type: */
    typedef typename et::MatVecPromote<
        left_result,right_result>::type result_type;
    typedef typename result_type::value_type value_type;

    /* Create an array with the right size (resize() is a no-op for fixed-size
     * vectors):
     */
    result_type y; y.resize(N);
    
    /* Dispatch to the right multiplication, based upon whether left is a
     * matrix or a vector expression:
     */
    detail::mul(y, left, right,
            same_type<left_result_tag,et::matrix_result_tag>::is_true);

    /* Return the result: */
    return y;
}

} // namespace matvec_ops

/** Dispatch for a matrix and a vector. */
template<typename E1, class AT1, typename E2, class AT2, class O>
typename et::MatVecPromote< matrix<E1,AT1>, vector<E2,AT2,O> >::type
operator*(const matrix<E1,AT1>& left,
          const vector<E2,AT2,O>& right)
{
    return matvec_ops::mul(left,right);
}

/** Dispatch for a matrix and a VectorXpr. */
template<typename E, class AT, typename XprT>
typename et::MatVecPromote< matrix<E,AT>, XprT >::type
operator*(const matrix<E,AT>& left,
          const et::VectorXpr<XprT>& right)
{
    return matvec_ops::mul(left,right);
}

/** Dispatch for a MatrixXpr and a VectorXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<XprT1, XprT2>::type
operator*(const et::MatrixXpr<XprT1>& left,
          const et::VectorXpr<XprT2>& right)
{
    return matvec_ops::mul(left,right);
}

/** Dispatch for a vector and a matrix. */
template<typename E1, class AT1, class O, typename E2, class AT2>
typename et::MatVecPromote< vector<E1,AT1,O>, matrix<E2,AT2> >::type
operator*(const vector<E1,AT1,O>& left,
          const matrix<E2,AT2>& right)
{
    return matvec_ops::mul(left,right);
}

/** Dispatch for a VectorXpr and a matrix. */
template<typename XprT, typename E, class AT>
typename et::MatVecPromote< XprT, matrix<E,AT> >::type
operator*(const et::VectorXpr<XprT>& left,
          const matrix<E,AT>& right)
{
    return matvec_ops::mul(left,right);
}

/** Dispatch for a VectorXpr and a MatrixXpr. */
template<typename XprT1, typename XprT2>
typename et::MatVecPromote<XprT1, XprT2>::type
operator*(const et::VectorXpr<XprT1>& left,
          const et::MatrixXpr<XprT2>& right)
{
    return matvec_ops::mul(left,right);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
