/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#if !defined(cml_vector_h)
#error "This should only be included from cml/vector.h"
#else

#ifndef vector_unroller_h
#define vector_unroller_h

#if !defined(CML_VECTOR_UNROLL_LIMIT)
#error "CML_VECTOR_UNROLL_LIMIT is undefined."
#endif

#include <cml/et/traits.h>

namespace cml {
namespace et {

/** Detail for the vector unroller code. */
namespace detail {

/** Unroll a binary assignment operator on a fixed-size vector.
 *
 * This uses a forward iteration to make better use of the cache.
 *
 * @sa cml::vector
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 * @bug Need to verify that the vector sizes match.
 */
template<class DestT, class SrcT, class OpT>
struct VectorAssignmentUnroller
{
    /* Forward declare: */
    template<int N, int Max, bool can_unroll> struct Eval;

    /* Record traits for the arguments: */
    typedef ExprTraits<DestT> dest_traits;
    typedef ExprTraits<SrcT> src_traits;

    /* Get argument reference types: */
    typedef typename dest_traits::reference dest_reference;
    typedef typename src_traits::const_reference src_reference;

    /** Evaluate the binary operator at element Max. */
    template<int Max> struct Eval<Max,Max,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to last element: */
            OpT().apply(dest[Max], src[Max]);
        }
    };

    /** Evaluate the binary operator for the first Max-1 elements. */
    template<int N, int Max> struct Eval<N,Max,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to current N: */
            OpT().apply(dest[N], src[N]);

            /* Apply to next N: */
            Eval<N+1,Max,true>()(dest, src);
        }
    };

    /** Evaluate the binary operator using a loop. */
    template<int N, int Max> struct Eval<N,Max,false> {
        void operator()(dest_reference dest, src_reference src) const {
            for(size_t i = 0; i <= Max; ++ i) {
                OpT().apply(dest[i], src[i]);
            }
        }
    };
};

/** Unroll assignment for a fixed-sized vector. */
template<class OpT, typename E, class AT, class SrcT>
void UnrollAssignment(
    cml::vector<E,AT>& dest, const SrcT& src, cml::fixed_size_tag)
{
    typedef cml::vector<E,AT> vector_type;
    enum { Max = vector_type::array_size-1 };
    typedef typename VectorAssignmentUnroller<vector_type,SrcT,OpT>
        ::template Eval<0, Max, (Max <= CML_VECTOR_UNROLL_LIMIT)> Unroller;
    Unroller()(dest,src);
}

/** Just use a loop for dynamic vector assignment. */
template<class OpT, typename E, class AT, class SrcT>
void UnrollAssignment(
        cml::vector<E,AT>& dest, const SrcT& src, cml::dynamic_size_tag)
{
    typedef ExprTraits<SrcT> src_traits;
    for(size_t i = 0; i <= dest.size(); ++ i) {
        OpT().apply(dest[i], src[i]);
    }
}

}

/** This constructs an assignment unroller for fixed-size arrays.
 *
 * The operator must be an assignment op (otherwise, this doesn't make any
 * sense).  Also, DestT must a fixed array type.
 *
 * @sa cml::vector
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 */
template<class OpT, typename E, class AT, class SrcT>
void UnrollAssignment(cml::vector<E,AT>& dest, const SrcT& src) {
    typedef cml::vector<E,AT> vector_type;
    detail::UnrollAssignment<OpT>(dest, src, typename vector_type::size_tag());
}

} // namespace et
} // namespace cml

#endif
#endif // !defined(cml_vector_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
