/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines promotions for matrices used in matrix/matrix or matrix/scalar
 * expressions.
 *
 * @sa UnaryMatrixOp
 * @sa BinaryMatrixOp
 */

#ifndef matrix_promotions_h
#define matrix_promotions_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>

namespace cml {

/* Forward declare for type promotions: */
template<typename E, class AT, class O> class matrix;

/* Promotions belong in the et namespace: */
namespace et {

/* Default matrix type promotion template. */
template<typename LeftT, typename RightT> struct MatrixPromote;

/** Type promotion for two matrix types.
 *
 * This requires that both matrix types have the same orientation, and
 * ensures that orientation for the resulting type.
 */
template<typename E1, class AT1, typename E2, class AT2, class O>
struct MatrixPromote< cml::matrix<E1,AT1,O>, cml::matrix<E2,AT2,O> >
{
    /* The deduced matrix result type: */
    typedef cml::matrix<
        typename ScalarPromote<E1,E2>::type,
        typename ArrayPromote<AT1,AT2>::type,
        O
    > type;
};

/** Type promotion for a matrix and a scalar. */
template<typename E, class AT, class O, typename S>
struct MatrixPromote<cml::matrix<E,AT,O>, S>
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<E,S>::type, AT O> type;
};

/** Type promotion for a scalar and a matrix. */
template<typename S, typename E, class AT, class O>
struct MatrixPromote<S, cml::matrix<E,AT,O> >
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<S,E>::type, AT, O> type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
