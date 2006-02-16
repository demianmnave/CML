/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  @warning The promotions aren't complete yet.
 *  @todo Add missing promotions.
 */

#ifndef vector_promotions_h
#define vector_promotions_h

#include <cml/et/scalar_promotions.h>
#include <cml/et/array_promotions.h>

namespace cml {

/* Forward declare for type promotions: */
template<typename E, class AT, class O> class vector;

/* Promotions belong in the et namespace: */
namespace et {

/* Default vector type promotion template. */
template<typename LeftT, typename RightT> struct VectorPromote;

/** Type promotion for two vector types.
 *
 * This requires that both vector types have the same orientation.
 */
template<typename E1, class AT1, typename E2, class AT2, class O>
struct VectorPromote< cml::vector<E1,AT1,O>, cml::vector<E2,AT2,O> >
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<E1,E2>::type,
        typename ArrayPromote<AT1,AT2>::type,
        O > type;
};

/** Type promotion for a vector and a scalar. */
template<typename E, class AT, class O, typename S>
struct VectorPromote<cml::vector<E,AT,O>, S>
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<E,S>::type,
        typename ArrayPromote<AT,AT>::type,
        O > type;
};

/** Type promotion for a scalar and a vector. */
template<typename S, typename E, class AT, class O>
struct VectorPromote<S, cml::vector<E,AT,O> >
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<S,E>::type,
        typename ArrayPromote<AT,AT>::type,
        O > type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
