/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines vector dot and outer products.
 *
 * @todo Use VectorAccumulateUnroller to unroll the dot product.
 */

#ifndef vector_products_h
#define vector_products_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/size_checking.h>
#include <cml/vector/vector_unroller.h>
#include <cml/vector/vector_expr.h>
#include <cml/matrix/matrix_expr.h>

/* This is used below to create a more meaningful compile-time error when
 * dot is not provided with vector or VectorExpr arguments:
 */
struct dot_expects_vector_args_error;

/* This is used below to create a more meaningful compile-time error when
 * outer() is not provided with vector or VectorExpr arguments:
 */
struct outer_expects_vector_args_error;

namespace cml {
namespace detail {

template<typename LeftT, typename RightT>
struct DotPromote
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::value_type left_value;
    typedef typename right_traits::value_type right_value;

    /* Deduce the promoted scalar type: */
    /* XXX This is primarily for the unrolling code, which hasn't
     * been re-integrated yet.
     */
    typedef et::OpMul<left_value, right_value> op_mul;
    typedef typename et::OpAdd<
        typename op_mul::value_type,
                 typename op_mul::value_type> op_add;
    typedef typename op_add::value_type promoted_scalar;
};

template<typename LeftT, typename RightT>
struct OuterPromote
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_type;
    typedef typename right_traits::result_type right_type;

    /* Deduce the matrix result type: */
    typedef typename et::MatrixPromote<
        left_type,right_type>::temporary_type promoted_matrix;
};

} // namespace detail


