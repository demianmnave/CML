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
#include <cml/vector.h>

#if !defined(CML_VECTOR_DOT_UNROLL_LIMIT)
#error "CML_VECTOR_DOT_UNROLL_LIMIT is undefined."
#endif

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

/* Wrap up specialized functions for dot(): */
namespace detail {

/** Helper struct that checks orientation of the arguments. */
template<typename LeftT, typename RightT>
struct ValidDotOrientation
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* Require that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    typedef typename left_traits::result_type::orient_tag left_orient;
    typedef typename right_traits::result_type::orient_tag right_orient;
#if defined(CML_IGNORE_VECTOR_ORIENTATION)
    enum { is_true = true };
#else
    enum { is_true = (same_type<left_orient,row_vector>::is_true
            && same_type<right_orient,col_vector>::is_true) };
#endif
};

/** Helper to simplify the unroller and the dot functions below.
 *
 * @internal This seems a bit hackish... is there a better way?
 */
template<typename LeftT, typename RightT>
struct DotHelper
{
    /* Store the expression traits types for the arguments: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* Record the size tags for the arguments: */
    typedef typename left_traits::result_type::size_tag left_size;
    typedef typename right_traits::result_type::size_tag right_size;

    /* Store the value types of the vectors: */
    typedef typename LeftT::value_type left_value;
    typedef typename RightT::value_type right_value;
    typedef et::OpMul<left_value, right_value> op_mul;
    typedef typename et::OpAdd<
        typename op_mul::value_type, typename op_mul::value_type> op_add;

    /* The final promotion for the scalar result: */
    typedef typename op_add::value_type promoted_scalar;
};

/** Construct a dot unroller for fixed-size arrays.
 *
 * @note This should only be called for vectors.
 *
 * @sa cml::vector_ops::dot
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
 * @sa cml::vector_ops::dot
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
    const size_t N = CheckedSize(left,right,dynamic_size_tag());

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

} // namespace detail


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
    using namespace meta;
    typedef typename select_switch<
        type_pair<left_size,right_size>,
        type_pair<fixed_size_tag,fixed_size_tag>, fixed_size_tag,
        Default,                                  dynamic_size_tag
    >::result size_tag;

    /* Call unroller: */
    return detail::UnrollDot(left,right,size_tag());
}

/** Operator* for two vector expression types.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<
    typename E1, class AT1, typename O1,
    typename E2, class AT2, typename O2>
typename detail::DotHelper<
    vector<E1,AT1,O1>, vector<E2,AT2,O2>
>::promoted_scalar
operator*(const vector<E1,AT1,O1>& left,
          const vector<E2,AT2,O2>& right)
{
    /* Require that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    CML_STATIC_REQUIRE_M(
            (detail::ValidDotOrientation<
                 vector<E1,AT1,O1>, vector<E2,AT2,O2> >::is_true),
            dot_expects_properly_oriented_args_error);

    return dot(left,right);
}

/** Dispatch for a vector and a VectorXpr.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<typename E, class AT, typename O, typename XprT>
typename detail::DotHelper< vector<E,AT,O>, XprT >::promoted_scalar
operator*(const vector<E,AT,O>& left,
          const et::VectorXpr<XprT>& right)
{
    /* Require that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    CML_STATIC_REQUIRE_M(
            (detail::ValidDotOrientation<vector<E,AT,O>, XprT>::is_true),
            dot_expects_properly_oriented_args_error);

    return dot(left,right);
}

/** Dispatch for a VectorXpr and a vector.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<typename XprT, typename E, class AT, typename O>
typename detail::DotHelper< XprT, vector<E,AT,O> >::promoted_scalar
operator*(const et::VectorXpr<XprT>& left,
          const vector<E,AT,O>& right)
{
    /* Require that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    CML_STATIC_REQUIRE_M(
            (detail::ValidDotOrientation<XprT, vector<E,AT,O> >::is_true),
            dot_expects_properly_oriented_args_error);

    return dot(left,right);
}

/** Dispatch for two VectorXpr's. */
template<typename XprT1, typename XprT2>
typename detail::DotHelper<XprT1,XprT2>::promoted_scalar
operator*(const et::VectorXpr<XprT1>& left,
          const et::VectorXpr<XprT2>& right)
{
    /* Shorthand: */
    typedef et::ExprTraits<XprT1> left_traits;
    typedef et::ExprTraits<XprT2> right_traits;

    /* Require that the left argument is a row_vector, and the right
     * argument is a col_vector:
     */
    CML_STATIC_REQUIRE_M(
            (detail::ValidDotOrientation<XprT1, XprT2>::is_true),
            dot_expects_properly_oriented_args_error);

    return dot(left,right);
}

} // namespace vector_ops
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
