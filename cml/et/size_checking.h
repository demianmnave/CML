/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Define matrix and vector linear expression size-checking classes.
 */

#ifndef size_checking_h
#define size_checking_h

#include <stdexcept>
#include <cml/core/cml_meta.h>
#include <cml/core/fwd.h>
#include <cml/et/tags.h>
#include <cml/et/traits.h>

/* This is used below to create a more meaningful compile-time error when
 * fixed-size vector arguments don't match at compile time:
 */
struct incompatible_expression_size_error;

namespace cml {
namespace et {

/* Forward declare for specialization below: */
template<typename LeftT, typename RightT, typename SizeT>
    struct GetCheckedSize;

/* Checking for fixed-size expression: */
template<typename LeftT, typename RightT>
struct GetCheckedSize<LeftT,RightT,fixed_size_tag>
{
    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Result types: */
    typedef typename left_traits::result_tag left_result;
    typedef typename right_traits::result_tag right_result;


    /* For specialization below: */
    template<typename LR, typename RR, class X = void> struct impl;

    /* Check for two matrices: */
    template<class X> struct impl<matrix_result_tag,matrix_result_tag,X> {
        typedef matrix_size size_type;
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_rows == (size_t)RightT::array_rows
                && (size_t)LeftT::array_cols == (size_t)RightT::array_cols,
                incompatible_expression_size_error);

        /* Record the array size as a constant: */
        enum {
            array_rows = LeftT::array_rows,
            array_cols = LeftT::array_cols
        };

        /* Return the matrix size: */
        size_type size() const { return size_type(array_rows,array_cols); }
    };

    /* Check for a matrix and a vector: */
    template<class X> struct impl<matrix_result_tag,vector_result_tag,X> {
        typedef size_t size_type;
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_cols == (size_t)RightT::array_size,
                incompatible_expression_size_error);

        /* Record the array size as a constant: */
        enum { array_size = RightT::array_size };

        /* Return the vector size: */
        size_type size() const { return size_type(array_size); }
    };

    /* Check for a vector and a matrix: */
    template<class X> struct impl<vector_result_tag,matrix_result_tag,X> {
        typedef size_t size_type;
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_size == (size_t)RightT::array_rows,
                incompatible_expression_size_error);

        /* Record the array size as a constant: */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size() const { return size_type(array_size); }
    };

    /* Check for a matrix and a scalar: */
    template<class X> struct impl<matrix_result_tag,scalar_result_tag,X> {
        typedef matrix_size size_type;

        /* Record the array size as a constant: */
        enum {
            array_rows = LeftT::array_rows,
            array_cols = LeftT::array_cols
        };

        /* Return the matrix size: */
        size_type size() const { return size_type(array_rows,array_cols); }
    };

    /* Check for a scalar and a matrix: */
    template<class X> struct impl<scalar_result_tag,matrix_result_tag,X> {
        typedef matrix_size size_type;

        /* Record the array size as a constant: */
        enum {
            array_rows = RightT::array_rows,
            array_cols = RightT::array_cols
        };

        /* Return the matrix size: */
        size_type size() const { return size_type(array_rows,array_cols); }
    };

    /* Check for two vectors: */
    template<class X> struct impl<vector_result_tag,vector_result_tag,X> {
        typedef size_t size_type;
        CML_STATIC_REQUIRE_M(
                (size_t)LeftT::array_size == (size_t)RightT::array_size,
                incompatible_expression_size_error);

        /* Record the array size as a constant: */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size() const { return size_type(array_size); }
    };

    /* Check for a vector and a scalar: */
    template<class X> struct impl<vector_result_tag,scalar_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant: */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size() const { return size_type(array_size); }
    };

    /* Check for a scalar and a vector: */
    template<class X> struct impl<scalar_result_tag,vector_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant: */
        enum { array_size = RightT::array_size };

        /* Return the vector size: */
        size_type size() const { return size_type(array_size); }
    };

    /* Record the type of the checker: */
    typedef impl<left_result,right_result> check_type;
    typedef typename check_type::size_type size_type;

    /* The implementation: */
    size_type operator()(const LeftT&, const RightT&) const {
        return check_type().size();
    }
};

