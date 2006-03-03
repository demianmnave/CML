/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Define matrix and vector linear expression size-checking classes.
 *
 * @todo Allow the size-checking code to be turned off.
 *
 * @internal This isn't the most elegant solution...
 */

#ifndef size_checking_h
#define size_checking_h

#include <stdexcept>
#include <cml/core/cml_assert.h>
#include <cml/et/tags.h>
#include <cml/et/traits.h>

/* This is used below to create a more meaningful compile-time error when
 * fixed-size vector arguments don't match at compile time:
 */
struct mismatched_fixed_vector_size_error;

/* This is used below to create a more meaningful compile-time error when
 * fixed-size matrix arguments don't match at compile time:
 */
struct mismatched_fixed_matrix_size_error;


namespace cml {
namespace et {

/* Forward declare for specialization below: */
template<typename LeftT, typename RightT, typename ResultTag>
    struct GetCheckedSize;

/** A struct to check and return the size of vector expressions.
 *
 * This struct defines functions to check and return the resulting size of a
 * vector binary expression.  Use the generator CheckedSize() to simplify
 * access to this struct.
 *
 * @sa CheckedSize
 */
template<typename LeftT, typename RightT>
struct GetCheckedSize<LeftT,RightT,vector_result_tag>
{
    /* The type returned from the functions below: */
    typedef size_t size_type;

    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /* Define a fixed-size checker: */
    template<typename LTag = left_size_tag, typename RTag = right_size_tag,
        typename X = void> struct fixed_check {};

    /* This just does a compile-time size check for fixed-size vectors: */
    template<typename X> struct fixed_check<fixed_size_tag,fixed_size_tag,X> {
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_size == (size_t)RightT::array_size,
                mismatched_fixed_vector_size_error);
        enum { array_size = LeftT::array_size };
    };


  protected:

    /* This is called only when one argument is a dynamic vector: */
    size_t equal_or_fail(size_t left, size_t right) const {
        if(left != right)
            throw std::invalid_argument(
                "expressions have incompatible sizes.");
        return left;
    }

    /* vector/scalar expression size: */
    template<typename LTag> size_t checked_size(
            const LeftT& left, const RightT&, LTag, unit_size_tag
            ) const
    {
        return left_traits().size(left);
    }

    /* scalar/vector expression size: */
    template<typename RTag> size_t checked_size(
            const LeftT&, const RightT& right, unit_size_tag, RTag
            ) const
    {
        return right_traits().size(right);
    }

    /* fixed vector expression size: */
    size_t checked_size(
            const LeftT&, const RightT&,
            fixed_size_tag, fixed_size_tag
            ) const
    {
        fixed_check<fixed_size_tag,fixed_size_tag>();
        return (size_t)LeftT::array_size;
    }

    /* Size of vector expression having a dynamic vector: */
    template<typename LTag, typename RTag>
    size_t checked_size(
            const LeftT& left, const RightT& right, LTag, RTag
            ) const
    {
        return equal_or_fail(
                left_traits().size(left),
                right_traits().size(right));
    }



  public:

    /* Define a fixed-size, compile-time checker: */
    typedef fixed_check<left_size_tag,right_size_tag> compile_time_check;

    /** Dispatch to the proper run-time implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    size_t operator()(const LeftT& left, const RightT& right) const {
        return checked_size(left, right, left_size_tag(), right_size_tag());
    }
};


/** A struct to check and return the size of matrix expressions.
 *
 * This struct defines functions to check and return the resulting size of a
 * (linear) matrix binary expression.  Use the generator CheckedSize() to
 * simplify access to this struct.
 *
 * @sa CheckedSize
 */
template<typename LeftT, typename RightT>
struct GetCheckedSize<LeftT,RightT,matrix_result_tag>
{
    /* The type returned from the functions below: */
    typedef matrix_size size_type;

    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /* Define a fixed-size checker: */
    template<typename LTag = left_size_tag, typename RTag = right_size_tag,
        typename X = void> struct fixed_check {};

    /* This just does a compile-time size check for fixed-size vectors: */
    template<typename X> struct fixed_check<fixed_size_tag,fixed_size_tag,X> {
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_rows == (size_t)RightT::array_rows
                && (size_t)LeftT::array_cols == (size_t)RightT::array_cols,
                mismatched_fixed_matrix_size_error);
    };


  protected:

    /* This is called only when one argument is a dynamic matrix: */
    matrix_size equal_or_fail(const LeftT& left, const RightT& right) const {
        size_t left_rows = left_traits().rows(left);
        size_t right_cols = right_traits().cols(right);
        if(left_rows != right_traits().rows(right)
                || right_cols != left_traits().cols(left))
            throw std::invalid_argument(
                "expressions have incompatible sizes.");
        return matrix_size(left_rows,right_cols);
    }

    /* matrix/scalar expression size: */
    template<typename LTag> matrix_size checked_size(
            const LeftT& left, const RightT&, LTag, unit_size_tag
            ) const
    {
        return matrix_size(
                left_traits().rows(left),
                left_traits().cols(left));
    }

    /* scalar/vector expression size: */
    template<typename RTag> matrix_size checked_size(
            const LeftT&, const RightT& right, unit_size_tag, RTag
            ) const
    {
        return matrix_size(
                right_traits().rows(right),
                right_traits().cols(right));
    }

    /* fixed vector expression size: */
    matrix_size checked_size(
            const LeftT&, const RightT&,
            fixed_size_tag, fixed_size_tag
            ) const
    {
        fixed_check<fixed_size_tag,fixed_size_tag>();
        return matrix_size(LeftT::array_rows,RightT::array_cols);
    }

    /* Size of vector expression having a dynamic vector: */
    template<typename LTag, typename RTag>
    matrix_size checked_size(
            const LeftT& left, const RightT& right, LTag, RTag
            ) const
    {
        return equal_or_fail(left,right);
    }



  public:

    /* Define a fixed-size, compile-time checker: */
    typedef fixed_check<left_size_tag,right_size_tag> compile_time_check;

    /** Dispatch to the proper run-time implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    matrix_size operator()(const LeftT& left, const RightT& right) const {
        return checked_size(left, right, left_size_tag(), right_size_tag());
    }
};

} // namespace et

/** Generator for GetCheckedSize. */
template<typename LeftT, typename RightT, typename ResultTag>
typename et::GetCheckedSize<LeftT,RightT,ResultTag>::size_type
CheckedSize(
        const LeftT& left, const RightT& right, ResultTag)
{
    return et::GetCheckedSize<LeftT,RightT,ResultTag>()(left,right);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
