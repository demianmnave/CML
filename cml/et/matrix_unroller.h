/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#if !defined(cml_matrix_h)
#error "This should only be included from cml/matrix.h"
#else

#ifndef matrix_unroller_h
#define matrix_unroller_h

#if !defined(CML_2D_UNROLLER) && !defined(CML_2D_TO_1D_UNROLLER) \
    && !defined(CML_NO_2D_UNROLLER)
#error "The matrix unroller is not defined."
#endif

#if (defined(CML_2D_UNROLLER) || defined(CML_2D_TO_1D_UNROLLER)) \
    && !defined(CML_MATRIX_UNROLL_LIMIT)
#error "CML_MATRIX_UNROLL_LIMIT is undefined."
#endif


#include <cml/et/traits.h>

namespace cml {
namespace et {

/** Detail for the matrix unroller code. */
namespace detail {

/** Unroll a binary assignment operator on a fixed-size matrix.
 *
 * This uses a forward iteration to make better use of the cache.
 *
 * @sa cml::matrix
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 * @bug Need to verify that the matrix sizes match.
 * @bug The 2D unroller needs to be specified for efficient column-major
 * access.
 * @todo Implement unrollers for blocked matrix access.
 */
template<class DestT, class SrcT, class OpT>
struct MatrixAssignmentUnroller
{
    /* Record traits for the arguments: */
    typedef ExprTraits<DestT> dest_traits;
    typedef ExprTraits<SrcT> src_traits;

    /* Get argument reference types: */
    typedef typename dest_traits::reference dest_reference;
    typedef typename src_traits::const_reference src_reference;

#if defined(CML_2D_UNROLLER)

    /* Forward declare: */
    template<int R, int C, int MaxRows, int MaxCols, bool can_unroll>
        struct Eval;

    /* XXX This needs to be specified for efficient col-major access also! */

    /** Evaluate the binary operator at element MaxRows,MaxCols. */
    template<int MaxRows, int MaxCols>
        struct Eval<MaxRows,MaxCols,MaxRows,MaxCols,true> {
            void operator()(dest_reference dest, src_reference src) const {
                OpT().apply(dest(MaxRows,MaxCols), src(MaxRows,MaxCols));
            }
        };

    /** Evaluate the binary operator at element MaxRows,C. */
    template<int C, int MaxRows, int MaxCols>
        struct Eval<MaxRows,C,MaxRows,MaxCols,true> {
            void operator()(dest_reference dest, src_reference src) const {
                OpT().apply(dest(MaxRows,C), src(MaxRows,C));

                /* Evaluate at MaxRows,C+1: */
                Eval<MaxRows,C+1,MaxRows,MaxCols,true>()(dest,src);
            }
        };

    /** Evaluate the binary operator at element R,MaxCols. */
    template<int R, int MaxRows, int MaxCols>
        struct Eval<R,MaxCols,MaxRows,MaxCols,true> {
            void operator()(dest_reference dest, src_reference src) const {
                OpT().apply(dest(R,MaxCols), src(R,MaxCols));

                /* Evaluate at R+1,0: */
                Eval<R+1,0,MaxRows,MaxCols,true>()(dest,src);
            }
        };

    /** Evaluate the binary operator at element R,C. */
    template<int R, int C, int MaxRows, int MaxCols>
        struct Eval<R,C,MaxRows,MaxCols,true> {
            void operator()(dest_reference dest, src_reference src) const {
                OpT().apply(dest(R,C), src(R,C));

                /* Evaluate at R,C+1: */
                Eval<R,C+1,MaxRows,MaxCols,true>()(dest,src);
            }
        };


    /** Evaluate operators on large matrices using a loop. */
    template<int R, int C, int MaxRows, int MaxCols>
        struct Eval<R,C,MaxRows,MaxCols,false> {
            void operator()(dest_reference dest, src_reference src) const {
                for(size_t i = 0; i <= MaxRows; ++ i) {
                    for(size_t j = 0; j <= MaxCols; ++ j) {
                        OpT().apply(dest(i,j), src(i,j));
                    }
                }
            }
        };

#endif // CML_2D_UNROLLER


#if defined(CML_2D_TO_1D_UNROLLER)

    /* Forward declare as a linear unroller: */
    template<int N, int Max, bool can_unroll> struct Eval;

