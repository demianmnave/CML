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

namespace cml {
namespace et {


/** A class for verifying the argument sizes of a BinaryVectorOp.
 *
 * Making this a class provides a common interface for checking the argument
 * sizes of binary vector expressions at compile-time and run-time.
 */
template<typename LeftT, typename RightT, typename ResultTag>
struct CheckLinearExprSizes
{
    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Record argument types: */
    typedef typename left_traits::expr_type left_t;
    typedef typename right_traits::expr_type right_t;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /** Implementation of the size checker. */
    template<typename L, typename R, typename RT, class X = void> struct impl;

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename L, class X> struct impl<L,unit_size_tag,ResultTag,X> {
        bool operator()(const left_t&, const right_t&) const {
            return true;
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename R, class X> struct impl<unit_size_tag,R,ResultTag,X> {
        bool operator()(const left_t&, const right_t&) const {
            return true;
        }
    };

    /** Compile-time check for fixed-size vectors. */
    template<class X>
    struct impl<fixed_size_tag,fixed_size_tag,vector_result_tag,X> {

        /** Statically compare the vector sizes. */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        bool operator()(const left_t&, const right_t&) const {
            return true;
        }
    };

    /** Compile-time check for fixed-size matrices. */
    template<class X>
    struct impl<fixed_size_tag,fixed_size_tag,matrix_result_tag,X> {

        /** Statically compare the vector sizes. */
        CML_STATIC_REQUIRE(
                (((long)left_t::array_rows == (long)right_t::array_rows)
                && ((long)left_t::array_cols == (long)right_t::array_cols)) );

        bool operator()(const left_t&, const right_t&) const {
            return true;
        }
    };

    /** Run-time check for any other vector combination. */
    template<typename L, typename R, class X>
    struct impl<L,R,vector_result_tag,X> {
        bool operator()(const left_t& left, const right_t& right) const {
            return left_traits().size(left) == right_traits().size(right);
        }
    };

    /** Run-time check for any other matrix combination. */
    template<typename L, typename R, class X>
    struct impl<L,R,matrix_result_tag,X> {
        bool operator()(const left_t& left, const right_t& right) const {
            return (left_traits().rows(left) == right_traits().rows(right))
                && (left_traits().cols(left) == right_traits().cols(right));
        }
    };


    /* Type of size checker to use: */
    typedef impl<left_size_tag,right_size_tag,ResultTag> check_size;

    /** Dispatch to the proper run-time implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    bool operator()(const left_t& left, const right_t& right) const {
        if(!check_size()(left, right)) {
            throw std::invalid_argument(
                    "expressions have incompatible sizes.");
        }
        return true;
    }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
