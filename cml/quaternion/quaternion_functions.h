/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Functions on quaternions.
 */

#ifndef quaternion_functions_h
#define quaternion_functions_h

#include <cml/quaternion/quaternion_dot.h>

namespace cml {

/** Returns the real part of the quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
real(const quaternion<VecT,OrderT,CrossT>& q) { return q.real(); }

/** Returns the imaginary (vector) part of the quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline const VecT&
imaginary(const quaternion<VecT,OrderT,CrossT>& q) { return q.imaginary(); }

/** Returns the real (scalar) part of the QuaternionXpr. */
template<typename XprT> inline typename et::QuaternionXpr<XprT>::value_type
real(const et::QuaternionXpr<XprT>& e) { return e.real(); }

/** Returns the imaginary (vector) part of the QuaternionXpr. */
template<typename XprT> inline typename et::QuaternionXpr<XprT>::result_type
imaginary(const et::QuaternionXpr<XprT>& e) { return e.imaginary(); }

/** Cayley norm of a quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
norm(const quaternion<VecT,OrderT,CrossT>& arg)
{
    return dot(arg,arg);
}

/** Cayley norm of a QuaternionXpr. */
template<typename XprT>
inline typename XprT::value_type
norm(QUATXPR_ARG_TYPE arg)
{
    return dot(arg,arg);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
