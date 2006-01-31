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
template<typename E, class AT> class vector;

/* Promotions belong in the et namespace: */
namespace et {

/* Default vector type promotion template. */
template<typename LeftT, typename RightT> struct VectorPromote;

/** Type promotion for two vector types. */
template<typename E1, class AT1, typename E2, class AT2>
struct VectorPromote< cml::vector<E1,AT1>, cml::vector<E2,AT2> >
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<E1,E2>::type,
        typename ArrayPromote<AT1,AT2>::type
            > type;
};

/** Type promotion for a vector and a scalar. */
template<typename E, class AT, typename S>
struct VectorPromote<cml::vector<E,AT>, S>
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<E,S>::type,
        typename ArrayPromote<AT,AT>::type
            > type;
};

/** Type promotion for a scalar and a vector. */
template<typename S, typename E, class AT>
struct VectorPromote<S, cml::vector<E,AT> >
{
    /* The deduced vector result type: */
    typedef cml::vector<
        typename ScalarPromote<S,E>::type,
        typename ArrayPromote<AT,AT>::type
            > type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