    /** Evaluate the binary operator at element Max. */
    template<int Max> struct Eval<Max,Max,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to last element: */
            OpT().apply(dest(Max), src(Max));
        }
    };

    /** Evaluate the binary operator for the first Max-1 elements. */
    template<int N, int Max> struct Eval<N,Max,true> {
        void operator()(dest_reference dest, src_reference src) const {

            /* Apply to current N: */
            OpT().apply(dest(N), src(N));

            /* Apply to next N: */
            Eval<N+1,Max,true>()(dest, src);
        }
    };

    /** Evaluate the binary operator on large matrices using a loop. */
    template<int N, int Max> struct Eval<N,Max,false> {
        void operator()(dest_reference dest, src_reference src) const {
            for(size_t i = 0; i <= Max; ++ i) {
                OpT().apply(dest(i), src(i));
            }
        }
    };

#endif // CML_2D_TO_1D_UNROLLER

#if defined(CML_NO_2D_UNROLLER)

    /** Evaluate the binary operator using a loop. */
    template<int R, int C, int MaxRows, int MaxCols> struct Eval {
        void operator()(dest_reference dest, src_reference src) const {
            for(size_t i = 0; i <= MaxRows; ++ i) {
                for(size_t j = 0; j <= MaxCols; ++ j) {
                    OpT().apply(dest(i,j), src(i,j));
                }
            }
        }
    };

#endif // CML_NO_2D_UNROLLER

};

/** Unroll assignment for a fixed-sized matrix. */
template<class OpT, typename E, class AT, typename O, class SrcT>
void UnrollAssignment(
    cml::matrix<E,AT,O>& dest, const SrcT& src, cml::fixed_size_tag)
{
    typedef cml::matrix<E,AT,O> matrix_type;
    enum {
        MaxRows = matrix_type::array_rows-1,
        MaxCols = matrix_type::array_cols-1,
        Max = (MaxRows+1)*(MaxCols+1)
    };

#if defined(CML_2D_UNROLLER)
    /* Allow the 2D unroller to figure out how to unroll the loop: */
    typedef typename MatrixAssignmentUnroller<matrix_type,SrcT,OpT>::template
        Eval<0, 0, MaxRows, MaxCols, (Max <= CML_MATRIX_UNROLL_LIMIT)> Unroller;
#endif

#if defined(CML_2D_TO_1D_UNROLLER)
    /* Allow the linearizing unroller to figure out how to unroll the loop: */
    typedef typename MatrixAssignmentUnroller<matrix_type,SrcT,OpT>
      ::template Eval<0, Max, (Max <= CML_MATRIX_UNROLL_LIMIT)> Unroller;
#endif

#if defined(CML_NO_2D_UNROLLER)
    /* Allow the 2D unroller to figure out how to unroll the loop: */
    typedef typename MatrixAssignmentUnroller<matrix_type,SrcT,OpT>
        ::template Eval<0, 0, MaxRows, MaxCols> Unroller;
#endif

    Unroller()(dest,src);
}

/** Use a loop for dynamic-sized matrix assignment.
 *
 * @note The target matrix must already have the correct size.
 *
 * @bug This needs to be specialized for efficient row-major or col-major
 * access.
 */
template<class OpT, typename E, class AT, typename O, class SrcT>
void UnrollAssignment(
        cml::matrix<E,AT,O>& dest, const SrcT& src, cml::dynamic_size_tag)
{
    typedef ExprTraits<SrcT> src_traits;
    for(size_t i = 0; i <= dest.rows(); ++ i) {
        for(size_t j = 0; j <= dest.cols(); ++ j) {
            OpT().apply(dest(i,j), src(i,j));
        }
    }
}

}

/** This constructs an assignment unroller for fixed-size arrays.
 *
 * The operator must be an assignment op, otherwise, this doesn't make any
 * sense.  Also, DestT must a fixed array type.
 *
 * @note The target matrix must already have the correct size.
 *
 * @sa cml::vector
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 */
template<class OpT, typename E, class AT, typename O, class SrcT>
void UnrollAssignment(cml::matrix<E,AT,O>& dest, const SrcT& src) {
    typedef cml::matrix<E,AT,O> matrix_type;
    detail::UnrollAssignment<OpT>(dest, src, typename matrix_type::size_tag());
}

} // namespace et
} // namespace cml

#endif
#endif // !defined(cml_vector_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
