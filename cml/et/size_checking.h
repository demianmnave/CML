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
     * This is specialized on the size types of the arguments.  The default
     * is to use a run-time check, since only two fixed-size vectors can be
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
    typedef impl<left_size_tag,right_size_tag> check_size;

    /** Dispatch to the proper run-time implementation.
     *
     * @throws std::invalid_argument if arguments have different sizes.
     */
    bool operator()(const left_t& left, const right_t& right) const {
        if(!check_size()(left, right)) {
            throw std::invalid_argument("vectors have incompatible sizes.");
        }
        return true;
    }
};


/** Figure out vector expression's result size and (size) type. */
template<typename LeftT, typename RightT>
struct DeduceVectorExprSize
{
  public:

    /* Record argument traits: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

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
        size_t operator()(const left_t& left, const right_t& right) const {
            return std::max(left.size(),right.size());
        }
    };

    /** Two fixed-size vectors result in a fixed-size vector. */
    template<class D> struct impl<fixed_size_tag,fixed_size_tag,D> {

        /* Setup and return the size: */
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



  protected:

    /* Deduce the size tag and result size: */
    typedef impl<left_size_tag,right_size_tag> deduce_size;


  public:

    /* The resulting tag type: */
    typedef typename deduce_size::tag tag;

    /* The (fixed) result size (-1 for dynamic vectors): */
    enum { result = deduce_size::result };

    /** A function returning the result size at run-time. */
    size_t operator()(const left_t& left, const right_t& right) const {
        return deduce_size()(left,right);
    }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
