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

#include <cml/core/fwd.h>
#include <cml/et/scalar_promotions.h>
#include <cml/vector/vector_promotions.h>

namespace cml {

/* Promotions belong in the et namespace: */
namespace et {

/* Default mat/vec type promotion template. */
template<typename LeftT, typename RightT> struct MatVecPromote;

/** Type promotion for a matrix and a vector. */
template<typename E1, class AT1, typename L, typename E2, class AT2, class O>
struct MatVecPromote< cml::matrix<E1,AT1,L>, cml::vector<E2,AT2,O> >
{
    typedef cml::matrix<E1,AT1,L> matrix_type;
    typedef cml::vector<E2,AT2,O> vector_type;

    /* Promote the arrays: */
    typedef typename ArrayPromote<
        typename matrix_type::array_type,
        typename vector_type::array_type
    >::type promoted_array;

    /* The deduced vector result type: */
    typedef cml::vector<
        typename promoted_array::value_type,
        typename promoted_array::generator_type,
        col_vector
    > type;

    /* The deduced temporary type: */
    typedef typename type::temporary_type temporary_type;
    /* Note: this is to avoid an "incomplete type" error from ICC9, which
     * can't handle e.g. <X>::<Y>::<Z> when <X> is a template type.
     */
};

/** Type promotion for a vector and a matrix. */
template<typename E1, class AT1, class O, typename E2, class AT2, typename L>
struct MatVecPromote< cml::vector<E1,AT1,O>, cml::matrix<E2,AT2,L> >
{
    typedef cml::vector<E1,AT1,O> vector_type;
    typedef cml::matrix<E2,AT2,L> matrix_type;

    /* Promote the arrays: */
    typedef typename ArrayPromote<
        typename vector_type::array_type,
        typename matrix_type::array_type
    >::type promoted_array;

    /* The deduced vector result type: */
    typedef cml::vector<
        typename promoted_array::value_type,
        typename promoted_array::generator_type,
        row_vector
    > type;

    /* The deduced temporary type: */
    typedef typename type::temporary_type temporary_type;
    /* Note: this is to avoid an "incomplete type" error from ICC9, which
     * can't handle e.g. <X>::<Y>::<Z> when <X> is a template type.
     */
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
