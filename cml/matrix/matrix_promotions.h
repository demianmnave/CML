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

#include <cml/core/cml_meta.h>
#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>
#include <cml/dynamic.h>

/* This is used below to create a more meaningful compile-time error when
 * either argument to OuterPromote has the wrong orientation.
 */
struct outer_promote_expects_properly_oriented_args_error;

namespace cml {
namespace et {

/* Default matrix type promotion template. */
template<typename LeftT, typename RightT> struct MatrixPromote;

/** Type promotion for two matrix types. */
template<typename E1, class AT1, typename L1,
         typename E2, class AT2, typename L2>
struct MatrixPromote< cml::matrix<E1,AT1,L1>, cml::matrix<E2,AT2,L2> >
{
    /* Promote the arrays: */
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

    /* The deduced temporary type: */
    typedef typename type::temporary_type temporary_type;
};

/** Type promotion for a matrix and a scalar. */
template<typename E, class AT, typename L, typename S>
struct MatrixPromote<cml::matrix<E,AT,L>, S>
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<E,S>::type, AT, L> type;

    /* The deduced temporary type: */
    typedef typename type::temporary_type temporary_type;
};

/** Type promotion for a scalar and a matrix. */
template<typename S, typename E, class AT, typename L>
struct MatrixPromote<S, cml::matrix<E,AT,L> >
{
    /* The deduced matrix result type (the array type is the same): */
    typedef cml::matrix<typename ScalarPromote<S,E>::type, AT, L> type;

    /* The deduced temporary type: */
    typedef typename type::temporary_type temporary_type;
};

/** Type promotion for outer product. */
template<typename E1, class AT1, class O1, typename E2, class AT2, class O2>
struct MatrixPromote< cml::vector<E1,AT1,O1>, cml::vector<E2,AT2,O2> >
{
    /* Require a left col-vector, and a right row-vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O1,col_vector>::is_true
             && same_type<O2,row_vector>::is_true),
            outer_promote_expects_properly_oriented_args_error);

    typedef cml::vector<E2,AT2,O1> left_type;
    typedef cml::vector<E2,AT2,O2> right_type;

    /* Get matrix size: */
    enum {
        array_rows = left_type::array_size,
        array_cols = right_type::array_size
    };

    /* Deduce the corresponding matrix types for the vectors: */
    typedef CML_DEFAULT_ARRAY_LAYOUT layout;
    typedef typename select_if<
        array_rows == -1, dynamic<>, fixed<array_rows,1>
    >::result left_storage;
    typedef cml::matrix<E1,left_storage,layout> left_matrix;

    typedef typename select_if<
        array_cols == -1, dynamic<>, fixed<1,array_rows>
    >::result right_storage;
    typedef cml::matrix<E2,right_storage,layout> right_matrix;

    /* Finally, promote the matrix types to get the result: */
    typedef typename et::MatrixPromote<left_matrix,right_matrix>::type type;
    typedef typename type::temporary_type temporary_type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
