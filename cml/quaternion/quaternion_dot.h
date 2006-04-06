/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef quaternion_dot_h
#define quaternion_dot_h

#include <cml/vector/vector_products.h>
#include <cml/quaternion/quaternion_expr.h>

namespace cml {
namespace detail {

template<typename LeftT, typename RightT> inline
typename detail::DotPromote<LeftT,RightT>::promoted_scalar
quaternion_dot(const LeftT& p, const RightT& q)
{
    return p[0]*q[0] + p[1]*q[1] + p[2]*q[2] + p[3]*q[3];
}

} // namespace detail

template<typename VecT1, typename VecT2, typename OrderT, typename CrossT>
inline typename detail::DotPromote<
    quaternion<VecT1,OrderT,CrossT>, quaternion<VecT2,OrderT,CrossT>
>::promoted_scalar
dot(const quaternion<VecT1,OrderT,CrossT>& p,
    const quaternion<VecT2,OrderT,CrossT>& q)
{
    return detail::quaternion_dot(p,q);
}

template<typename VecT, typename OrderT, typename CrossT, typename XprT>
inline typename detail::DotPromote<
    quaternion<VecT,OrderT,CrossT>, et::QuaternionXpr<XprT>
>::promoted_scalar
dot(const quaternion<VecT,OrderT,CrossT>& p, QUATXPR_ARG_TYPE q)
{
    return detail::quaternion_dot(p,q);
}

template<typename XprT, typename VecT, typename OrderT, typename CrossT>
inline typename detail::DotPromote<
    et::QuaternionXpr<XprT>, quaternion<VecT,OrderT,CrossT>
>::promoted_scalar
dot(QUATXPR_ARG_TYPE p, const quaternion<VecT,OrderT,CrossT>& q)
{
    return detail::quaternion_dot(p,q);
}

template<typename XprT1, typename XprT2> inline
typename detail::DotPromote<
    et::QuaternionXpr<XprT1>, et::QuaternionXpr<XprT2>
>::promoted_scalar
dot(QUATXPR_ARG_TYPE_N(1) p, QUATXPR_ARG_TYPE_N(2) q)
{
    return detail::quaternion_dot(p,q);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
