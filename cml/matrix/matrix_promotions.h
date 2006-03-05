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
template<typename E, class AT> class matrix;

/* Promotions belong in the et namespace: */
namespace et {

/* Default matrix type promotion template. */
template<typename LeftT, typename RightT> struct MatrixPromote;

/** Type promotion for two matrix types. */
template<typename E1, class AT1, typename E2, class AT2>
struct MatrixPromote< cml::matrix<E1,AT1>, cml::matrix<E2,AT2> >
{
    typedef typename ArrayPromote<
        typename cml::matrix<E1,AT1>::array_type,
        typename cml::matrix<E2,AT2>::array_type
    >::type promoted_array;

    /* The deduced matrix result type: */
    typedef cml::matrix<
        typename promoted_array::value_type,
        typename promoted_array::generator_type
    > type;
};

/** Type promotion for a matrix and a scalar. */
template<typename E, class AT, typename S>
struct MatrixPromote<cml::matrix<E,AT>, S>
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<E,S>::type, AT> type;
};

/** Type promotion for a scalar and a matrix. */
template<typename S, typename E, class AT>
struct MatrixPromote<S, cml::matrix<E,AT> >
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<S,E>::type, AT> type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
