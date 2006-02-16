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

template<typename LeftT, typename RightT>
typename et::ScalarPromote<
    typename LeftT::value_type, typename RightT::value_type
>::type
dot(const LeftT& left, const RightT& right)
{
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* dot() requires that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    typedef typename left_traits::result_type::orient_tag left_orient;
    typedef typename right_traits::result_type::orient_tag right_orient;

    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */
    CML_STATIC_REQUIRE(
        (same_type<left_orient,row_vector>::is_true)
            && (same_type<right_orient,col_vector>::is_true));

    /* The return type: */
    typedef typename et::ScalarPromote<
        typename left_traits::value_type, typename right_traits::value_type
    >::type sum_type;

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time, and throws
     * at run-time if the sizes don't match:
     */
    et::CheckExprSizes<LeftT,RightT>()(left,right);

    /* Require at least one element: */
    if(left.size() < 1)
        throw std::invalid_argument(
                "dot() requires vectors having at least 1 element");

    /* Initialize the sum (these must be vector expressions, so it's okay
     * to use the array notation here):
     */
    sum_type sum(left[0]*right[0]);
    for(size_t i = 1; i < left.size(); ++i) {
        /* XXX This should probably be unrolled: */
        sum += left[i]*right[i];
    }

    /* Done: */
    return sum;
}

}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
