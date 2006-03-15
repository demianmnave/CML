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
 * either argument to dot() has the wrong orientation.
 */
struct dot_expects_properly_oriented_args_error;

/* This is used below to create a more meaningful compile-time error when
 * outer() is not provided with vector or VectorExpr arguments:
 */
struct outer_expects_vector_args_error;

namespace cml {
namespace vector_ops {

namespace detail {

/* Compute the dot product: */
template<class LeftT, class RightT>
struct dot_impl
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename left_traits::value_type left_value;
    typedef typename right_traits::value_type right_value;

    typedef et::OpMul<left_value, right_value> op_mul;
    typedef typename et::OpAdd<
        typename op_mul::value_type,
                 typename op_mul::value_type> op_add;
    typedef typename op_add::value_type result_type;

    /* XXX This can be unrolled, but use a loop for now: */
    result_type operator()(const LeftT& left, const RightT& right) const
    {
        /* Deduce the size tag to use to check sizes: */
        typedef typename left_result::size_tag left_size;
        typedef typename right_result::size_tag right_size;

        using namespace meta;
        typedef typename select_switch<
            type_pair<left_size,right_size>,
            type_pair<fixed_size_tag,fixed_size_tag>, fixed_size_tag,
            Default,                                  dynamic_size_tag
        >::result size_tag;

        size_t N = CheckedSize(left,right,size_tag());
        result_type sum(left[0]*right[0]);
        for(size_t i = 1; i < N; ++ i) {
            sum += left[i]*right[i];
        }
        return sum;
    }
};

/* Compute the outer product: */
template<class LeftT, class RightT>
struct outer_impl
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename left_traits::value_type left_value;
    typedef typename right_traits::value_type right_value;

    /* The matrix return type: */
    typedef typename et::MatrixPromote<
        left_result,right_result>::temporary_type result_type;

    result_type operator()(const LeftT& left, const RightT& right) const
    {
        /* Create a matrix with the right size (resize() is a no-op for
         * fixed-size matrices):
         */
        result_type C;
        cml::et::detail::Resize(C, left.rows(), right.cols());

        /* Now, compute the outer product: */
        for(size_t i = 0; i < left.rows(); ++i) {
            for(size_t j = 0; j < right.cols(); ++j) {
                C(i,j) = left[i]*right[j];
                /* Note: both arguments are vectors, so array notation
                 * is okay here.
                 */
            }
        }
        return C;
    }
};

/** Wrap up the dot and outer implementations.
 *
 * This allows the proper implementation to be selected based upon the
 * orientation of the arguments.
 */
template<class LeftT, class RightT>
struct VectorProduct
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename left_traits::value_type left_value;
    typedef typename right_traits::value_type right_value;

#if !defined(CML_IGNORE_VECTOR_ORIENTATION)
    /* This is specialized based upon orientation: */
    template<class O1, class O2, typename X=void> struct impl;

    /* Inner product as a specialization of impl: */
    template<typename X> struct impl<row_vector,col_vector,X> {
        typedef typename dot_impl<LeftT,RightT>::result_type result_type;
        result_type operator()(const LeftT& left, const RightT& right) const
        {
            return dot_impl<LeftT,RightT>()(left,right);
        }
    };

    /* Outer product as a specialization of impl: */
    template<typename X> struct impl<col_vector,row_vector,X> {
        typedef typename outer_impl<LeftT,RightT>::result_type result_type;
        result_type operator()(const LeftT& left, const RightT& right) const
        {
            return outer_impl<LeftT,RightT>()(left,right);
        }
    };

    /* Can use type deduction when orientation is enforced: */
    typedef impl<
        typename left_result::orient_tag,
        typename right_result::orient_tag> product;

    typedef typename product::result_type result_type;
#endif
};

} // namespace detail


/* Define the orientation-independent dot() and outer() functions: */
template<
    typename E1, class AT1, typename O1,
    typename E2, class AT2, typename O2>
typename detail::dot_impl<
    vector<E1,AT1,O1>, vector<E2,AT2,O2>
>::result_type
dot(const vector<E1,AT1,O1>& left,
    const vector<E2,AT2,O2>& right)
{
    typedef typename detail::dot_impl<
        vector<E1,AT1,O1>, vector<E2,AT2,O2>
    > product;
    return product()(left,right);
}

template<typename E, class AT, typename O, typename XprT>
typename detail::dot_impl<
    vector<E,AT,O>, typename XprT::result_type
>::result_type
dot(const vector<E,AT,O>& left,
    const et::VectorXpr<XprT>& right)
{
    typedef typename detail::dot_impl<
        vector<E,AT,O>, typename XprT::result_type
    > product;
    return product()(left,right);
}

