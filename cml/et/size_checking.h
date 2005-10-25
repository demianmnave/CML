/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Define matrix and vector size-related classes.
 *
 * @todo Allow the size-checking code to be turned off.
 *
 * @internal This isn't the most elegant solution...
 */

#if !defined(cml_vector_h) && !defined(cml_matrix_h)
#error "This should only be included from cml/vector.h or cml/matrix.h"
#else

#ifndef size_checking_h
#define size_checking_h

#include <cml/core/cml_assert.h>
#include <cml/et/traits.h>

namespace cml {
namespace et {


/** A class for verifying the argument sizes of a BinaryVectorOp.
 *
 * Making this a class provides a common interface for checking the argument
 * sizes of binary vector expressions at compile-time and run-time.
 */
template<typename LeftT, typename RightT>
struct CheckVectorSizes
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

    /** Implementation of the size checker.
     *
     * This is specialized on size types of the arguments.  The default is
     * to use a run-time check, since only two fixed-size vectors can be
     * compared at compile time.
     */
    template<typename LTag, typename RTag, class Dummy = void> struct impl {
        bool operator()(const left_t& left, const right_t& right) const {
            return (left.size() == right.size());
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename R, class D> struct impl<unit_size_tag,R,D> {
        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename L, class D> struct impl<L,unit_size_tag,D> {
        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for fixed-size vectors. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /** Statically compare the vector sizes. */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };


    /* Type of size checker to use: */
    typedef impl<left_size_tag,right_size_tag> check;

    /** Dispatch to the proper implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    bool operator()(const left_t& left, const right_t& right) const {
        if(!check()(left, right)) {
            throw std::invalid_argument("vectors have incompatible sizes.");
        }
        return true;
    }
};


/** Figure out a BinaryVectorOp's result size and size type. */
template<typename LeftT, typename RightT>
struct DeduceVectorResultSize
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

    /* A checker to verify the argument sizes at compile- or run-time: */
    typedef CheckVectorSizes<LeftT,RightT> check_size;


    /** This is specialized for each combination. */
    template<typename LTag, typename RTag, class Dummy = void> struct impl;

    /** Two dynamic-size vectors result in a dynamic-size vector. */
    template<class D> struct impl<dynamic_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t& left, const right_t& right) const {
            if(!check_size()(left,right)) return 0;
            return left.size();
        }
    };

    /** Two fixed-size vectors result in a fixed-size vector. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /* Require that the vectors have the same size: */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
        size_t operator()(const left_t& left, const right_t&) const {
            return size_t(result);
        }
    };

    /** Two unit types result in a unit type. */
    template<class D> struct impl<unit_size_tag,unit_size_tag,D> {
        typedef unit_size_tag tag;
        enum { result = 1 };
        size_t operator()(const left_t&, const right_t&) const {
            return 1;
        }
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename R, class D> struct impl<fixed_size_tag,R,D> {
        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
        size_t operator()(const left_t&, const right_t&) const {
            return size_t(result);
        }
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename L, class D> struct impl<L,fixed_size_tag,D> {
        typedef fixed_size_tag tag;
        enum { result = right_t::array_size };
        size_t operator()(const left_t&, const right_t&) const {
            return size_t(result);
        }
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<unit_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t&, const right_t& right) const {
            return right.size();
        }
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<dynamic_size_tag,unit_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t& left, const right_t&) const {
            return left.size();
        }
    };


    /* Deduce the size tag and result size: */
    typedef impl<left_size_tag,right_size_tag> deduce;

    /* The resulting tag type: */
    typedef typename deduce::tag tag;

    /* The result size: */
    enum { result = deduce::result };

    /* A function returning the result size at run-time: */
    size_t operator()(const left_t& left, const right_t& right) const {
        return deduce()(left,right);
    }
};




#if 0
/** A class for verifying the argument sizes of a BinaryVectorOp.
 *
 * Making this a class provides a common interface for checking the argument
 * sizes of binary vector expressions at compile-time and run-time.
 */
template<typename XprT>
struct CheckVectorSizes
{
    /* Record argument traits: */
    typedef typename XprT::left_traits left_traits;
    typedef typename XprT::right_traits right_traits;

