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

#if 0
#if 0
/** Type promotion for matrix multiplication.
 */
template<typename E1, class AT1, typename E2, class AT2>
struct MatMulPromote< cml::matrix<E1,AT1>, cml::matrix<E2,AT2> >
{
    /* If either matrix is dynamically-sized, use ArrayPromote<> to deduce
     * the size.  Otherwise, both are fixed-sized, so generate the new type
     * directly:
     */
    typedef typename AT1::size_tag left_tag;
    typedef typename AT2::size_tag right_tag;
    select_if<
        (same_type<left_tag,fixed_size_tag>::is_true
         && same_type<right_tag,fixed_size_tag>::is_true),

        /* If A has size R1xC1 and B has size C1xR2, then the result has
         * size R1xR2, with its layout inherited from AT1:
         */
        fixed<AT1::array_rows,AT2::array_rows,typename AT1::layout>,
        typename ArrayPromote<AT1,AT2>::type

    /* The deduced matrix result type: */
    typedef cml::matrix<
        typename ScalarPromote<E1,E2>::type,
        typename ArrayPromote<AT1,AT2>::type,
        O
    > type;
};

#else
/** Type promotion for matrix multiplication
 */
template<typename E1, class AT1, typename O1,
         typename E2, class AT2, typename O2>
struct MatMulPromote< cml::matrix<E1,AT1,O1>, cml::matrix<E2,AT2,O2> >
{
    /* Require opposite orientations: */
    CML_STATIC_REQUIRE((same_type<O1,O2>::is_false));

    /* If either matrix is dynamically-sized, use ArrayPromote<> to deduce
     * the size.  Otherwise, both are fixed-sized, so generate the new type
     * directly:
     */
    typedef typename AT1::size_tag left_tag;
    typedef typename AT2::size_tag right_tag;
    select_if<
        same_type<left_tag,fixed_size_tag>::is_true
        && same_type<right_tag,fixed_size_tag>::is_true,
        fixed<

        type_pair<left_
        type_pair<fixed_size_tag,fixed_s
    typename ArrayPromote<AT1,AT2>::type deduced_array;

    /* The deduced matrix result type: */
    typedef cml::matrix<
        typename ScalarPromote<E1,E2>::type,
        typename ArrayPromote<AT1,AT2>::type,
        O
    > type;
};
#endif
#endif

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
