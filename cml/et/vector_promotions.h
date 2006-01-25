/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
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

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
