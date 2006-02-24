/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_unroller_h
#define matrix_unroller_h

#if !defined(CML_2D_UNROLLER) && !defined(CML_NO_2D_UNROLLER)
#error "The matrix unroller is not defined."
#endif

#if defined(CML_2D_UNROLLER) && !defined(CML_MATRIX_UNROLL_LIMIT)
#error "CML_MATRIX_UNROLL_LIMIT is undefined."
#endif


#include <cml/et/traits.h>
#include <cml/et/size_checking.h>

namespace cml {

/* Forward declare for the matrix expressions below: */
template<typename E, class AT> class matrix;

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
 * @bug The 2D unroller needs to be specified for efficient col-major
 * access.
 */
template<class OpT, typename E, class AT, class SrcT>
struct MatrixAssignmentUnroller
{
    /* The matrix type being assigned to: */
    typedef cml::matrix<E,AT> matrix_type;

    /* Record traits for the arguments: */
    typedef ExprTraits<matrix_type> dest_traits;
    typedef ExprTraits<SrcT> src_traits;

    /* Get argument reference types: */
    typedef typename dest_traits::reference dest_reference;
    typedef typename src_traits::const_reference src_reference;

#if defined(CML_2D_UNROLLER)

    /* Forward declare: */
    template<int R, int C, int MaxRows, int MaxCols, bool can_unroll>
        struct Eval;

    /* XXX This needs to be specified for efficient col-major access also! */

    /** Evaluate the binary operator at element R,C. */
    template<int R, int C, int LastRow, int LastCol>
        struct Eval<R,C,LastRow,LastCol,true> {
            void operator()(dest_reference dest, src_reference src) const {

                /* Apply to current R,C: */
                OpT().apply(dest(R,C), src_traits().get(src,R,C));

                /* Evaluate at R,C+1: */
                Eval<R,C+1,LastRow,LastCol,true>()(dest,src);
            }
        };

    /** Evaluate the binary operator at element R,LastCol. */
    template<int R, int LastRow, int LastCol>
        struct Eval<R,MaxCols,LastRow,LastCol,true> {
            void operator()(dest_reference dest, src_reference src) const {

                /* Apply to R,LastCol: */
                OpT().apply(dest(R,MaxCols), src_traits().get(src,R,LastCol));

                /* Evaluate at R+1,0; i.e. move to next row and start the
                 * col iteration from 0:
                 */
                Eval<R+1,0,LastRow,LastCol,true>()(dest,src);
            }
        };

    /** Evaluate the binary operator at element LastRow,C. */
    template<int C, int LastRow, int LastCol>
        struct Eval<LastRow,C,LastRow,LastCol,true> {
            void operator()(dest_reference dest, src_reference src) const {

                /* Apply to LastRow,C: */
                OpT().apply(dest(MaxRows,C), src_traits().get(src,LastRow,C));

                /* Evaluate at LastRow,C+1: */
                Eval<LastRow,C+1,LastRow,LastCol,true>()(dest,src);
            }
        };

    /** Evaluate the binary operator at element MaxRows-1,MaxCols-1. */
    template<int MaxRows, int MaxCols>
        struct Eval<MaxRows,MaxCols,MaxRows,MaxCols,true> {
            void operator()(dest_reference dest, src_reference src) const {

                /* Apply to LastRow,LastCol: */
                OpT().apply(
                        dest(LastRow,LastCol),
                        src_traits().get(src,LastRow,LastCol));
            }
        };


    /** Evaluate operators on large matrices using a loop. */
    template<int R, int C, int LastRow, int LastCol>
        struct Eval<R,C,LastRow,LastCol,false> {
            void operator()(dest_reference dest, src_reference src) const {
                for(size_t i = 0; i <= LastRow; ++i) {
                    for(size_t j = 0; j <= LastCol; ++j) {
                        OpT().apply(dest(i,j), src_traits().get(src,i,j));
                    }
                }
            }
        };

#endif // CML_2D_UNROLLER

#if defined(CML_NO_2D_UNROLLER)

    /** Evaluate the binary operator using a loop. */
    template<int R, int C, int LastRow, int LastCol> struct Eval {
        void operator()(dest_reference dest, src_reference src) const {
            for(size_t i = 0; i <= LastRow; ++i) {
                for(size_t j = 0; j <= LastCol; ++j) {
                    OpT().apply(dest(i,j), src_traits().get(src,i,j));
                }
            }
        }
    };

#endif // CML_NO_2D_UNROLLER

};

/** Unroll assignment for a fixed-sized matrix. */
template<class OpT, typename E, class AT, class SrcT>
void UnrollAssignment(
    cml::matrix<E,AT>& dest, const SrcT& src, cml::fixed_size_tag)
{
    typedef cml::matrix<E,AT> matrix_type;
    enum {
        MaxRows = matrix_type::array_rows,
        MaxCols = matrix_type::array_cols,
        Max = MaxRows*MaxCols
    };

#if defined(CML_2D_UNROLLER)
    typedef typename MatrixAssignmentUnroller<OpT,E,AT,SrcT>::template
        Eval<0, 0, MaxRows-1, MaxCols-1,
        (Max <= CML_MATRIX_UNROLL_LIMIT)> Unroller;
#endif

#if defined(CML_NO_2D_UNROLLER)
    /* Use a loop: */
    typedef typename MatrixAssignmentUnroller<OpT,E,AT,SrcT>
        ::template Eval<0, 0, MaxRows-1, MaxCols-1> Unroller;
#endif

    Unroller()(dest,src);
}

/** Use a loop for dynamic-sized matrix assignment.
 *
 * @note The target matrix must already have the correct size.
 *
 * @todo This needs to be specialized for efficient row-major or col-major
 * layout access.
 */
template<class OpT, typename E, class AT, class SrcT>
void UnrollAssignment(
        cml::matrix<E,AT>& dest, const SrcT& src, cml::dynamic_size_tag)
{
    typedef ExprTraits<SrcT> src_traits;
    for(size_t i = 0; i <= dest.rows(); ++i) {
        for(size_t j = 0; j <= dest.cols(); ++j) {
            OpT().apply(dest(i,j), src_traits().get(src,i,j));
            /* Note: we don't need get(), since we know dest is a vector. */
        }
    }
}

}

/** This constructs an assignment unroller for fixed-size arrays.
 *
 * The operator must be an assignment op (otherwise, this doesn't make any
 * sense).  Also, automatic unrolling is only performed for fixed-size
 * matrices; a loop is used for dynamic-sized matrices.
 *
 * @sa cml::matrix
 * @sa cml::et::OpAssign
 *
 * @bug Need to verify that OpT is actually an assignment operator.
 */
template<class OpT, class SrcT, typename E, class AT>
void UnrollAssignment(cml::matrix<E,AT>& dest, const SrcT& src) {
    typedef cml::matrix<E,AT> matrix_type;

    /* Record traits for the arguments: */
    typedef ExprTraits<matrix_type> dest_traits;
    typedef ExprTraits<SrcT> src_traits;

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time:
     */
    CheckLinearExprSizes<matrix_type,SrcT,matrix_result_tag>()(dest,src);

    /* Do the unroll call: */
    detail::UnrollAssignment<OpT>(dest, src, typename matrix_type::size_tag());
}

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