template<typename LeftT, typename RightT>
typename detail::DotPromote<LeftT,RightT>::promoted_scalar
dot(const LeftT& left, const RightT& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_tag left_result;
    typedef typename right_traits::result_tag right_result;
    typedef typename detail::DotPromote<LeftT,RightT>
        ::promoted_scalar result_type;

    /* dot() requires vector expressions: */
    CML_STATIC_REQUIRE_M(
        (same_type<left_result, et::vector_result_tag>::is_true
         && same_type<right_result, et::vector_result_tag>::is_true),
        dot_expects_vector_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas.
     */

    /* Deduce the size tag to use to check sizes: */
    typedef typename left_traits::size_tag left_size;
    typedef typename right_traits::size_tag right_size;
    typedef typename select_switch<
        type_pair<left_size,right_size>,
        type_pair<fixed_size_tag,fixed_size_tag>, fixed_size_tag,
        Default,                                  dynamic_size_tag
    >::result size_tag;

    /* Verify that the arguments have the same length, and store it: */
    size_t N = et::CheckedSize(left,right,size_tag());

    /* Compute the dot product: */
    result_type sum(left[0]*right[0]);
    for(size_t i = 1; i < N; ++ i) {
        sum += left[i]*right[i];
    }
    return sum;
}

template<typename LeftT, typename RightT>
typename detail::OuterPromote<LeftT,RightT>::promoted_matrix
outer(const LeftT& left, const RightT& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_tag left_result;
    typedef typename right_traits::result_tag right_result;

    /* outer() requires vector expressions: */
    CML_STATIC_REQUIRE_M(
        (same_type<left_result, et::vector_result_tag>::is_true
         && same_type<right_result, et::vector_result_tag>::is_true),
        dot_expects_vector_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas.
     */

    /* Create a matrix with the right size (resize() is a no-op for
     * fixed-size matrices):
     */
    typename detail::OuterPromote<LeftT,RightT>::promoted_matrix C;
    cml::et::detail::Resize(C, left.size(), right.size());

    /* Now, compute the outer product: */
    for(size_t i = 0; i < left.size(); ++i) {
        for(size_t j = 0; j < right.size(); ++j) {
            C(i,j) = left[i]*right[j];
            /* Note: both arguments are vectors, so array notation
             * is okay here.
             */
        }
    }

    return C;
}

#if defined(CML_ENABLE_DOT_OPERATOR)

/** dot() via operator*() for two vectors. */
template<
    typename E1, class AT1,
    typename E2, class AT2>
typename detail::DotPromote<
    vector<E1,AT1>, vector<E2,AT2>
>::promoted_scalar
operator*(const vector<E1,AT1>& left,
          const vector<E2,AT2>& right)
{
    return dot(left,right);
}

/** dot() via operator*() for a vector and a VectorXpr. */
template<typename E, class AT, typename XprT>
typename detail::DotPromote<
    vector<E,AT>, typename XprT::result_type
>::promoted_scalar
operator*(const vector<E,AT>& left,
          const et::VectorXpr<XprT>& right)
{
    return dot(left,right);
}

/** dot() via operator*() for a VectorXpr and a vector. */
template<typename XprT, typename E, class AT>
typename detail::DotPromote<
    typename XprT::result_type, vector<E,AT>
>::promoted_scalar
operator*(const et::VectorXpr<XprT>& left,
          const vector<E,AT>& right)
{
    return dot(left,right);
}

/** dot() via operator*() for two VectorXpr's. */
template<typename XprT1, typename XprT2>
typename detail::DotPromote<
    typename XprT1::result_type, typename XprT2::result_type
>::promoted_scalar
operator*(const et::VectorXpr<XprT1>& left,
          const et::VectorXpr<XprT2>& right)
{
    return dot(left,right);
}

#endif

} // namespace cml

#endif





#if SAVE_THIS_FOR_LATER
/* XXX This is the unrolling dispatch code for dot(), from the now defunct
 * vector_dot.h header:
 */

/** Construct a dot unroller for fixed-size arrays.
 *
 * @note This should only be called for vectors.
 *
 * @sa cml::dot
 */
template<typename LeftT, typename RightT>
typename DotHelper<LeftT,RightT>::promoted_scalar
UnrollDot(const LeftT& left, const RightT& right, fixed_size_tag)
{
    /* Shorthand: */
    typedef DotHelper<LeftT,RightT> dot_helper;

    /* Compile-type vector size check: */
    typedef typename et::GetCheckedSize<LeftT,RightT,fixed_size_tag>
        ::check_type check_sizes;

    /* Get the fixed array size using the helper: */
    enum { Len = check_sizes::array_size };

    /* Record the unroller type: */
    typedef typename dot_helper::op_mul op_mul;
    typedef typename dot_helper::op_add op_add;
    typedef typename et::detail::VectorAccumulateUnroller<
        op_add,op_mul,LeftT,RightT>::template
        Eval<0, Len-1, (Len <= CML_VECTOR_DOT_UNROLL_LIMIT)> Unroller;
    /* Note: Len is the array size, so Len-1 is the last element. */

    /* Now, call the unroller: */
    return Unroller()(left,right);
}

/** Use a loop to compute the dot product for dynamic arrays.
 *
 * @note This should only be called for vectors.
 *
 * @sa cml::dot
 */
template<typename LeftT, typename RightT>
typename DotHelper<LeftT,RightT>::promoted_scalar
UnrollDot(const LeftT& left, const RightT& right, dynamic_size_tag)
{
    /* Shorthand: */
    typedef DotHelper<LeftT,RightT> dot_helper;
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename dot_helper::op_mul op_mul;
    typedef typename dot_helper::op_add op_add;

    /* Record the return type: */
    typedef typename dot_helper::promoted_scalar sum_type;

    /* Verify expression sizes: */
    const size_t N = et::CheckedSize(left,right,dynamic_size_tag());

    /* Initialize the sum. Left and right must be vector expressions, so
     * it's okay to use array notation here:
     */
    sum_type sum(op_mul().apply(left[0],right[0]));
    for(size_t i = 1; i < N; ++i) {
        /* XXX This might not be optimized properly by some compilers.
         * but to do anything else requires changing the requirements
         * of a scalar operator, or requires defining a new class of scalar
         * <op>= operators.
         */
        sum = op_add().apply(sum, op_mul().apply(left[i], right[i]));
        /* Note: we don't need get(), since both arguments are required to
         * be vector expressions.
         */
    }
    return sum;
}

/** Vector dot (inner) product implementation.
 *
 * This computes a dot b -> Scalar without checking the vector orientation
 * (orientation is implied by the call to dot()).
 *
 * @todo Figure out if the source or destination size type should trigger
 * unrolling.  May need a per-compiler compile-time option for this.
 */
template<typename LeftT, typename RightT>
typename detail::DotHelper<LeftT,RightT>::promoted_scalar
dot(const LeftT& left, const RightT& right)
{
    /* Shorthand: */
    typedef detail::DotHelper<LeftT,RightT> dot_helper;
    typedef typename dot_helper::left_size left_size;
    typedef typename dot_helper::right_size right_size;

    /* dot() requires vector expressions: */
    CML_STATIC_REQUIRE_M(
            (et::VectorExpressions<LeftT,RightT>::is_true),
            dot_expects_vector_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    /* Figure out the unroller to use (fixed or dynamic): */
    typedef typename select_switch<
        type_pair<left_size,right_size>,
        type_pair<fixed_size_tag,fixed_size_tag>, fixed_size_tag,
        Default,                                  dynamic_size_tag
    >::result size_tag;

    /* Call unroller: */
    return detail::UnrollDot(left,right,size_tag());
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
