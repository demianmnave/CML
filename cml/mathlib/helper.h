/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef helper_h
#define helper_h

#include <cstddef>
#include <cml/constants.h>

namespace cml {

/* Helper classes for axis order, coordinate system handedness, z-clipping
 * range and spherical coordinate type.
 *
 * @todo: Figure out the best way to handle this.
 *
 * Initially I used enumerations for these parameters, but switched to class
 * objects to prevent the passing of erroneous values for arguments. However,
 * it had slipped my mind that type is enforced with C++ enums, so passing of
 * correct arguments would have been ensured anyway. Duh.
 *
 * Still, enums seem a little clunky, so maybe this is better. We'll see.
 *
 * Also, these should go in their own file, but I couldn't think of a name for
 * it. And finally, they should probably be taken out of the detail namespace,
 * as users may want to declare variables of these types. The only issue with
 * that is that some functions have argument names that are the same as the
 * class names, so those will probably have to be revised.
 *
 * Update: Ok, I backed myself into a bit of a corner here and had to do some
 * hackery to get myself out. In short, I made the helper object global, which
 * worked fine within an Xcode project, but not (I think) in the CML as a
 * standalone library.
 *
 * Rather than re-write a lot of code, I did some hacks in this file so that
 * the code elsewhere would only require minimal changes. The motivation was
 * basically to avoid yet another delay in getting the library out, but once
 * things have settled down a bit I'll redo all this. From the user's
 * perspective, all that really matters is that there is some constant or
 * global or static object that can be passed to represent a particular
 * handedness, Euler-angle order, or what have you. Once we've settled on a
 * syntax for this, updating user code to reflect it should be a simple matter
 * of a few search-and-replace's.
 *
 * Update: Switched to enums. May revisit again though.
 */
 
//////////////////////////////////////////////////////////////////////////////
// Euler order
//////////////////////////////////////////////////////////////////////////////

enum EulerOrder {
    euler_order_xyz, // 0x00 [0000]
    euler_order_xyx, // 0x01 [0001]
    euler_order_xzy, // 0x02 [0010]
    euler_order_xzx, // 0x03 [0011]
    euler_order_yzx, // 0x04 [0100]
    euler_order_yzy, // 0x05 [0101]
    euler_order_yxz, // 0x06 [0110]
    euler_order_yxy, // 0x07 [0111]
    euler_order_zxy, // 0x08 [1000]
    euler_order_zxz, // 0x09 [1001]
    euler_order_zyx, // 0x0A [1010]
    euler_order_zyz  // 0x0B [1011]
};

namespace detail {

/* Note: All this bit-hacking is kind of old-school, so I may try to replace
 * it at some point with something more elegant (ideally without disturbing
 * the API).
 */

inline void unpack_euler_order(
    EulerOrder order,
    size_t& i,
    size_t& j,
    size_t& k,
    bool& odd,
    bool& repeat)
{
    enum { REPEAT = 0x01, ODD = 0x02, AXIS = 0x0C };

    repeat = order & REPEAT;
    odd = order & ODD;
    size_t offset = size_t(odd);
    i = (order & AXIS) % 3;
    j = (i + 1 + offset) % 3;
    k = (i + 2 - offset) % 3;
    
    /* @todo: I'm thinking about either adding a 'reverse' argument to
     * cyclic_permutation(), or offering a reverse_cyclic_permutation()
     * function, in which case the above can be passed off to this (these)
     * function (functions).
     */
}

} // namespace detail

//////////////////////////////////////////////////////////////////////////////
// Axis order
//////////////////////////////////////////////////////////////////////////////

enum AxisOrder {
    axis_order_xyz = euler_order_xyz, // 0x00 [0000]
    axis_order_xzy = euler_order_xzy, // 0x02 [0010]
    axis_order_yzx = euler_order_yzx, // 0x04 [0100]
    axis_order_yxz = euler_order_yxz, // 0x06 [0110]
    axis_order_zxy = euler_order_zxy, // 0x08 [1000]
    axis_order_zyx = euler_order_zyx, // 0x0A [1010]
};

namespace detail {

/* Note: There's some duplicated effort here. I might try to clean it up
 * within the current context, or replace the whole system with something more
 * elegant as noted above.
 */

inline void unpack_axis_order(
    AxisOrder order,
    size_t& i,
    size_t& j,
    size_t& k,
    bool& odd)
{
    enum { ODD = 0x02, AXIS = 0x0C };

    odd = order & ODD;
    size_t offset = size_t(odd);
    i = (order & AXIS) % 3;
    j = (i + 1 + offset) % 3;
    k = (i + 2 - offset) % 3;
    
    /* @todo: I'm thinking about either adding a 'reverse' argument to
     * cyclic_permutation(), or offering a reverse_cyclic_permutation()
     * function, in which case the above can be passed off to this (these)
     * function (functions).
     */
}

inline AxisOrder pack_axis_order(size_t i, bool odd) {
    return AxisOrder((i << 2) | (size_t(odd) << 1));
}

inline AxisOrder swap_axis_order(AxisOrder order)
{
    size_t i, j, k;
    bool odd;
    unpack_axis_order(order, i, j, k, odd);
    return pack_axis_order(j, !odd);
}

} // namespace detail

//////////////////////////////////////////////////////////////////////////////
// Axis order 2D
//////////////////////////////////////////////////////////////////////////////

enum AxisOrder2D {
    axis_order_xy = axis_order_xyz, // 0x00 [0000]
    axis_order_yx = axis_order_yxz, // 0x06 [0110]
};

namespace detail {

/* Note: There's some duplicated effort here. I might try to clean it up
 * within the current context, or replace the whole system with something more
 * elegant as noted above.
 */

inline void unpack_axis_order_2D(
    AxisOrder2D order,
    size_t& i,
    size_t& j,
    bool& odd)
{
    enum { ODD = 0x02, AXIS = 0x0C };

    odd = order & ODD;
    size_t offset = size_t(odd);
    i = (order & AXIS) % 3;
    j = (i + 1 + offset) % 3;
    
    /* @todo: I'm thinking about either adding a 'reverse' argument to
     * cyclic_permutation(), or offering a reverse_cyclic_permutation()
     * function, in which case the above can be passed off to this (these)
     * function (functions).
     */
}

} // namespace detail

//////////////////////////////////////////////////////////////////////////////
// Handedness
//////////////////////////////////////////////////////////////////////////////

enum Handedness { left_handed, right_handed };

//////////////////////////////////////////////////////////////////////////////
// Z clip
//////////////////////////////////////////////////////////////////////////////

enum ZClip { z_clip_neg_one, z_clip_zero };

//////////////////////////////////////////////////////////////////////////////
// Spherical coordinate type
//////////////////////////////////////////////////////////////////////////////

enum SphericalType { latitude, colatitude };

} // namespace cml

#endif