template<typename XprT, typename E, class AT, typename O>
typename detail::dot_impl<
    typename XprT::result_type,
    vector<E,AT,O>
>::result_type
dot(const et::VectorXpr<XprT>& left,
    const vector<E,AT,O>& right)
{
    typedef typename detail::dot_impl<
        typename XprT::result_type, vector<E,AT,O>
    > product;
    return product()(left,right);
}

template<typename XprT1, typename XprT2>
typename detail::dot_impl<
    typename XprT1::result_type,
    typename XprT2::result_type
>::result_type
dot(const et::VectorXpr<XprT1>& left,
    const et::VectorXpr<XprT2>& right)
{
    typedef typename detail::dot_impl<
        typename XprT1::result_type,
        typename XprT2::result_type
    > product;
    return product()(left,right);
}

template<
    typename E1, class AT1, typename O1,
    typename E2, class AT2, typename O2>
typename detail::outer_impl<
    vector<E1,AT1,O1>, vector<E2,AT2,O2>
>::result_type
outer(const vector<E1,AT1,O1>& left,
    const vector<E2,AT2,O2>& right)
{
    typedef typename detail::outer_impl<
        vector<E1,AT1,O1>, vector<E2,AT2,O2>
    > product;
    return product()(left,right);
}

template<typename E, class AT, typename O, typename XprT>
typename detail::outer_impl<
    vector<E,AT,O>, typename XprT::result_type
>::result_type
outer(const vector<E,AT,O>& left,
          const et::VectorXpr<XprT>& right)
{
    typedef typename detail::outer_impl<
        vector<E,AT,O>, typename XprT::result_type
    > product;
    return product()(left,right);
}

template<typename XprT, typename E, class AT, typename O>
typename detail::outer_impl<
    typename XprT::result_type,
    vector<E,AT,O>
>::result_type
outer(const et::VectorXpr<XprT>& left,
      const vector<E,AT,O>& right)
{
    typedef typename detail::outer_impl<
        typename XprT::result_type, vector<E,AT,O>
    > product;
    return product()(left,right);
}

template<typename XprT1, typename XprT2>
typename detail::outer_impl<
    typename XprT1::result_type,
    typename XprT2::result_type
>::result_type
outer(const et::VectorXpr<XprT1>& left,
    const et::VectorXpr<XprT2>& right)
{
    typedef typename detail::outer_impl<
        typename XprT1::result_type,
        typename XprT2::result_type
    > product;
    return product()(left,right);
}


#if !defined(CML_IGNORE_VECTOR_ORIENTATION)

/** Operator* for two vectors.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<
    typename E1, class AT1, typename O1,
    typename E2, class AT2, typename O2>
typename detail::VectorProduct<
    vector<E1,AT1,O1>, vector<E2,AT2,O2>
>::result_type
operator*(const vector<E1,AT1,O1>& left,
          const vector<E2,AT2,O2>& right)
{
    typedef typename detail::VectorProduct<
        vector<E1,AT1,O1>, vector<E2,AT2,O2>
    >::product product;
    return product()(left,right);
}

/** Dispatch for a vector and a VectorXpr.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<typename E, class AT, typename O, typename XprT>
typename detail::VectorProduct<
    vector<E,AT,O>, typename XprT::result_type
>::product::result_type
operator*(const vector<E,AT,O>& left,
          const et::VectorXpr<XprT>& right)
{
    typedef typename detail::VectorProduct<
        vector<E,AT,O>, typename XprT::result_type
    >::product product;
    return product()(left,right);
}

/** Dispatch for a VectorXpr and a vector.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<typename XprT, typename E, class AT, typename O>
typename detail::VectorProduct<
    typename XprT::result_type,
    vector<E,AT,O>
>::product::result_type
operator*(const et::VectorXpr<XprT>& left,
          const vector<E,AT,O>& right)
{
    typedef typename detail::VectorProduct<
        typename XprT::result_type, vector<E,AT,O>
    >::product product;
    return product()(left,right);
}

/** Dispatch for two VectorXpr's.
 *
 * If CML_IGNORE_VECTOR_ORIENTATION is defined, the orientation of the
 * arguments is ignored.  Otherwise, left must be a row_vector, and right
 * must be a col_vector.
 */
template<typename XprT1, typename XprT2>
typename detail::VectorProduct<
    typename XprT1::result_type,
    typename XprT2::result_type
>::product::result_type
operator*(const et::VectorXpr<XprT1>& left,
          const et::VectorXpr<XprT2>& right)
{
    typedef typename detail::VectorProduct<
        typename XprT1::result_type,
        typename XprT2::result_type
    >::product product;
    return product()(left,right);
}

#endif

} // namespace vector_ops
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

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
