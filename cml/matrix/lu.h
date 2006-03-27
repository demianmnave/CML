/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Implements LU decomposition for square matrix expressions.
 *
 * @todo The LU implementation does not check for a zero diagonal entry
 * (implying that the input has no LU factorization).
 *
 * @todo Should also have a pivoting implementation.
 *
 * @todo need to throw a numeric error if the determinant of the matrix
 * given to lu(), lu_solve(), or inverse() is 0.
 *
 * @internal The implementation is the same for fixed- and dynamic-size
 * matrices.  It can be sped up for small matrices later.
 */

#ifndef lu_h
#define lu_h

#include <cml/et/size_checking.h>
#include <cml/matrix/matrix_expr.h>
#include <cml/matvec/matvec_promotions.h>

/* This is used below to create a more meaningful compile-time error when
 * lu is not provided with a matrix or MatrixExpr argument:
 */
struct lu_expects_a_matrix_arg_error;

/* This is used below to create a more meaningful compile-time error when
 * lu is not provided with a square matrix or MatrixExpr argument:
 */
struct lu_expects_a_square_matrix_arg_error;

/* This is used below to create a more meaningful compile-time error when
 * lu_inplace is not provided with an assignable matrix argument:
 */
struct lu_inplace_expects_an_assignable_matrix_arg_error;

