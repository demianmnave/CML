/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the dot product of two vectors.
 */

#ifndef vector_dot_h
#define vector_dot_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/size_checking.h>
#include <cml/et/vector_promotions.h>

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
 * performance.
 */
template<typename LeftT, typename RightT>
inline typename et::ScalarPromote<
    typename LeftT::value_type, typename RightT::value_type
>::type
dot(const LeftT& left, const RightT& right)
{
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* First, require vector expressions: */
    typedef typename left_traits::result_tag left_result_tag;
    typedef typename right_traits::result_tag right_result_tag;
    CML_STATIC_REQUIRE(
            (same_type<left_result_tag,et::vector_result_tag>::is_true
             && same_type<right_result_tag,et::vector_result_tag>::is_true));
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    /* dot() requires that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    typedef typename left_traits::result_type::orient_tag left_orient;
    typedef typename right_traits::result_type::orient_tag right_orient;
    CML_STATIC_REQUIRE(
            (same_type<left_orient,row_vector>::is_true
             && same_type<right_orient,col_vector>::is_true));
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    /* Deduce the return type: */
    typedef typename et::ScalarPromote<
        typename left_traits::value_type, typename right_traits::value_type
    >::type sum_type;

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time, and throws
     * at run-time if the sizes don't match:
     */
    et::CheckLinearExprSizes<LeftT,RightT,et::vector_result_tag>()(left,right);

    /* Require at least one element: */
    if(left.size() < 1) {
        throw std::invalid_argument(
                "dot() requires vectors having at least 1 element");
    }

    /* Initialize the sum.  Left and right must be vector expressions, so
     * it's okay to use array notation here:
     */
    sum_type sum(left[0]*right[0]);
    for(size_t i = 1; i < left.size(); ++i) {
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
