/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines vector unrollers.
 *
 * @todo Add unrolling for dynamic vectors, and for vectors longer than
 * CML_VECTOR_UNROLL_LIMIT.
 */

#ifndef vector_unroller_h
#define vector_unroller_h

#include <cml/et/traits.h>
#include <cml/et/size_checking.h>
#include <cml/et/scalar_promotions.h>

#if !defined(CML_VECTOR_UNROLL_LIMIT)
#error "CML_VECTOR_UNROLL_LIMIT is undefined."
#endif

namespace cml {

/* Forward declare for the vector expressions below: */
template<typename E, class AT, class O> class vector;

namespace et {

/** Detail for the vector unroller code. */
namespace detail {

/** Unroll a binary assignment operator on a fixed-size vector.
 *
 * This uses forward iteration to make efficient use of the cache.
 *
 * @sa cml::vector
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 */
template<class OpT, typename E, class AT, class O, class SrcT>
struct VectorAssignmentUnroller
{
    /* Forward declare: */
    template<int N, int Last, bool can_unroll> struct Eval;

    /* The vector type being assigned to: */
    typedef cml::vector<E,AT,O> vector_type;

    /* Record traits for the arguments: */
    typedef ExprTraits<vector_type> dest_traits;
    typedef ExprTraits<SrcT> src_traits;

    /* Get argument reference types: */
    typedef typename dest_traits::reference dest_reference;
    typedef typename src_traits::const_reference src_reference;

    /** Evaluate the binary operator for the first Len-1 elements. */
    template<int N, int Last> struct Eval<N,Last,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to current N: */
            OpT().apply(dest[N], src_traits().get(src,N));
            /* Note: we don't need get(), since we know dest is a vector. */

            /* Apply to N+1: */
            Eval<N+1,Last,true>()(dest, src);
        }
    };

    /** Evaluate the binary operator at element Last. */
    template<int Last> struct Eval<Last,Last,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to last element: */
            OpT().apply(dest[Last], src_traits().get(src,Last));
            /* Note: we don't need get(), since we know dest is a vector. */
        }
    };

    /** Evaluate the binary operator using a loop.
     *
     * This is used when the vector's length is longer than
     * CML_VECTOR_UNROLL_LIMIT
     */
    template<int N, int Last> struct Eval<N,Last,false> {
        void operator()(dest_reference dest, src_reference src) const {
            for(size_t i = 0; i <= Last; ++i) {
                OpT().apply(dest[i], src_traits().get(src,i));
                /* Note: we don't need get(), since we know dest is a vector. */
            }
        }
    };


    /** Unroll assignment for a fixed-sized vector. */
    void operator()(
        cml::vector<E,AT,O>& dest, const SrcT& src, cml::fixed_size_tag)
    {
        typedef cml::vector<E,AT,O> vector_type;
        enum { Len = vector_type::array_size };
        typedef typename VectorAssignmentUnroller<OpT,E,AT,O,SrcT>::template
            Eval<0, Len-1, (Len <= CML_VECTOR_UNROLL_LIMIT)> Unroller;
        /* Note: Len is the array size, so Len-1 is the last element. */

        /* Check the expression size (the returned size isn't needed): */
        CheckedSize(dest,src,vector_result_tag());
        /* Note: for two fixed-size expressions, the if-statements and
         * comparisons should be completely eliminated as dead code.  If src
         * is a dynamic-sized expression, the check will still happen.
         */

        /* Now, call the unroller: */
        Unroller()(dest,src);
    }

    /** Just use a loop for dynamic vector assignment. */
    void operator()(
            cml::vector<E,AT,O>& dest, const SrcT& src, cml::dynamic_size_tag)
    {
        /* Shorthand: */
        typedef ExprTraits<SrcT> src_traits;
        size_t N = CheckedSize(dest,src,vector_result_tag());
        for(size_t i = 0; i < N; ++i) {
            OpT().apply(dest[i], src_traits().get(src,i));
            /* Note: we don't need get(), since we know dest is a vector. */
        }
    }

};

/** Unroll a vector accumulation (reduction) operator.
 *
 * This uses forward iteration to make efficient use of the cache.
 */
template<class AccumT, class OpT, class LeftT, class RightT>
struct VectorAccumulateUnroller
{
    /* Forward declare: */
    template<int N, int Last, bool can_unroll> struct Eval;

    /* Record traits for the arguments: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Get argument reference types: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;

    /* Figure out the return type: */
    typedef typename AccumT::value_type result_type; 

    /** Evaluate for the first Len-1 elements. */
    template<int N, int Last> struct Eval<N,Last,true> {
        result_type operator()(
                left_reference left, right_reference right) const
        {

            /* Apply to last value: */
            return AccumT().apply(
                    OpT().apply(left[N], right[N]),
                    Eval<N+1,Last,true>()(left, right));
            /* Note: we don't need get(), since both arguments are required to
             * be vector expressions.
             */
        }
    };

    /** Evaluate the binary operator at element Last. */
    template<int Last> struct Eval<Last,Last,true> {
        result_type operator()(
                left_reference left, right_reference right) const
        {
            return OpT().apply(left[Last],right[Last]);
            /* Note: we don't need get(), since both arguments are required to
             * be vector expressions.
             */
        }
    };

    /** Evaluate using a loop. */
    template<int N, int Last> struct Eval<N,Last,false> {
        result_type operator()(
                left_reference left, right_reference right) const
        {
            result_type accum = OpT().apply(left[0],right[0]);
            for(size_t i = 1; i <= Last; ++i) {
                /* XXX This might not be optimized properly by some compilers,
                 * but to do anything else requires changing the requirements
                 * of a scalar operator.
                 */
                accum = AccumT().apply(accum, OpT().apply(left[i],right[i]));
                /* Note: we don't need get(), since both arguments are
                 * required to be vector expressions.
                 */
            }
        }
    };
};

}

/** Construct an assignment unroller for fixed-size arrays.
 *
 * The operator must be an assignment op (otherwise, this doesn't make any
 * sense).  Also, automatic unrolling is only performed for fixed-size
 * vectors; a loop is used for dynamic-sized vectors.
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 *
 * @todo Figure out if the source or destination size type should trigger
 * unrolling.  May need a per-compiler compile-time option for this.
 */
template<class OpT, class SrcT, typename E, class AT, class O>
void UnrollAssignment(cml::vector<E,AT,O>& dest, const SrcT& src)
{
    /* Record the destination vector type: */
    typedef cml::vector<E,AT,O> vector_type;

    /* Record the type of the unroller: */
    typedef detail::VectorAssignmentUnroller<OpT,E,AT,O,SrcT> unroller;

    /* Finally, do the unroll call: */
    //unroller()(dest, src, typename vector_type::size_tag());
    unroller()(dest, src, typename SrcT::size_tag());
}

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
