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

#include <cml/core/fwd.h>
#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>

namespace cml {

/* Promotions belong in the et namespace: */
namespace et {

/* Default matrix type promotion template. */
template<typename LeftT, typename RightT> struct MatrixPromote;

/** Type promotion for two matrix types. */
template<typename E1, class AT1, typename L1,
         typename E2, class AT2, typename L2>
struct MatrixPromote< cml::matrix<E1,AT1,L1>, cml::matrix<E2,AT2,L2> >
{
    typedef typename ArrayPromote<
        typename cml::matrix<E1,AT1,L1>::array_type,
        typename cml::matrix<E2,AT2,L2>::array_type
    >::type promoted_array;

    /* The deduced matrix result type: */
    typedef cml::matrix<
        typename promoted_array::value_type,
        typename promoted_array::generator_type,
        typename promoted_array::layout
    > type;
};

/** Type promotion for a matrix and a scalar. */
template<typename E, class AT, typename L, typename S>
struct MatrixPromote<cml::matrix<E,AT,L>, S>
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<E,S>::type, AT, L> type;
};

/** Type promotion for a scalar and a matrix. */
template<typename S, typename E, class AT, typename L>
struct MatrixPromote<S, cml::matrix<E,AT,L> >
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<S,E>::type, AT, L> type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
