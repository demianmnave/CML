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
template<typename E, class AT, class OT, class CT>
inline typename quaternion<E,AT,OT,CT>::value_type
real(const quaternion<E,AT,OT,CT>& q)
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
template<typename E, class AT, class OT, class CT>
inline typename quaternion<E,AT,OT,CT>::imaginary_type
imaginary(const quaternion<E,AT,OT,CT>& q)
{
    return q.imaginary();
}

/** Returns the imaginary (vector) part of the QuaternionXpr. */
template<typename XprT>
inline typename et::QuaternionXpr<XprT>::temporary_type
imaginary(const et::QuaternionXpr<XprT>& e)
{
    return e.imaginary();
}

/** Cayley norm of a quaternion. */
template<typename E, class AT, class OT, class CT>
inline typename quaternion<E,AT,OT,CT>::value_type
norm(const quaternion<E,AT,OT,CT>& arg)
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
template<typename E, class AT, class OT, class CT>
inline typename quaternion<E,AT,OT,CT>::value_type
length_squared(const quaternion<E,AT,OT,CT>& arg)
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
template<typename E, class AT, class OT, class CT>
inline typename quaternion<E,AT,OT,CT>::value_type
length(const quaternion<E,AT,OT,CT>& arg)
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

/** Normalize a quaternion.
 *
 * The input quaternion is not changed.
 */
template<typename E, class AT, class OT, class CT>
inline quaternion<E,AT,OT,CT>
normalize(const quaternion<E,AT,OT,CT>& arg)
{
    typename quaternion<E,AT,OT,CT>::temporary_type result(arg);
    result.normalize();
    return result;
}

/** Normalize a quaternion expr. */
template<typename XprT>
inline typename XprT::temporary_type
normalize(QUATXPR_ARG_TYPE arg)
{
    return arg.normalize();
}

/** Set a quaternion to the multiplicative identity.
 *
 * The input quaternion is not changed.
 */
template<typename E, class AT, class OT, class CT>
inline quaternion<E,AT,OT,CT>
identity(const quaternion<E,AT,OT,CT>& arg)
{
    typename quaternion<E,AT,OT,CT>::temporary_type result(arg);
    result.identity();
    return result;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