/* Checking for resizeable expression: */
template<typename LeftT, typename RightT>
struct GetCheckedSize<LeftT,RightT,dynamic_size_tag>
{
    /* Type of the size checker (for calling equal_or_fail): */
    typedef GetCheckedSize<LeftT,RightT,dynamic_size_tag> self;

    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Result types: */
    typedef typename left_traits::result_tag left_result;
    typedef typename right_traits::result_tag right_result;


    /* For specialization below: */
    template<typename LR, typename RR, class X = void> struct impl;

    /* Return the size if the same, or fail if different: */
#if defined(CML_CHECK_VECTOR_EXPR_SIZES)
    template<typename V> V equal_or_fail(V left, V right) const {
        if(left != right)
            throw std::invalid_argument(
                    "expressions have incompatible sizes.");
        return left;
    }
#else
    template<typename V> V equal_or_fail(V left, V) const {
        return left;
    }
#endif

    /* Check for two matrices: */
    template<class X> struct impl<matrix_result_tag,matrix_result_tag,X> {
        typedef matrix_size size_type;

        /* Record the array size as a constant: */
        enum {
            array_rows = LeftT::array_rows,
            array_cols = LeftT::array_cols
        };

        /* Return the matrix size, or fail if incompatible: */
        size_type size(const LeftT& left, const RightT& right) const {
            return self().equal_or_fail(
                    left_traits().size(left), right_traits().size(right));
        }
    };

    /* Check for a matrix and a vector: */
    template<class X> struct impl<matrix_result_tag,vector_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant (it will be -1): */
        enum { array_size = RightT::array_size };

        /* Return the vector size: */
        size_type size(const LeftT& left, const RightT& right) const {
            return self().equal_or_fail(
                    left_traits().cols(left), right_traits().size(right));
        }
    };

    /* Check for a vector and a matrix: */
    template<class X> struct impl<vector_result_tag,matrix_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant (it will be -1): */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size(const LeftT& left, const RightT& right) const {
            return self().equal_or_fail(
                    left_traits().size(left), right_traits().rows(right));
        }
    };

    /* Check for a matrix and a scalar: */
    template<class X> struct impl<matrix_result_tag,scalar_result_tag,X> {
        typedef matrix_size size_type;

        /* Record the array size as a constant: */
        enum {
            array_rows = LeftT::array_rows,
            array_cols = LeftT::array_cols
        };

        /* Return the matrix size: */
        size_type size(const LeftT& left, const RightT&) const {
            return left_traits().size(left);
        }
    };

    /* Check for a scalar and a matrix: */
    template<class X> struct impl<scalar_result_tag,matrix_result_tag,X> {
        typedef matrix_size size_type;

        /* Record the array size as a constant: */
        enum {
            array_rows = RightT::array_rows,
            array_cols = RightT::array_cols
        };

        /* Return the matrix size: */
        size_type size(const LeftT&, const RightT& right) const {
            return right_traits().size(right);
        }
    };

    /* Check for two vectors: */
    template<class X> struct impl<vector_result_tag,vector_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant (it will be -1): */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size(const LeftT& left, const RightT& right) const {
            return self().equal_or_fail(
                    left_traits().size(left), right_traits().size(right));
        }
    };

    /* Check for a vector and a scalar: */
    template<class X> struct impl<vector_result_tag,scalar_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant (it will be -1): */
        enum { array_size = LeftT::array_size };

        /* Return the vector size: */
        size_type size(const LeftT& left, const RightT&) const {
            return left_traits().size(left);
        }
    };

    /* Check for a scalar and a vector: */
    template<class X> struct impl<scalar_result_tag,vector_result_tag,X> {
        typedef size_t size_type;

        /* Record the array size as a constant (it will be -1): */
        enum { array_size = RightT::array_size };

        /* Return the vector size: */
        size_type size(const LeftT&, const RightT& right) const {
            return right_traits().size(right);
        }
    };

    /* Record the type of the checker: */
    typedef impl<left_result,right_result> check_type;
    typedef typename check_type::size_type size_type;

    /* The implementation: */
    size_type operator()(const LeftT& left, const RightT& right) const {
        return check_type().size(left,right);
    }
};

} // namespace et

/** Generator for GetCheckedSize. */
template<typename LeftT, typename RightT, typename SizeTag>
typename et::GetCheckedSize<LeftT,RightT,SizeTag>::size_type
CheckedSize(
        const LeftT& left, const RightT& right, SizeTag)
{
    return et::GetCheckedSize<LeftT,RightT,SizeTag>()(left,right);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
