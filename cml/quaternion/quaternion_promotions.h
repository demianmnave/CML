/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef quaternion_promotions_h
#define quaternion_promotions_h

#include <cml/et/scalar_promotions.h>
#include <cml/vector/vector_promotions.h>

namespace cml {
namespace et {

/* Default quaternion type promotion template. */
template<typename LeftT, typename RightT> struct QuaternionPromote;

/** Type promotion for two quaternion types. */
template<typename VecT1, typename VecT2, typename OrderT>
struct QuaternionPromote<
    cml::quaternion<VecT1,OrderT>,
    cml::quaternion<VecT2,OrderT>
>
{
    /* The deduced vector type: */
    typedef typename VectorPromote<VecT1, VecT2>::type promoted_vector;

    /* The deduced quaternion result type: */
    typedef cml::quaternion<promoted_vector,OrderT> type;
};

/** Type promotion for a quaternion and a vector. */
template<typename VecT, typename OrderT, typename E, class AT>
struct QuaternionPromote<
    cml::quaternion<VecT,OrderT>,
    cml::vector<E,AT>
>
{
    /* The deduced vector type: */
    typedef typename VectorPromote<
        VecT, cml::vector<E,AT>
    >::type promoted_vector;

    /* The deduced quaternion result type: */
    typedef cml::quaternion<promoted_vector,OrderT> type;
};

/** Type promotion for a quaternion and a vector. */
template<typename E, class AT, typename VecT, typename OrderT>
struct QuaternionPromote<
    cml::vector<E,AT>,
    cml::quaternion<VecT,OrderT>
>
{
    /* The deduced vector type: */
    typedef typename VectorPromote<
        cml::vector<E,AT>, VecT
    >::type promoted_vector;

    /* The deduced quaternion result type: */
    typedef cml::quaternion<promoted_vector,OrderT> type;
};

/** Type promotion for a quaternion and a scalar. */
template<typename VecT, typename OrderT, typename S>
struct QuaternionPromote<cml::quaternion<VecT,OrderT>, S>
{
    /* The deduced vector type: */
    typedef typename VectorPromote<VecT,S>::type promoted_vector;

    /* The deduced quaternion result type: */
    typedef cml::quaternion<promoted_vector,OrderT> type;
};

/** Type promotion for a scalar and a quaternion. */
template<typename S, typename VecT, typename OrderT>
struct QuaternionPromote<S, cml::quaternion<VecT,OrderT> >
{
    /* The deduced vector type: */
    typedef typename VectorPromote<S,VecT>::type promoted_vector;

    /* The deduced quaternion result type: */
    typedef cml::quaternion<promoted_vector,OrderT> type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
