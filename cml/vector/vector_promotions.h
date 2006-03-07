/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines promotions for vectors used in vector/vector or vector/scalar
 * expressions.
 *
 * @sa BinaryVectorOp
 */

#ifndef vector_promotions_h
#define vector_promotions_h

#include <cml/core/fwd.h>
#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>

/* This is used below to create a more meaningful compile-time error when the
 * orientations of the arguments to VectorPromote are not the same:
 */
struct vector_promote_expects_vectors_with_same_orientation_error;

namespace cml {
namespace et {

/* Default vector type promotion template. */
template<typename LeftT, typename RightT> struct VectorPromote;

/** Type promotion for two vector types. */
template<typename E1, class AT1, class O1,
         typename E2, class AT2, class O2>
struct VectorPromote< cml::vector<E1,AT1,O1>, cml::vector<E2,AT2,O2> >
{
    /* Require a row vector: */
    CML_STATIC_REQUIRE_M(
            (same_type<O1,O2>::is_true),
            vector_promote_expects_vectors_with_same_orientation_error);

    typedef typename ArrayPromote<
        typename cml::vector<E1,AT1,O1>::array_type,
        typename cml::vector<E2,AT2,O2>::array_type
    >::type promoted_array;

    /* The deduced vector result type: */
    typedef cml::vector<
        typename promoted_array::value_type,
        typename promoted_array::generator_type,
        O1
    > type;
};

/** Type promotion for a vector and a scalar. */
template<typename E, class AT, class O, typename S>
struct VectorPromote<cml::vector<E,AT,O>, S>
{
    /* The deduced vector result type (the array type is the same): */
    typedef cml::vector<typename ScalarPromote<E,S>::type, AT, O> type;
};

/** Type promotion for a scalar and a vector. */
template<typename S, typename E, class AT, class O>
struct VectorPromote<S, cml::vector<E,AT,O> >
{
    /* The deduced vector result type (the array type is the same): */
    typedef cml::vector<typename ScalarPromote<S,E>::type, AT, O> type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