namespace cml {
namespace detail {

/** Verify the sizes of the argument matrices for matrix multiplication.
 *
 * @returns a matrix_size containing the size of the resulting matrix.
 */
template<typename MatT> inline size_t
LUCheckedSize(const MatT&, fixed_size_tag)
{
    CML_STATIC_REQUIRE_M(
            ((size_t)MatT::array_rows == (size_t)MatT::array_cols),
            lu_expects_a_square_matrix_arg_error);
    return (size_t)MatT::array_rows;
}

/** Verify the sizes of the argument matrices for matrix multiplication.
 *
 * @returns a matrix_size containing the size of the resulting matrix.
 */
template<typename MatT> inline size_t
LUCheckedSize(const MatT& m, dynamic_size_tag)
{
    matrix_size N = m.size();
    et::GetCheckedSize<MatT,MatT,dynamic_size_tag>()
        .equal_or_fail(N.first, N.second);
    return N.first;
}

/* Compute the LU decomposition in-place: */
template<class MatT> inline
void lu_inplace(MatT& A)
{
    /* Shorthand: */
    typedef et::ExprTraits<MatT> arg_traits;
    typedef typename arg_traits::result_tag arg_result;
    typedef typename arg_traits::assignable_tag arg_assignment;
    typedef typename arg_traits::size_tag size_tag;
    typedef typename arg_traits::value_type value_type;

    /* lu_inplace() requires an assignable matrix expression: */
    CML_STATIC_REQUIRE_M(
        (same_type<arg_result, et::matrix_result_tag>::is_true
         && same_type<arg_assignment, et::assignable_tag>::is_true),
        lu_inplace_expects_an_assignable_matrix_arg_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas.
     */

    /* Verify that the matrix is square, and get the size: */
    ssize_t N = (ssize_t) detail::LUCheckedSize(A, size_tag());

    /* Compute the LU factorizaion in-place (the first row is the same
     * as the first row of A):
     */
    /* Note: need ssize_t here so that i-1 is actually negative when i = 0: */
    for(ssize_t i = 1; i < N; ++i) {
        /* Compute the factorization for row i such that it only depends upon
         * row i-1:
         */

        value_type L;
        for(ssize_t j = 0; j <= i-1; ++j) {
            L = A(i,j);
            for(ssize_t k = 0; k < j-1; ++k) {
                L -= A(i,k)*A(k,j);
            }
            
            /* XXX Need to check that A(j,j) != 0. here!!! */
            A(i,j) = L/A(j,j);
        }

        /* Now compute U(i,i..N): */
        value_type U;
        for(ssize_t j = i; j < N; ++j) {
            U = A(i,j);
            for(ssize_t k = 0; k < i-1; ++k) {
                U -= A(i,k)*A(k,j);
            }
            A(i,j) = U;
        }
    }
}

/* Compute the LU decomposition, and return a copy of the result: */
template<class MatT>
inline typename MatT::temporary_type
lu_copy(const MatT& M)
{
    /* Shorthand: */
    typedef et::ExprTraits<MatT> arg_traits;
    typedef typename arg_traits::result_tag arg_result;

    /* lu_with_copy() requires a matrix expression: */
    CML_STATIC_REQUIRE_M(
        (same_type<arg_result, et::matrix_result_tag>::is_true),
        lu_expects_a_matrix_arg_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas.
     */

    /* Use the in-place LU function, and return the result: */
    typename MatT::temporary_type A;
    cml::et::detail::Resize(A,M.rows(),M.cols());
    A = M;
    lu_inplace(A);
    return A;
}

} // namespace detail

/** LU factorization for a matrix. */
template<typename E, class AT, class L>
inline typename matrix<E,AT,L>::temporary_type
lu(const matrix<E,AT,L>& m)
{
    return detail::lu_copy(m);
}

/** LU factorization for a matrix expression. */
template<typename XprT>
inline typename et::MatrixXpr<XprT>::temporary_type
lu(const et::MatrixXpr<XprT>& e)
{
    return detail::lu_copy(e);
}

/** Solve y = LUx for x.
 *
 * This solves Lb = y for b by forward substitution, then Ux = b for x by
 * backward substitution.
 */
template<typename MatT, typename VecT> inline
typename et::MatVecPromote<MatT,VecT>::temporary_type
lu_solve(const MatT& LU, const VecT& y)
{
    /* Shorthand. */
    typedef et::ExprTraits<MatT> lu_traits;
    typedef typename et::MatVecPromote<MatT,VecT>::temporary_type vector_type;
    typedef typename vector_type::value_type value_type;

    /* Verify that the matrix is square, and get the size: */
    ssize_t N = (ssize_t) detail::LUCheckedSize(
            LU, typename lu_traits::size_tag());

    /* Verify that the matrix and vector have compatible sizes: */
    et::CheckedSize(LU, y, typename vector_type::size_tag());

    /* Solve Lb = y for b by forward substitution.  The entries below the
     * diagonal of LU correspond to L, understood to be below a diagonal of
     * 1's:
     */
    vector_type b; cml::et::detail::Resize(b,N);
    b[0] = y[0];
    for(ssize_t i = 1; i < N; ++i) {

        /* Compute left-hand sum of L(i,k)*b[i] up to k = i-1 (L(i,i)=1): */
        value_type lhs = b[0]*LU(i,0) ;
        for(ssize_t k = 1; k < i-1; ++k) {
            lhs += b[k]*LU(i,k);
        }

        /* L(i,i)*b[i] = b[i], so b[i] = y[i] - lhs: */
        b[i] = y[i] - lhs;
    }

    /* Solve Ux = b for x by backward substitution.  The entries at and above
     * the diagonal of LU correspond to U:
     */
    vector_type x; cml::et::detail::Resize(x,N);
    x[N-1] = b[N-1]/LU(N-1,N-1);
    for(ssize_t i = 2; i <= N; ++i) {

        /* Compute left-hand sum of U(N-i,k)*x[N-i+1] from k = N-i+1 to k =
         * N-1:
         */
        value_type lhs = LU(N-i,N-i+1)*x[N-i+1];
        for(ssize_t k = N-i+2; k < N; ++k) {
            lhs += LU(N-i,k)*x[k];
        }

        /* U(N-i,N-i) != 1, so x[N-i] = (b[N-i] - lhs)/U(N-i,N-i): */
        x[N-i] = (b[N-i] - lhs)/LU(N-i,N-i);
    }

    /* Return x: */
    return x;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
