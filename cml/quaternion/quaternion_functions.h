/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Functions on quaternions.
 *
 * @todo The functions that return quaternions and vectors should be changed
 * to return quaternion expression nodes, as should the corresponding
 * class methods.
 */

#ifndef quaternion_functions_h
#define quaternion_functions_h

namespace cml {

/** Returns the real part of the quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
real(const quaternion<VecT,OrderT,CrossT>& q)
{
    return q.real();
}

/** Returns the real (scalar) part of the QuaternionXpr. */
template<typename XprT>
inline typename et::QuaternionXpr<XprT>::value_type
real(const et::QuaternionXpr<XprT>& e)
{
    return e.real();
}

/** Returns the imaginary (vector) part of the quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline const VecT&
imaginary(const quaternion<VecT,OrderT,CrossT>& q)
{
    return q.imaginary();
}

/** Returns the imaginary (vector) part of the QuaternionXpr. */
template<typename XprT>
inline typename et::QuaternionXpr<XprT>::result_type
imaginary(const et::QuaternionXpr<XprT>& e)
{
    return e.imaginary();
}

/** Cayley norm of a quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
norm(const quaternion<VecT,OrderT,CrossT>& arg)
{
    return arg.length_squared();
}

/** Cayley norm of a QuaternionXpr. */
template<typename XprT>
inline typename XprT::value_type
norm(QUATXPR_ARG_TYPE arg)
{
    return arg.length_squared();
}

/** Squared length of a quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
length_squared(const quaternion<VecT,OrderT,CrossT>& arg)
{
    return arg.length_squared();
}

/** Squared length of a quaternion expr. */
template<typename XprT>
inline typename XprT::value_type
length_squared(QUATXPR_ARG_TYPE arg)
{
    return arg.length_squared();
}

/** Length of a quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline typename VecT::value_type
length(const quaternion<VecT,OrderT,CrossT>& arg)
{
    return arg.length();
}

/** Length of a quaternion expr. */
template<typename XprT>
inline typename XprT::value_type
length(QUATXPR_ARG_TYPE arg)
{
    return arg.length();
}

/** Normalize a quaternion. */
template<typename VecT, typename OrderT, typename CrossT>
inline quaternion<VecT,OrderT,CrossT>&
normalize(quaternion<VecT,OrderT,CrossT>& arg)
{
    return arg.normalize();
}

/** Normalize a quaternion expr. */
template<typename XprT>
inline typename XprT::result_type
normalize(QUATXPR_ARG_TYPE arg)
{
    return arg.normalize();
}

/** Set a quaternion to the multiplicative identity. */
template<typename VecT, typename OrderT, typename CrossT>
inline quaternion<VecT,OrderT,CrossT>&
identity(quaternion<VecT,OrderT,CrossT>& arg)
{
    return arg.identity();
}


} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
