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

#ifndef	matrix_mul_h
#define	matrix_mul_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/matrix_promotions.h>

/* This is used below to create a more meaningful compile-time error when
 * mul is not provided with matrix or MatrixExpr arguments:
 */
struct mul_expects_matrix_args_error;

namespace cml {

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
inline typename et::MatrixPromote<
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

    /* Then, require that A has the same number of rows as B has columns.
     * This automatically checks fixed-size vectors at compile time, and
     * throws at run-time if the sizes don't match:
     */
    CheckedSize(col(left,0), row(right,0), et::vector_result_tag());
    /* XXX This is probably a pretty inefficient way to verify the matrix
     * sizes---a dedicated size checker would be better here.
     */

    /* Deduce resulting matrix and element type: */
    typedef typename et::MatrixPromote<
        left_result,right_result>::type result_type;
    typedef typename result_type::value_type value_type;

    result_type C;
    for(size_t row = 0; row < left.rows(); ++row) {
        for(size_t col = 0; col < right.cols(); ++col) {
            value_type sum(left(row,0)*right(0,col));
            for(size_t k = 1; k < right.rows(); ++k) {
                sum += (left(row,k)*right(k,col));
            }
            C(row,col) = sum;
        }
    }

    return C;
}

} // namespace matrix_ops
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
