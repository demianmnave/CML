/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_quaternion_readable_quaternion_h
#define	cml_quaternion_readable_quaternion_h

#include <cml/common/compiler.h>
#include <cml/scalar/binary_ops.h>
#include <cml/quaternion/cross_type.h>
#include <cml/quaternion/order.h>
#include <cml/quaternion/traits.h>

// #include <cml/quaternion/temporary.h>

namespace cml {

#if 0
/* Forward declarations: */
template<class Sub, class Scalar, class Op> class quaternion_scalar_node;
template<class Sub> class imaginary_node;
#endif

/** Base class for readable quaternion types.  Readable quaternions support
 * const access to its elements.
 *
 * DerivedT must implement:
 *
 * - <X> get(int i) const, where <X> is the immutable_value type defined by
 * quaternion_traits<DerivedT>.  Note that immutable_value is not
 * necessarily a reference or const type.
 */
template<class DerivedT>
class readable_quaternion
{
  public:

    typedef DerivedT					quaternion_type;
    typedef quaternion_traits<quaternion_type>		traits_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::order_type		order_type;
    typedef typename traits_type::cross_type		cross_type;


  public:

    /** Localize the ordering as an enum. */
    enum {
        W = order_type::W,
        X = order_type::X,
        Y = order_type::Y,
        Z = order_type::Z
    };


  public:

    /** Return a const reference to the quaternion cast as DerivedT. */
    const DerivedT& actual() const;

    /** Return const element @c i. */
    immutable_value get(int i) const;

    /** Return const element @c i. */
    immutable_value operator[](int i) const;


  public:

    /** Return the real part of the quaternion. */
    immutable_value real() const;

    /** Return the squared length of the quaternion. */
    value_type length_squared() const;

    /** Return the length of the quaternion. */
    value_type length() const;

    /** Return the Cayley norm of the quaternion. */
    value_type norm() const;

#if 0
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Return the imaginary part of the quaternion as a vector expression,
     * storing a reference of the source quaternion in the node.
     */
    imaginary_node<const DerivedT&> imaginary() const &;

    /** Return the imaginary part of the quaternion as a vector expression,
     * storing a copy of the source quaternion in the node.
     */
    imaginary_node<DerivedT&&> imaginary() const &&;
#else
    /** Return the imaginary part of the quaternion as a vector expression,
     * storing a copy of the source quaternion in the node.
     */
    imaginary_node<DerivedT&&> imaginary() const;
#endif
#endif

#if 0
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Return the normalized quaternion as an expression node, storing a
     * reference of the source quaternion in the node.
     */
    quaternion_scalar_node<const DerivedT&, value_type,
      op::binary_divide<value_type,value_type>> normalize() const &;

    /** Return the normalized quaternion as an expression node, storing a
     * copy of the quaternion in the node.
     */
    quaternion_scalar_node<DerivedT&&, value_type,
      op::binary_divide<value_type,value_type>> normalize() const &&;
#else
    /** Return the normalized quaternion as an expression node, storing a
     * copy of the quaternion in the node.
     */
    quaternion_scalar_node<DerivedT&&, value_type,
      op::binary_divide<value_type,value_type>> normalize() const;
#endif
#endif


  protected:

    // Use the compiler-generated default constructor:
    readable_quaternion() = default;

    // Use the compiler-generated copy constructor:
    readable_quaternion(const readable_quaternion&) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    // Use the compiler-generated move constructor:
    readable_quaternion(readable_quaternion&&) = default;
#endif
};

} // namespace cml

#define __CML_QUATERNION_READABLE_QUATERNION_TPP
#include <cml/quaternion/readable_quaternion.tpp>
#undef __CML_QUATERNION_READABLE_QUATERNION_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
