/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Functions on quaternions.
 */

#ifndef quaternion_functions_h
#define quaternion_functions_h

namespace cml {

/** Returns the real part of the quaternion. */
template<typename VecT> inline typename VecT::value_type
real(const quaternion<VecT>& q) { return q.real(); }

/** Returns the imaginary (vector) part of the quaternion. */
template<typename VecT> inline const VecT&
imag(const quaternion<VecT>& q) { return q.imaginary(); }

/** Returns the real (scalar) part of the QuaternionXpr. */
template<typename XprT> inline typename et::QuaternionXpr<XprT>::value_type
real(const et::QuaternionXpr<XprT>& e) { return e.real(); }

/** Returns the imaginary (vector) part of the QuaternionXpr. */
template<typename XprT> inline typename et::QuaternionXpr<XprT>::result_type
imag(const et::QuaternionXpr<XprT>& e) { return e.imaginary(); }

/** Cayley norm of a quaternion. */
template<typename VecT>
inline typename VecT::value_type
norm(const quaternion<VecT>& arg)
{
    return arg[0]*arg[0] + arg[1]*arg[1] + arg[2]*arg[2] + arg[3]*arg[3];
}

/** Cayley norm of a QuaternionXpr. */
template<typename XprT>
inline typename XprT::value_type
norm(QUATXPR_ARG_TYPE arg)
{
    return arg[0]*arg[0] + arg[1]*arg[1] + arg[2]*arg[2] + arg[3]*arg[3];
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
