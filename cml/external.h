/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_h
#define external_h

namespace cml {

/** This is a selector for external 1D and 2D arrays.
 *
 * The external<> struct is used only to select a 1D or 2D array as the
 * base class of a vector or matrix.  The rebind<> template is used by
 * quaternion<> to select its vector length in a generic way.
 *
 * @sa fixed
 * @sa dynamic
 */
template<int Dim1 = -1, int Dim2 = -1> struct external {

    /** Rebind to a 1D type.
     *
     * This is used by quaternion<>.
     */
    template<int D> struct rebind { typedef external<D> other; };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
