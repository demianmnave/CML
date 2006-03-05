/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines promotions for the vectors resulting from matrix/vector or
 * vector/matrix ops.
 *
 * @sa matvec_ops::mvmul
 */

#ifndef matvec_promotions_h
#define matvec_promotions_h

#include <cml/core/cml_meta.h>
#include <cml/et/scalar_promotions.h>
#include <cml/et/vector_promotions.h>

/* This is used below to create a more meaningful compile-time error when
 * mat-vec mul is not provided with the right arguments:
 */
struct matvec_promote_expects_properly_oriented_args_error;

namespace cml {

/* Forward declare for type promotions: */
template<typename E, class AT, class O> class vector;
template<typename E, class AT> class matrix;

/* Promotions belong in the et namespace: */
namespace et {

/* Default mat/vec type promotion template. */
template<typename LeftT, typename RightT> struct MatVecPromote;

/** Type promotion for a matrix and a vector.
 *
 * @note The vector must be a column vector.  This is enforced at compile time
 * unless CML_IGNORE_VECTOR_ORIENTATIONS is defined.
 */
template<typename E1, class AT1, typename E2, class AT2, class O>
struct MatVecPromote< cml::matrix<E1,AT1>, cml::vector<E2,AT2,O> >
{
    typedef cml::matrix<E1,AT1> matrix_type;
    typedef cml::vector<E2,AT2,O> vector_type;

    /* Require a column vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O,col_vector>::is_true),
            matvec_promote_expects_properly_oriented_args_error);

    /* The deduced vector result type: */
    typedef typename VectorPromote<
        typename matrix_type::row_type,
        typename vector_type::transpose_type
    >::type type;
};

/** Type promotion for a vector and a matrix.
 *
 * @note The vector must be a row vector.  This is enforced at compile time
 * unless CML_IGNORE_VECTOR_ORIENTATIONS is defined.
 */
template<typename E1, class AT1, class O, typename E2, class AT2>
struct MatVecPromote< cml::vector<E1,AT1,O>, cml::matrix<E2,AT2> >
{
    typedef cml::vector<E1,AT1,O> vector_type;
    typedef cml::matrix<E2,AT2> matrix_type;

    /* Require a row vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O,row_vector>::is_true),
            matvec_promote_expects_properly_oriented_args_error);

    /* The deduced vector result type: */
    typedef typename VectorPromote<
        typename vector_type::transpose_type,
        typename matrix_type::row_type
    >::type type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
