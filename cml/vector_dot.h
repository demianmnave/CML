/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the dot product of two vectors.
 *
 *  @internal This does not need to return an expression type, since the
 *  temporary generation for the scalar result is handled automatically by
 *  the compiler.  i.e. when used in a vector expression, the result is
 *  automatically included in the expression tree as a temporary.
 */

#ifndef vector_dot_h
#define vector_dot_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/size_checking.h>
#include <cml/et/vector_promotions.h>

/* This is used below to create a more meaningful compile-time error when
 * dot is not provided with vector or VectorExpr arguments:
 */
struct dot_expects_vector_args_error;

/* This is used below to create a more meaningful compile-time error when
 * either argument has the wrong orientation.
 */
struct dot_expects_properly_oriented_args_error;

namespace cml {

/* Vector operators are in their own namespace: */
namespace vector_ops {

/** Vector dot (inner) product.
 *
 * This computes a dot b -> Scalar.
 *
 * @internal Because the return type is a scalar type (e.g. double), the
 * compiler will automatically synthesize a temporary into the expression
 * tree to hold the result.
 *
 * @todo The loop below may need to be explicitly unrolled to get the best
 * performance for fixed-size vectors.
 */
template<typename LeftT, typename RightT>
inline typename et::ScalarPromote<
    typename LeftT::value_type, typename RightT::value_type
>::type
dot(const LeftT& left, const RightT& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* dot() requires vector expressions: */
    typedef typename left_traits::result_tag left_result_tag;
    typedef typename right_traits::result_tag right_result_tag;
    CML_STATIC_REQUIRE_M(
            (same_type<left_result_tag,et::vector_result_tag>::is_true
             && same_type<right_result_tag,et::vector_result_tag>::is_true),
            dot_expects_vector_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

#if 0
    /* dot() requires that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    typedef typename left_traits::result_type::orient_tag left_orient;
    typedef typename right_traits::result_type::orient_tag right_orient;
    CML_STATIC_REQUIRE_M(
            (same_type<left_orient,row_vector>::is_true
             && same_type<right_orient,col_vector>::is_true),
            dot_expects_properly_oriented_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */
#endif

    /* Deduce the return type: */
    typedef typename et::ScalarPromote<
        typename left_traits::value_type, typename right_traits::value_type
    >::type sum_type;

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time, and throws
     * at run-time if the sizes don't match:
     */
    const size_t N = CheckedSize(left,right,et::vector_result_tag());

    /* Require at least one element: */
    if(N < 1) {
        throw std::invalid_argument(
                "dot() requires vectors having at least 1 element");
    }

    /* Initialize the sum.  Left and right must be vector expressions, so
     * it's okay to use array notation here:
     */
    sum_type sum(left[0]*right[0]);
    for(size_t i = 1; i < N; ++i) {
        sum += left[i]*right[i];
    }

    /* Done: */
    return sum;
}

} // namespace vector_ops
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