    /* Record argument types: */
    typedef typename left_traits::expr_type left_t;
    typedef typename right_traits::expr_type right_t;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /** Implementation of the size checker.
     *
     * This is specialized on size types of the arguments.  The default is
     * to use a run-time check, since only two fixed-size vectors can be
     * compared at compile time.
     */
    template<typename LTag, typename RTag, class Dummy = void> struct impl {
        bool operator()(const left_t& left, const right_t& right) const {
            return (left.size() == right.size());
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename R, class D> struct impl<unit_size_tag,R,D> {
        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename L, class D> struct impl<L,unit_size_tag,D> {
        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for fixed-size vectors. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /** Statically compare the vector sizes. */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        bool operator()(const left_t& left, const right_t& right) const {
            return true;
        }
    };


    /* Type of size checker to use: */
    typedef impl<left_size_tag,right_size_tag> check;

    /** Dispatch to the proper implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    bool operator()(const left_t& left, const right_t& right) const {
        if(!check()(left, right)) {
            throw std::invalid_argument("vectors have incompatible sizes.");
        }
    }
};

/** Figure out a BinaryVectorOp's result size and size type. */
template<typename XprT>
struct DeduceVectorResultSize
{
    /* Record argument traits: */
    typedef typename XprT::left_traits left_traits;
    typedef typename XprT::right_traits right_traits;

    /* Record argument types: */
    typedef typename left_traits::expr_type left_t;
    typedef typename right_traits::expr_type right_t;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /* A checker to verify the argument sizes at compile- or run-time: */
    typedef CheckVectorSizes<XprT> check_size;


    /** This is specialized for each combination. */
    template<typename LTag, typename RTag, class Dummy = void> struct impl;

    /** Two dynamic-size vectors result in a dynamic-size vector. */
    template<class D> struct impl<dynamic_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t& left, const right_t& right) const {
            if(!check_size()(left,right)) return 0;
            return left.size();
        }
    };

    /** Two fixed-size vectors result in a fixed-size vector. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /* Require that the vectors have the same size: */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
        size_t operator()(const left_t& left, const right_t&) const {
            return size_t(result);
        }
    };

    /** Two unit types result in a unit type. */
    template<class D> struct impl<unit_size_tag,unit_size_tag,D> {
        typedef unit_size_tag tag;
        enum { result = 1 };
        size_t operator()(const left_t&, const right_t&) const {
            return 1;
        }
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename R, class D> struct impl<fixed_size_tag,R,D> {
        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
        size_t operator()(const left_t&, const right_t&) const {
            return size_t(result);
        }
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename L, class D> struct impl<L,fixed_size_tag,D> {
        typedef fixed_size_tag tag;
        enum { result = right_t::array_size };
        size_t operator()(const left_t&, const right_t&) const {
            return size_t(result);
        }
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<unit_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t&, const right_t& right) const {
            return right.size();
        }
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<dynamic_size_tag,unit_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
        size_t operator()(const left_t& left, const right_t&) const {
            return left.size();
        }
    };


    /* Deduce the size tag and result size: */
    typedef impl<left_size_tag,right_size_tag> deduce;

    /* The resulting tag type: */
    typedef typename deduce::tag tag;

    /* The result size: */
    enum { result = deduce::result };

    /* A function returning the result size at run-time: */
    size_t operator()(const left_t& left, const right_t& right) const {
        return deduce()(left,right);
    }
};
#endif


#if 0
/** A class for verifying the argument sizes of a LinearBinaryMatrixOp.
 *
 * Making this a class provides a common interface for checking the argument
 * sizes of binary matrix expressions at compile-time and run-time.
 */
template<typename XprT>
struct CheckLinearMatrixSizes
{
    /* Record argument traits: */
    typedef typename XprT::left_traits left_traits;
    typedef typename XprT::right_traits right_traits;

    /* Record argument types: */
    typedef typename left_traits::expr_type left_t;
    typedef typename right_traits::expr_type right_t;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;

    /** Implementation of the size checker.
     *
     * This is specialized on size types of the arguments.  The default is
     * to use a run-time check, since only two fixed-size matrices can be
     * compared at compile time.
     */
    template<typename LTag, typename RTag, class Dummy = void> struct impl {
        bool check_sizes(const left_t& left, const right_t& right) const {
            return (left.rows() == right.rows() && left.cols() == right.cols());
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename R, class D> struct impl<unit_size_tag,R,D> {
        bool check_sizes(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for unit-size scalars with anything else. */
    template<typename L, class D> struct impl<L,unit_size_tag,D> {
        bool check_sizes(const left_t& left, const right_t& right) const {
            return true;
        }
    };

    /** Compile-time check for fixed-size matrices. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /** Statically compare the vector sizes. */
        CML_STATIC_REQUIRE(
                ((long)left_t::array_rows == (long)right_t::array_rows)
                && ((long)left_t::array_cols == (long)right_t::array_cols)
                );

        bool check_sizes(const left_t& left, const right_t& right) const {
            return true;
        }
    };


    /* Type of size checker to use: */
    typedef impl<left_size_tag,right_size_tag> size_checker;

    /** Dispatch to the proper implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    bool operator()(const left_t& left, const right_t& right) const {
        if(!size_checker().check_sizes(left, right)) {
            throw std::invalid_argument("matrices have incompatible sizes.");
        }
    }
};

/** Figure out a BinaryVectorOp's result size and size type. */
template<typename XprT>
struct DeduceMatrixResultSize
{
    /* Record argument traits: */
    typedef typename XprT::left_traits left_traits;
    typedef typename XprT::right_traits right_traits;

    /* Record argument types: */
    typedef typename left_traits::expr_type left_t;
    typedef typename right_traits::expr_type right_t;

    /* Record argument size tags: */
    typedef typename left_traits::size_tag left_size_tag;
    typedef typename right_traits::size_tag right_size_tag;


    /** This is specialized for each combination. */
    template<typename LTag, typename RTag, class Dummy = void> struct impl;

    /** Two dynamic-size vectors result in a dynamic-size vector. */
    template<class D> struct impl<dynamic_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
    };

    /** Two fixed-size vectors result in a fixed-size vector. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /* Require that the vectors have the same size: */
        CML_STATIC_REQUIRE(
                (long)left_t::array_size == (long)right_t::array_size);

        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
    };

    /** Two unit types result in a unit type. */
    template<class D> struct impl<unit_size_tag,unit_size_tag,D> {
        typedef unit_size_tag tag;
        enum { result = 1 };
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename R, class D> struct impl<fixed_size_tag,R,D> {
        typedef fixed_size_tag tag;
        enum { result = left_t::array_size };
    };

    /** Anything with a fixed-size vector produces a fixed-size vector: */
    template<typename L, class D> struct impl<L,fixed_size_tag,D> {
        typedef fixed_size_tag tag;
        enum { result = right_t::array_size };
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<unit_size_tag,dynamic_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
    };

    /** A unit type and a dynamic vector result in a dynamic vector. */
    template<class D> struct impl<dynamic_size_tag,unit_size_tag,D> {
        typedef dynamic_size_tag tag;
        enum { result = -1 };
    };


    /* Deduce the size tag and result size: */
    typedef impl<left_size_tag,right_size_tag> deduce;

    /* The resulting tag type: */
    typedef typename deduce::tag tag;

    /* The result size: */
    enum {
        result_rows = deduce::result_rows,
        result_cols = deduce::result_cols
    };
};




/** A class for comparing the sizes of two matrices.
 *
 * Making this a class provides a common interface for checking the sizes
 * of matrices in an expression at compile-time and run-time.
 *
 * @internal This class enforces at compile time the condition that the two
 * arguments are not different size types.
 */
template<typename LeftT, typename RightT, bool ForLinearOp>
struct MatrixSizeChecker
{
    /* Statically compare the matrix sizes.  For dynamically-sized matrices,
     * this is always true (rows and cols are both -1):
     */
    CML_STATIC_REQUIRE(
            (ForLinearOp)

            /* Need exact matrix sizes for a linear op: */
            ? ( ((long) LeftT::array_rows == (long)RightT::array_rows)
                && ((long) LeftT::array_cols == (long)RightT::array_cols) )

            /* Need same rows in LeftT as cols in RightT otherwise: */
            : ((long) LeftT::array_rows == (long)RightT::array_cols)
            );

    /* Check sizes at run-time.  For fixed-size vectors, this will be
     * optimized away if they have the same size.
     */
    void operator()(const LeftT& left, const RightT& right) const {
        return (ForLinearOp)

            /* Need exact matrix sizes for a linear op: */
            ? (left.rows() == right.rows() && left.cols() == right.cols())

            /* Need same rows in LeftT as cols in RightT otherwise: */
            : (left.rows() == right.cols());
    };
};
#endif

} // namespace et
} // namespace cml

#endif

#endif // !defined(cml_vector_h) && !defined(cml_matrix_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
